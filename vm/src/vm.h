#ifndef _VM_H
#define _VM_H

#include <stdbool.h>

typedef unsigned int vm_instruction;

/* vm_opcodes - operation codes for the instructions */
enum vm_opcodes {
    OP_GETGLOBAL,
    OP_LOADI,
    OP_LOADK,
    OP_LOADKX,
    OP_CALL,
    OP_RETURN,
    OP_ARGPREP,
    OP_VARARGPREP,
    OP_CLOSURE
};

/* Retrieves the operation for a Lua++ instruction. This section acts almost as a header for the
 * following 32 bit instruction. */
#define GETARG_OP(instruction) (instruction & 0xFF);

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

/* vm_constant_type - the type of value */
enum vm_value_type { V_STRING, V_NUMBER };

/* vm_value - represents a data structure in the VM. These are on the stack or constants that can be
 * loaded from p->k */
struct vm_value {
    /* value type */
    enum vm_value_type type;

    /* data union */
    union {
        struct {
            char *value;
        } string;
        struct {
            double value;
        } number;
    } data;
};

/* Represents a slot on the stack (register) */
typedef struct vm_value *vm_register;

/* vm_proto - represents a function in the VM (similar to IR proto) */
struct vm_proto {
    /* function properties */
    unsigned char parameters_size;
    bool is_vararg;
    unsigned char max_stack_size;

    /* individual instructions for the function */
    vm_instruction *code;

    /* array of values used within the program */
    struct vm_value *constants;
    int sizek;
};

/* vm_context - carries all of the important data for the VM */
struct vm_context {
    /* string table */
    char **strings;

    /* all functions in the program */
    struct vm_proto *protos;

    /* error count */
    int error_count;
};

void vm_execute(struct vm_context *context);

#endif