#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "vm.h"

/* Macros we use for the VM execution */
#define VM_NEXT() goto dispatch;
#define VM_RESET() goto init_dispatch;

/* Retrieve the vm_value located at the given position on the stack */
#define VM_GETREG(arg)                                                                             \
    (assert(arg < (context->stack.top - context->stack.base)), &context->stack.base[arg])

/* Retrieve the constant located at the given position from the constant's array */
#define VM_GETK(arg) (assert(arg < p.sizek), &k[arg])

struct vm_stack vm_stack(int capacity)
{
    struct vm_stack s;

    /* Create new stack */
    s.stack = calloc(capacity, sizeof(struct vm_value));
    assert(s.stack);

    /* Init pointers */
    s.base = s.stack;
    s.top = s.top;

    return s;
}

void vm_execute(struct vm_context *context)
{
    struct vm_value *k;
    const vm_instruction *pc;
    struct vm_proto p = context->protos[0];

init_dispatch:
    /* Init all of the values needed to execute the current proto */
    context->stack = vm_stack(p.max_stack_size);
    k = p.constants;
    pc = p.code;
dispatch : {
    /* Run each instruction */
    unsigned int op = GETARG_OP(*pc);
    printf("OP: %u\n", op);
    switch (op) {
        case OP_LOADK: {
            vm_instruction instr = *pc++;

            /* Get the stack slot (ra) and constant reference (kv) */
            vm_register ra = VM_GETREG(GETARG_A(instr));
            struct vm_value *kv = VM_GETK(GETARG_Bx(instr));

            /* Load the constant into the register slot */
            VM_SETOBJ(ra, kv);
            VM_NEXT();
        }
        case OP_GETENV: {
            vm_instruction instr = *pc++;

            /* Get the stack slot (ra) and constant reference (kv) */
            vm_register ra = VM_GETREG(GETARG_A(instr));
            struct vm_value *kv = VM_GETK(GETARG_Bx(instr));

            if (kv->type != V_NIL)
                VM_SETOBJ(ra, kv);

            /* TODO: Add second arg (aux instruction) which will contain the index of the string
             * constants. Will be useful if this opcode is used on an environment member that is
             * added at runtime. */

            VM_NEXT();
        }
        case OP_CALL: {
            vm_instruction instr = *pc++;

            /* Get the stack slot (ra) */
            vm_register ra = VM_GETREG(GETARG_A(instr));
            
            /* Get the number of parameters and results */
            int parameters = GETARG_B(instr) - 1;
            int results = GETARG_C(instr) - 1;

            /* Update the stack frame */
            context->stack.base = ra + 1;
            context->stack.top = ra + parameters + 1;

            struct vm_closure *closure = ra->data.object->closure;

            /* Determine the type of closure and handle it */
            if (closure->is_c) {
                /* Get the function and call it */
                int ret = closure->c.function(context);

                if (ret < 0)
                    goto exit;
            }

            VM_NEXT();
        }
        case OP_VARARGPREP: {
            *pc++;
            /* TODO: Resize the stack for the amount of parameters passed. This instruction is only
             * really needed for lua functions, not for main function. */
            VM_NEXT();
        }
    }
}
exit:;
}