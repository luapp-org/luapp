#ifndef _VM_H
#define _VM_H

#include <stdbool.h>

/* vm_constant_type - the type of constant */
enum vm_constant_type { CONSTANT_STRING, CONSTANT_NUMBER };

/* vm_constant - represents a constant within the program (similar to IR constant) */
struct vm_constant {
    /* constant type */
    enum vm_constant_type type;

    /* data union */
    union {
        struct {
            unsigned int symbol_id;
        } string;
        struct {
            double value;
        } number;
    } data;
};

/* vm_proto - represents a function in the VM (similar to IR proto) */
struct vm_proto {
    /* function properties */
    unsigned char parameters_size;
    bool is_vararg;
    unsigned char max_stack_size;

    /* individual instructions for the function */
    unsigned int *code;

    /* array of constants used within the program */
    struct vm_constant *constants;
};

/* vm_context - carries all of the important data for the VM */
struct vm_context {
    /* string table */
    char **strings;

    /* all functions in the program */
    struct vm_proto *protos;
};

#endif