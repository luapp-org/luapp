/*
 *  symbol.h
 *
 *  Usually, symbol tables are constructed before the type checker is launched. In this compiler,
 *  symbols are a little different than ones you may find in a traditional symbol table. Since Lua++
 *  bytecode actually contains a list of constants used within the codebase, the symbol traversal
 *  should simply just find constants and store them so that you could just throw them at the IR pass
 *  and be done.
 */

#ifndef _SYMBOL_H
#define _SYMBOL_H

#include <stdio.h>

#include "compiler.h"
struct node;
struct type;

unsigned int nextSymbolId;

struct symbol {
    char *name;
    unsigned int id;
};

struct symbol_list {
    struct symbol symbol;
    struct symbol_list *next, *prev;
};

struct symbol_table {
    struct symbol_list *first, *last;
    unsigned int size;
};

struct symbol_context {
    struct symbol_table *table;
    int error_count;
};

void symbol_initialize_table(struct symbol_table *table);
void symbol_table_destroy(struct symbol_table *table);

void symbol_ast_traversal(struct symbol_context *context, struct node *node);
void symbol_print_table(FILE *output, struct symbol_table *table);

#endif