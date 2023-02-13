#define LUA_CORE
#include "lua/lfunc.h"
#include "lua/lgc.h"
#include "lua/lobject.h"
#include "lua/ltable.h"
#include "lua/lvm.h"

#include <stdbool.h>

#include "../../common/opcodes.h"

/* Protects the stack pointer from any external Lua calls that could reallocate the stack. */
#define PROTECT(x)                                                                                 \
    {                                                                                              \
        L->savedpc = pc;                                                                           \
        {                                                                                          \
            x;                                                                                     \
        };                                                                                         \
        base = L->base;                                                                            \
    }

#define RUNTIME_CHECK(L, c)                                                                        \
    {                                                                                              \
        if (!(c))                                                                                  \
            break;                                                                                 \
    }

#define DO_ARITH(op, ra, rb, rc, tm)                                                               \
    {                                                                                              \
        if (ttisnumber(rb) && ttisnumber(rc)) {                                                    \
            lua_Number nb = nvalue(rb), nc = nvalue(rc);                                           \
            setnvalue(ra, op(nb, nc));                                                             \
        } else                                                                                     \
            PROTECT(luaV_arith(L, ra, rb, rc, tm));                                                \
    }

#define JUMP(L, pc, i)                                                                             \
    {                                                                                              \
        (pc) += (i);                                                                               \
        luai_threadyield(L);                                                                       \
    }

/* Performs basic arithmetic operation and invokes luaV_arith if needed */
#define ARITH(op, tm)                                                                              \
    {                                                                                              \
        StkId ra = RA(i);                                                                          \
        StkId rb = RB(i);                                                                          \
        StkId rc = RC(i);                                                                          \
                                                                                                   \
        DO_ARITH(op, ra, rb, rc, tm);                                                              \
    }

#define ARITHK(op, tm)                                                                             \
    {                                                                                              \
        StkId ra = RA(i);                                                                          \
        StkId rb = RB(i);                                                                          \
        StkId rk = KC(i);                                                                          \
                                                                                                   \
        DO_ARITH(op, ra, rb, rk, tm);                                                              \
    }

#define JUMP(L, pc, i)                                                                             \
    {                                                                                              \
        (pc) += (i);                                                                               \
        luai_threadyield(L);                                                                       \
    }

/* Register manipulation */
#define RA(i) (lua_assert(GETARG_A(i) < L->top - base), (&base[GETARG_A(i)]))
#define RB(i) (lua_assert(GETARG_B(i) < L->top - base), (&base[GETARG_B(i)]))
#define RC(i) (lua_assert(GETARG_C(i) < L->top - base), (&base[GETARG_C(i)]))

/* Constant manipulation */
#define KD(i) (lua_assert(GETARG_D(i) < cl->p->sizek), (&k[GETARG_D(i)]))
#define KB(i) (lua_assert(GETARG_C(i) < cl->p->sizek), (&k[GETARG_C(i)]))
#define KC(i) (lua_assert(GETARG_C(i) < cl->p->sizek), (&k[GETARG_C(i)]))
#define K(i) (lua_assert((i) < (uint32_t)cl->p->sizek), (&k[i]))

static void callTMres(lua_State *L, StkId res, const TValue *f, const TValue *p1, const TValue *p2)
{
    ptrdiff_t result = savestack(L, res);
    setobj2s(L, L->top, f);      /* push function */
    setobj2s(L, L->top + 1, p1); /* 1st argument */
    setobj2s(L, L->top + 2, p2); /* 2nd argument */
    luaD_checkstack(L, 3);
    L->top += 3;
    luaD_call(L, L->top - 3, 1);
    res = restorestack(L, result);
    L->top--;
    setobjs2s(L, res, L->top);
}

static void callTM(lua_State *L, const TValue *f, const TValue *p1, const TValue *p2,
                   const TValue *p3)
{
    setobj2s(L, L->top, f);      /* push function */
    setobj2s(L, L->top + 1, p1); /* 1st argument */
    setobj2s(L, L->top + 2, p2); /* 2nd argument */
    setobj2s(L, L->top + 3, p3); /* 3th argument */
    luaD_checkstack(L, 4);
    L->top += 4;
    luaD_call(L, L->top - 4, 0);
}

