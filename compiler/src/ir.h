#ifndef _IR_H
#define _IR_H

#include <stdbool.h>
#include <stdio.h>

#include "compiler.h"

/* Blind definitions */
struct node;
struct symbol;
struct symbol_table;

enum ir_operand_type { OPERAND_A, OPERAND_B, OPERAND_C };

struct ir_operand {
    enum ir_operand_type type;
    int location;
    union {
        int A;
        unsigned short B;
        short C;
    } data;
};

enum ir_opcode { IR_GETGLOBAL, IR_LOADI, IR_LOADK, IR_LOADKX, IR_CALL, IR_RETURN, IR_VARARGPREP };

struct ir_instruction {
    enum ir_opcode op;
    struct ir_operand operands[3];
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
            char *value;
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
    unsigned char top_register;

    /* What will be serialized into bytecode */
    struct symbol_table *table;
    struct ir_constant_list *list;
    unsigned char stack_size;
};

struct ir_section *ir_build(struct ir_context *context, struct node *node);

#endif