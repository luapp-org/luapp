#ifndef _IR_H
#define _IR_H

#include <stdbool.h>
#include <stdio.h>

/* Blind definitions */
struct node;
struct symbol;
struct symbol_table;

enum ir_operand_type { OPERAND_REGULAR, OPERAND_LARGE };

struct ir_operand {
    enum ir_operand_type type;

    union {
        int regular;
        double large;
    } data;
};

enum ir_opcode {

};

struct ir_instruction {
    enum ir_opcode op;
    ir_operand operands[3];
    struct ir_instruction *prev, *next;
};

struct ir_section {
    struct ir_instruction *first, *last;
};

struct ir_context {
    int error_count;
    struct symbol_table *table;
};

void ir_build(struct ir_context *context, struct node *node);

#endif