static int call_binTM(lua_State *L, const TValue *p1, const TValue *p2, StkId res, TMS event)
{
    const TValue *tm = luaT_gettmbyobj(L, p1, event); /* try first operand */
    if (ttisnil(tm))
        tm = luaT_gettmbyobj(L, p2, event); /* try second operand */
    if (ttisnil(tm))
        return 0;
    callTMres(L, res, tm, p1, p2);
    return 1;
}

static const TValue *get_compTM(lua_State *L, Table *mt1, Table *mt2, TMS event)
{
    const TValue *tm1 = fasttm(L, mt1, event);
    const TValue *tm2;
    if (tm1 == NULL)
        return NULL; /* no metamethod */
    if (mt1 == mt2)
        return tm1; /* same metatables => same metamethods */
    tm2 = fasttm(L, mt2, event);
    if (tm2 == NULL)
        return NULL;                /* no metamethod */
    if (luaO_rawequalObj(tm1, tm2)) /* same metamethods? */
        return tm1;
    return NULL;
}

static int call_orderTM(lua_State *L, const TValue *p1, const TValue *p2, TMS event)
{
    const TValue *tm1 = luaT_gettmbyobj(L, p1, event);
    const TValue *tm2;
    if (ttisnil(tm1))
        return -1; /* no metamethod? */
    tm2 = luaT_gettmbyobj(L, p2, event);
    if (!luaO_rawequalObj(tm1, tm2)) /* different metamethods? */
        return -1;
    callTMres(L, L->top, tm1, p1, p2);
    return !l_isfalse(L->top);
}

