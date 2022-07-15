#ifndef _TYPE_H
#define _TYPE_H

#include <stdbool.h>
#include <stdio.h>

#include "util/hashmap.h"

struct node;

enum type_kind { TYPE_PRIMITIVE, TYPE_CUSTOM };

/* Maybe add other types..? */
enum type_primitive_kind {
    TYPE_BASIC_NUMBER,
    TYPE_BASIC_STRING,
    TYPE_BASIC_BOOLEAN,
    TYPE_BASIC_NIL,
    TYPE_BASIC_ANY,
    TYPE_BASIC_FUNCTION,
    TYPE_BASIC_TABLE,
    TYPE_BASIC_ARRAY
};

struct type {
    enum type_kind kind;

    /* Data stored below */
    union {
        struct {
            /* Kind of basic data type */
            enum type_primitive_kind kind;
        } primitive;
    } data;
};

struct type_context {
    bool is_strict;  /* Strict context flag */
    int error_count; /* Number of errors */

    map_t type_map; /* Hashmap of all identifiers and types */
};

void type_init(struct type_context *context);
void type_destroy(struct type_context *context);

struct type *type_basic(enum type_primitive_kind kind);
bool type_is(struct type *first, struct type *second);
void type_ast_traversal(struct type_context *context, struct node *node);

char *type_to_string(struct type *type);

#endif