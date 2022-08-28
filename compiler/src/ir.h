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
    IR_VARARGPREP
};

/* opcode_names -- array of opcode names that are used in ir.c */
static const char *const opcode_names[] = {"GETGLOBAL", "LOADI",  "LOADK",   "LOADKX",
                                           "CALL",      "RETURN", "ARGPREP", "VARARGPREP"};

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
};

struct ir_context {
    /* Variables the IR uses */
    int error_count;
    struct symbol_table *table;
    unsigned char top_register;

    /* What will be serialized into bytecode */
    struct ir_constant_list *constant_list;
    unsigned int constants;
    unsigned char stack_size;
};

struct ir_section *ir_build(struct ir_context *context, struct node *node, bool main);
void ir_init(struct ir_context *context);

void ir_print_context(FILE *output, struct ir_context *context);
void ir_print_section(FILE *output, struct ir_section *section);

#endif