void luapp_execute(lua_State *L, int nexeccalls)
{
    LClosure *cl;
    StkId base;
    TValue *k;
    const Instruction *pc;

    /* Entry point */
reentry:
    lua_assert(isLua(L->ci));
    pc = L->savedpc;
    cl = &clvalue(L->ci->func)->l;
    base = L->base;
    k = cl->p->k;

    /* Main loop for the vm */
    for (;;) {
        /* Prep instruction for execution */
        const Instruction i = *pc++;
        //printf("%s\n", opcode_names[GET_OPCODE(i)]);
        /* Handle each opcode */
        switch (GET_OPCODE(i)) {
            case OP_VARARGPREP: {
                /* TODO: #6 Remove stackprep from luaD_precall and move here. */
                continue;
            }
            case OP_MOVE: {
                setobjs2s(L, RA(i), RB(i));
                continue;
            }
            case OP_LOADK: {
                setobj2s(L, RA(i), KD(i));
                continue;
            }
            case OP_LOADKX: {
                /* Constant is stored in the sub instruction */
                const Instruction sub = *pc++;

                setobj2s(L, RA(i), K(sub));
                continue;
            }
            case OP_LOADBOOL: {
                setbvalue(RA(i), GETARG_B(i));

                if (GETARG_C(i))
                    pc++;
                continue;
            }
            case OP_LOADNN: {
                setnvalue(RA(i), -(double)(GETARG_Du(i)));
                continue;
            }
            case OP_LOADPN: {
                setnvalue(RA(i), (double)(GETARG_Du(i)));
                continue;
            }
            case OP_ADD: {
                ARITH(luai_numadd, TM_ADD);
                break;
            }
            case OP_SUB: {
                ARITH(luai_numsub, TM_SUB);
                break;
            }
            case OP_MUL: {
                ARITH(luai_nummul, TM_MUL);
                break;
            }
            case OP_DIV: {
                ARITH(luai_numdiv, TM_DIV);
                break;
            }
            case OP_POW: {
                ARITH(luai_numpow, TM_POW);
                break;
            }
            case OP_MOD: {
                ARITH(luai_nummod, TM_MOD);
                break;
            }
            case OP_ADDK: {
                ARITHK(luai_numadd, TM_ADD);
                break;
            }
            case OP_SUBK: {
                ARITHK(luai_numsub, TM_SUB);
                break;
            }
            case OP_MULK: {
                ARITHK(luai_nummul, TM_MUL);
                break;
            }
            case OP_DIVK: {
                ARITHK(luai_numdiv, TM_DIV);
                break;
            }
            case OP_POWK: {
                ARITHK(luai_numpow, TM_POW);
                break;
            }
            case OP_MODK: {
                ARITHK(luai_nummod, TM_MOD);
                break;
            }
            case OP_GETENV: {
                TValue *kv = KD(i);

                /* Make sure we were able to successfully retrieve the value from our environment */
                if (!ttisnil(kv))
                    setobj2s(L, RA(i), kv);
                continue;
            }
            case OP_CONCAT: {
                int32_t b = GETARG_B(i);
                int32_t c = GETARG_C(i);

                PROTECT(luaV_concat(L, c - b + 1, c); luaC_checkGC(L));

                setobjs2s(L, RA(i), base + b);
                continue;
            }
            case OP_CALL: {
                StkId ra = RA(i);

                /* Retrieve information from the instruction */
                int32_t nparams = GETARG_B(i) - 1;
                int32_t nresults = GETARG_C(i) - 1;

                if (nparams != LUA_MULTRET)
                    L->top = ra + 1 + nparams;

                L->savedpc = pc;
                switch (luaD_precall(L, ra, nresults)) {
                    case PCRLUA: {
                        nexeccalls++;
                        goto reentry; /* restart over new Lua function */
                    }
                    case PCRC: {
                        /* it was a C function (`precall' called it); adjust results */
                        if (nresults >= 0)
                            L->top = L->ci->top;
                        base = L->base;
                        continue;
                    }
                    default: {
                        return; /* yield */
                    }
                }
            }
            case OP_CLOSURE: {
                StkId ra = RA(i);

                Proto *pv = cl->p->p[GETARG_D(i)];
                lua_assert(GETARG_D(i) < cl->p->sizep);
                /* create new lua closure */
                Closure *ncl = luaF_newLclosure(L, pv->nups, cl->env);
                ncl->l.p = pv;

                setclvalue(L, ra, ncl);
                PROTECT(luaC_checkGC(L));
                continue;
            }
            case OP_NEJMP:
            case OP_EQJMP: {
                TValue *rb = RB(i);
                TValue *rc = RC(i);

                const Instruction sub = *pc++;
                int result;
                PROTECT(if (result = equalobj(L, rb, rc)) JUMP(L, pc, sub););

                setbvalue(RA(i), GET_OPCODE(i) == OP_NEJMP ? !result : result);
                continue;
            }
            case OP_LEJMP: {
                TValue *rb = RB(i);
                TValue *rc = RC(i);

                const Instruction sub = *pc++;
                int result;
                PROTECT(if (result = luaV_lessequal(L, rb, rc)) JUMP(L, pc, sub););

                setbvalue(RA(i), result);
                continue;
            }
            case OP_LTJMP: {
                TValue *rb = RB(i);
                TValue *rc = RC(i);

                const Instruction sub = *pc++;
                int result;
                PROTECT(if (result = luaV_lessthan(L, rb, rc)) JUMP(L, pc, sub););

                setbvalue(RA(i), result);
                continue;
            }
            case OP_JMPIF: {
                TValue *ra = RA(i);
                int16_t jmp = GETARG_D(i);

                PROTECT(if (bvalue(ra)) JUMP(L, pc, jmp););
                continue;
            }
            case OP_JMPIFNOT: {
                TValue *ra = RA(i);
                int16_t jmp = GETARG_D(i);

                PROTECT(if (!bvalue(ra)) JUMP(L, pc, jmp););
                continue;
            }
            case OP_JMPBACK: {
                PROTECT(JUMP(L, pc, GETARG_E(i)));
                continue;
            }
            case OP_NEWTABLE: {
                int32_t b = GETARG_B(i);
                int32_t c = GETARG_C(i);

                sethvalue(L, RA(i), luaH_new(L, luaO_fb2int(b), luaO_fb2int(c)));

                PROTECT(luaC_checkGC(L));
                continue;
            }
            case OP_SETLIST: {
                TValue *ra = RA(i);
                int32_t n = GETARG_B(i);
                int32_t c = GETARG_C(i);

                if (n == 0) {
                    n = cast_int(L->top - ra) - 1;
                    L->top = L->ci->top;
                }

                if (c == 0)
                    c = cast_int(*pc++);

                RUNTIME_CHECK(L, ttistable(ra));

                Table *h = hvalue(ra);
                int32_t last = ((c - 1) * LFIELDS_PER_FLUSH) + n;

                if (last > h->sizearray)          /* needs more space? */
                    luaH_resizearray(L, h, last); /* pre-alloc it at once */

                for (; n > 0; n--) {
                    TValue *val = ra + n;
                    setobj2t(L, luaH_setnum(L, h, last--), val);
                    luaC_barriert(L, h, val);
                }
                continue;
            }
            case OP_GETTABLEN: {
                TValue *ra = RA(i);
                TValue *rb = RB(i);
                int32_t val = GETARG_C(i) - 1;

                if (ttistable(rb)) {
                    Table *h = hvalue(rb);

                    /* Fast check: in allocated array memory space */
                    if (val < h->sizearray && !h->metatable) {
                        setobj2s(L, ra, &h->array[val]);
                        continue;
                    }
                }

                TValue n;
                setnvalue(&n, val + 1);
                PROTECT(luaV_gettable(L, rb, &n, ra));
                continue;
            }
            case OP_GETTABLE: {
                TValue *ra = RA(i);
                TValue *rb = RB(i);
                TValue *rc = RC(i);

                /* Fast path for arrays with preallocated memory space */
                if (ttistable(rb) && ttisnumber(rc)) {
                    Table *h = hvalue(rb);

                    const int32_t raw = (int32_t)nvalue(rc);
                    int32_t index = (raw < 0 ? h->sizearray + raw + 1 : raw);

                    if (index - 1 < h->sizearray && !h->metatable) {
                        setobj2s(L, ra, &h->array[index - 1]);
                        continue;
                    }

                    /* Out of bounds, update RC */
                    setnvalue(rc, index);
                }

                PROTECT(luaV_gettable(L, rb, rc, ra));
                continue;
            }
            case OP_SETTABLE: {
                TValue *ra = RA(i);
                TValue *rb = RB(i);
                TValue *rc = RC(i);

                /* Fast path for arrays with preallocated memory space */
                if (ttistable(ra) && ttisnumber(rb)) {
                    Table *h = hvalue(ra);
                    int32_t index = (int32_t)nvalue(rb) - 1;

                    if (index < h->sizearray && !h->metatable) {
                        setobj2s(L, &h->array[index], rc);
                        luaC_barriert(L, h, rc);
                        continue;
                    }
                }

                PROTECT(luaV_settable(L, ra, rb, rc));
                continue;
            }
            case OP_UNM: {
                TValue *ra = RA(i);
                TValue *rb = RB(i);

                if (ttisnumber(rb)) {
                    lua_Number nb = nvalue(rb);
                    setnvalue(ra, luai_numunm(nb));
                } else {
                    PROTECT(luaV_arith(L, ra, rb, rb, TM_UNM));
                }
                continue;
            }
            case OP_LEN: {
                TValue *ra = RA(i);
                TValue *rb = RB(i);

                if (ttistable(rb)) {
                    Table *h = hvalue(rb);

                    /* If it has no metamethod, invoke luaH_getn */
                    if (!fasttm(L, h->metatable, TM_LEN)) {
                        setnvalue(ra, cast_num(luaH_getn(hvalue(rb))));
                        continue;
                    }
                }
                /* If we have a string, get it's length */
                else if (ttisstring(rb)) {
                    TString *ts = rawtsvalue(rb);
                    setnvalue(ra, cast_num(ts->tsv.len));
                    continue;
                }

                PROTECT(call_binTM(L, rb, luaO_nilobject, ra, TM_LEN));
                continue;
            }
            case OP_NOT: {
                TValue *ra = RA(i);
                TValue *rb = RB(i);

                bool res = l_isfalse(rb);
                setbvalue(ra, res);
                continue;
            }
            case OP_RETURN:
                goto exit;
        }
    }
/* exit point */
exit:;
}