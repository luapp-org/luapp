#define LUA_CORE
#include "lua/lgc.h"
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
                    int32_t index = (raw < 0 ? h->sizearray + raw + 1: raw);

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
            case OP_RETURN:
                goto exit;
        }
    }
/* exit point */
exit:;
}