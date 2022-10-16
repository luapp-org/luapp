#ifndef _VM_H
#define _VM_H

#include <stdbool.h>

struct vm_table;
struct vm_value;

typedef unsigned int vm_instruction;

/* vm_opcodes - operation codes for the instructions */
enum vm_opcodes {
    OP_GETENV,
    OP_LOADI,
    OP_LOADK,
    OP_LOADKX,
    OP_CALL,
    OP_RETURN,
    OP_VARARGPREP,
    OP_CLOSURE
};

/* Retrieves the operation for a Lua++ instruction. This section acts almost as a header for the
 * following 32 bit instruction. */
#define GETARG_OP(instruction) ((instruction)&0xFF);

/* This is the ABC encoding. It consists of three 8-bit values that usually point to a register or a
 * really small number. */
#define GETARG_A(instruction) ((instruction >> 8) & 0xFF)
#define GETARG_B(instruction) ((instruction >> 16) & 0xFF)
#define GETARG_C(instruction) ((instruction >> 24) & 0xFF)

/* The ABx encoding. It consists of two values, one 8-bit and one signed 16-bit value. Usually used
 * for loading larger values onto the stack. */
#define GETARG_Bx(instruction) (((int)instruction >> 16))

/* Finally the sAx encoding. It consists of one signed 24-bit value used for instructions that
 * require one very large argument. */
#define GETARG_sAx(instruction) (((int)instruction >> 16))

/* Represents a slot on the stack (register) */
typedef struct vm_value *vm_register;

/* vm_proto - represents a function in the VM (similar to IR proto) */
struct vm_proto {
    /* Function properties */
    unsigned char parameters_size;
    bool is_vararg;
    unsigned char max_stack_size;

    /* Individual instructions for the function */
    vm_instruction *code;

    /* Array of values used within the program */
    struct vm_value *constants;
    int sizek;
};

/* vm_stack - represents a stack of vm_values in the VM */
struct vm_stack {
    /* Total amout of items in the stack array */
    int size;
    /* The capacity of the stack (how many slots exist in the array) */
    int capacity;

    /* Pointers to sections on the stack */
    struct vm_value *top;  /* First empty register on the stack */
    struct vm_value *base; /* Base register */

    /* The stack itself */
    struct vm_value *stack;
};

/* vm_context - carries all of the important data for the VM */
struct vm_context {
    /* String table */
    char **strings;

    /* Environment table */
    struct vm_table *env;

    /* All functions in the program */
    struct vm_proto *protos;

    /* Stack for the current program */
    struct vm_stack stack;

    /* Error count */
    int error_count;
};

void vm_execute(struct vm_context *context);

#endif