#ifndef _LIB_H
#define _LIB_H

#include <stdbool.h>
#include <stdio.h>

struct vm_context;

/* vm_constant_type - the type of value */
enum vm_value_type { V_NIL, V_STRING, V_NUMBER, V_FUNCTION };

/* cfunction - represenation of a C function in the VM */
typedef int (*cfunction)(struct vm_context *);

/* vm_object - all objects that have required memory from the heap. The GC will collect and free all
 * of these objects. */
struct vm_object {
    char *string;
    struct vm_closure *closure;
};

/* vm_value - represents a data structure in the VM. These are on the stack or constants that can be
 * loaded from p->k */
struct vm_value {
    /* value type */
    enum vm_value_type type;

    /* data union */
    union {
        struct {
            double value;
        } number;

        struct vm_object *object;
    } data;
};

struct vm_closure {
    /* Current closure is C closure */
    bool is_c;

    /* Data union */
    union {
        /* Information about the built in C function */
        struct {
            cfunction function;
        } c;

        /* Info about the lua function */
        struct {
            struct vm_proto *proto;
        } lua;
    };
};

/* Set a vm value to a string. Used during execution and lifting. */
#define VM_SETSVALUE(obj, x)                                                                       \
    {                                                                                              \
        struct vm_value *z = (obj);                                                                \
        z->type = V_STRING;                                                                        \
        z->data.object = (struct vm_object *)x;                                                    \
    }

/* Set a vm value to a number. Used during execution and lifting. */
#define VM_SETNVALUE(obj, x)                                                                       \
    {                                                                                              \
        struct vm_value *z = (obj);                                                                \
        z->type = V_NUMBER;                                                                        \
        z->data.number.value = x;                                                                  \
    }

/* Set a vm value to another vm value. Used during execution and lifting. */
#define VM_SETOBJ(obj1, obj2)                                                                      \
    {                                                                                              \
        const struct vm_value *o2 = (obj2);                                                        \
        struct vm_value *o1 = (obj1);                                                              \
        *o1 = *o2;                                                                                 \
    }

/* Set value to nil */
#define VM_SETNIL(obj) ((obj)->type = V_NIL)

/* vm_pair - a pair consisting of a key and a value. Found in tables */
struct vm_pair {
    /* key and value */
    struct vm_value key, value;
};

/* vm_table - represents a Lua++ table in the VM */
struct vm_table {
    /* table properties */
    size_t size;
    size_t cap;

    /* table children */
    struct vm_pair **nodes;
};

void lib_open(struct vm_context *context);
void lib_close(struct vm_context *context);

struct vm_table *vm_table();
struct vm_value *vm_table_get(struct vm_table *table, struct vm_value key);
void vm_table_destroy(struct vm_table *table);

struct vm_pair *vm_pair(struct vm_value key, struct vm_value value);
void vm_pair_destroy(struct vm_pair *pair);

bool vm_value_is(struct vm_value first, struct vm_value second);
void vm_value_destroy(struct vm_value *value);

#endif