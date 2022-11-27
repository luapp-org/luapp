#ifndef _IR_H
#define _IR_H

#include <stdbool.h>
#include <stdio.h>

#include "compiler.h"
#include "../../opcodes.h"

/* Blind definitions */
struct node;
struct symbol;
struct symbol_table;

struct ir_instruction {
    uint32_t value;

    enum opcode_mode mode;
    struct ir_instruction *prev, *next;
};

struct ir_section {
    struct ir_instruction *first, *last;
    int size;
};

enum ir_constant_type { CONSTANT_STRING, CONSTANT_NUMBER, CONSTANT_ENV };

struct ir_constant {
    enum ir_constant_type type;
    union {
        struct {
            uint32_t symbol_id;
        } symbol;
        struct {
            double value;
        } number;
        struct {
            uint32_t index;
        } env;
    } data;

    struct ir_constant *prev, *next;
};

struct ir_constant_list {
    struct ir_constant *first, *last;
    int size;
};

struct ir_proto_list;

/* IR function prototypes */
struct ir_proto {
    /* Information variables */
    uint8_t max_stack_size;
    uint8_t parameters_size;
    uint8_t upvalues_size;
    bool is_vararg;

    struct ir_proto_list *protos;
    struct ir_constant_list *constant_list;
    struct ir_section *code;

    /* Variables used within the IR */
    uint8_t top_register;
    struct ir_proto *prev, *next;
};

struct ir_proto_list {
    struct ir_proto *first, *last;
    int size;
};

struct ir_context {
    /* Variables the IR uses */
    int error_count;

    /* What will be serialized */
    struct symbol_table *table;
    struct ir_proto *main_proto;
};

struct ir_proto *ir_build(struct ir_context *context, struct node *node);
void ir_init(struct ir_context *context);

void ir_print_context(FILE *output, struct ir_context *context);
struct ir_proto_list *ir_collect_protos(struct ir_proto *main);

#endif