#ifndef _IR_H
#define _IR_H

#include <stdbool.h>
#include <stdio.h>

#include "compiler.h"

/* Blind definitions */
struct node;
struct symbol;
struct symbol_table;

enum ir_opcode {
    IR_GETGLOBAL,
    IR_LOADI,
    IR_LOADK,
    IR_LOADKX,
    IR_CALL,
    IR_RETURN,
    IR_ARGPREP,
    IR_VARARGPREP,
    IR_CLOSURE
};

/* opcode_names -- array of opcode names that are used in ir.c */
static const char *const opcode_names[] = {"GETGLOBAL", "LOADI",   "LOADK",      "LOADKX", "CALL",
                                           "RETURN",    "ARGPREP", "VARARGPREP", "CLOSURE"};

enum ir_instruction_mode { iABC, iABx, iAsBx, SUB };

struct ir_instruction {
    union {
        unsigned int value;
        struct {
            enum ir_opcode op;
            unsigned char A;
            union {
                struct {
                    unsigned char B;
                    unsigned char C;
                };
                unsigned short Bx;
                short sBx;
            };
        };
    };

    enum ir_instruction_mode mode;
    struct ir_instruction *prev, *next;
};

struct ir_section {
    struct ir_instruction *first, *last;
    int size;
};

enum ir_constant_type { CONSTANT_STRING, CONSTANT_NUMBER };

struct ir_constant {
    enum ir_constant_type type;
    union {
        struct {
            unsigned int symbol_id;
        } string;
        struct {
            double value;
        } number;
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
    unsigned char parameters_size;
    bool is_vararg;
    unsigned char max_stack_size;
    struct ir_proto_list *protos;
    struct ir_constant_list *constant_list;
    struct ir_section *code;

    /* Variables used within the IR */
    unsigned char top_register;
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