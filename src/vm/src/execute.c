#define LUA_CORE
#include "lua/lgc.h"
#include "lua/lvm.h"

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
                /* Prepare the stack for any possible varargs */
                int32_t numparams = GETARG_A(i);

                /* Get more stack space as each argument is copied over */
                PROTECT(luaD_checkstack(L, cl->p->maxstacksize + numparams));

                lua_assert(cast_int(L->top - base) >= numparams);

                StkId fixed = base;
                base = L->top;

                for (int32_t i = 0; i < numparams; ++i)
                    setobj2s(L, base + i, fixed + i);
                setnilvalue(fixed + i);

                /* Rewire our stack frame to point to the new base */
                L->ci->base = base;
                L->ci->top = base + cl->p->maxstacksize;

                L->base = base;
                L->top = L->ci->top;
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

                /* empty sub instruction */
                const Instruction sub = *pc++;
                
                int result;
                PROTECT(if (result = equalobj(L, rb, rc)) JUMP(L, pc, sub););

                setbvalue(RA(i), GET_OPCODE(i) == OP_NEJMP ? !result : result);
                continue;
            }
            case OP_RETURN:
                goto exit;
        }
    }
/* exit point */
exit:
}