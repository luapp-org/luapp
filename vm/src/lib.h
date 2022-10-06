#ifndef _LIB_H
#define _LIB_H

#include <stdio.h>
#include <stdbool.h>

/* vm_constant_type - the type of value */
enum vm_value_type { V_STRING, V_NUMBER, V_FUNCTION };

/* vm_value - represents a data structure in the VM. These are on the stack or constants that can be
 * loaded from p->k */
struct vm_value {
    /* value type */
    enum vm_value_type type;

    /* data union */
    union {
        struct {
            char *value;
        } string;
        struct {
            double value;
        } number;
        struct {

        } function;
    } data;
};

/* Set a vm value to a string. Used during execution and lifting. */
#define VM_SETSVALUE(obj, x)                                                                       \
    {                                                                                              \
        struct vm_value *v = (obj);                                                                \
        v->type = V_STRING;                                                                        \
        v->data.string.value = x;                                                                  \
    }

/* Set a vm value to a number. Used during execution and lifting. */
#define VM_SETNVALUE(obj, x)                                                                       \
    {                                                                                              \
        struct vm_value *v = (obj);                                                                \
        v->type = V_NUMBER;                                                                        \
        v->data.number.value = x;                                                                  \
    }

/* vm_pair - a pair consisting of a key and a value. Found in tables */
struct vm_pair {
    /* key and value */
    struct vm_value *key, *value;
};

/* vm_table - represents a Lua++ table in the VM */
struct vm_table {
    /* table properties */
    size_t size;
    size_t cap;

    /* table children */
    struct vm_pair *nodes;
};

struct vm_table *vm_table();
void vm_table_destroy(struct vm_table *table);

struct vm_pair *vm_pair(struct vm_value *key, struct vm_value *value);
void vm_pair_destroy(struct vm_pair *pair);

bool vm_value_is(struct vm_value *first, struct vm_value *second);
void vm_value_destroy(struct vm_value *value);

#endif