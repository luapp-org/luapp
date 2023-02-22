#ifndef _IR_H
#define _IR_H

#include <stdbool.h>
#include <stdio.h>

#include "compiler.h"
#include "util/hashmap.h"

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

struct ir_constant {
    constant_t type;
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
        struct {
            int size;
            uint32_t *indicies;
        } array;
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

    uint32_t proto_size;
    uint32_t protos[BUFSIZ];

    struct ir_constant_list *constant_list;
    struct ir_section *code;

    /* Variables used within the IR */
    uint8_t top_register;
    int32_t target_register;
    bool mult_ret;
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
    struct ir_proto_list *protos;

    /* IR 'local' register map */
    map_t local_map;
};

void ir_init(struct ir_context *context);
void ir_destroy(struct ir_context *context);

void ir_print_context(FILE *output, struct ir_context *context);
struct ir_proto_list *ir_build(struct ir_context *context, struct node *node);
struct ir_proto *ir_build_proto(struct ir_context *context, struct ir_proto *proto,
                                struct node *node);

#endif