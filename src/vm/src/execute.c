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

/* Register manipulation */
#define RA(i) (lua_assert(GETARG_A(i) < L->top - base), (&base[GETARG_A(i)]))
#define RB(i) (lua_assert(GETARG_B(i) < L->top - base), (&base[GETARG_B(i)]))
#define RC(i) (lua_assert(GETARG_C(i) < L->top - base), (&base[GETARG_C(i)]))

/* Constant manipulation */
#define KD(i) (lua_assert(GETARG_D(i) < cl->p->sizek), (&k[GETARG_D(i)]))
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
            case OP_LOADNN: {
                setnvalue(RA(i), -(double)(GETARG_Du(i)));
                continue;
            }
            case OP_LOADPN: {
                setnvalue(RA(i), (double)(GETARG_Du(i)));
                continue;
            }
            case OP_GETENV: {
                TValue *kv = KD(i);

                /* Make sure we were able to successfully retrieve the value from our environment */
                if (!ttisnil(kv))
                    setobj2s(L, RA(i), kv);
                continue;
            }
            case OP_CALL: {
                StkId ra = RA(i);

                /* Retrieve information from the instruction */
                int32_t nparams = GETARG_B(i) - 1;
                int32_t nresults = GETARG_C(i) - 1;

                if (nparams == LUA_MULTRET)
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
            case OP_RETURN:
                goto exit;
        }
    }
/* exit point */
exit:
}