#ifndef _TYPE_H
#define _TYPE_H

#include <stdbool.h>
#include <stdio.h>

enum type_kind { TYPE_PRIMITIVE, TYPE_LIST, TYPE_CUSTOM };

/* Maybe add other types..? */
enum type_primitive_kind {
    TYPE_BASIC_NUMBER,
    TYPE_BASIC_STRING,
    TYPE_BASIC_BOOLEAN,
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
        struct {
            struct type *first; /* Primitive */
            struct type *next;  /* Primitive or List */
        } list;
    } data;
};

struct type *type_basic(enum type_primitive_kind kind);
struct type *type_list(struct type *first, struct type *next);

char *type_to_string(struct type *type);

#endif