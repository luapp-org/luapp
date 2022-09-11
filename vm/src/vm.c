#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "vm.h"

/* Macros we use for the VM execution */
#define VM_NEXT() goto dispatch;
#define VM_RESET() goto init_dispatch;

/* Retrieve the vm_value located at the given position on the stack */
#define VM_GETREG(arg) (assert(arg < p.max_stack_size), &stack[arg])

/* Retrieve the constant located at the given position from the constant's array */
#define VM_GETCON(arg) (assert(arg < p.sizek), &k[arg])

struct vm_value *vm_stack(int size)
{
    /* Create new stack */
    struct vm_value *stack = malloc(size * sizeof(struct vm_value *));
    assert(stack);

    return stack;
}

void vm_execute(struct vm_context *context)
{
    struct vm_value *stack, *k;
    const vm_instruction *pc;
    struct vm_proto p = *context->protos;

init_dispatch:
    /* Init all of the values needed to execute the current proto */
    stack = vm_stack(p.max_stack_size);
    k = p.constants;
    pc = p.code;

dispatch:
    /* Run each instruction */
    unsigned int op = GETARG_OP(*pc);

    switch (op) {
        case OP_LOADK: {
            vm_instruction instr = *pc++;

            /* Get the stack slot (ra) and constant reference (kv) */
            vm_register ra = VM_GETREG(GETARG_A(instr));
            const struct vm_value *kv = VM_GETCON(GETARG_Bx(instr));

            /* Load the constant into the register slot */
            *ra = *kv;
            VM_NEXT();
        }
    }
}