#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "vm.h"

#define INITIAL_CAPACITY 16 /* Value can be anything, just not 0 */

#define FNV_OFFSET 14695981039346656037UL /* Offset used in hashfunc */
#define FNV_PRIME 1099511628211UL         /*  */

/* Create a new pair representation */
struct vm_pair *vm_pair(struct vm_value key, struct vm_value value)
{
    /* Mem alloc */
    struct vm_pair *pair = malloc(sizeof(struct vm_pair));
    assert(pair);

    pair->key = key;
    pair->value = value;

    return pair;
}

/* Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
 * https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
 */
static unsigned long hash_string(const char *string)
{
    unsigned long hash = FNV_OFFSET;

    /* Hash each character */
    for (const char *p = string; *p; p++) {
        hash ^= (unsigned long)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }

    return hash;
}

/* Get the index of a hashed value */
static size_t get_hash_index(struct vm_value value, size_t cap)
{
    switch (value.type) {
        case V_STRING: {
            unsigned long hash = hash_string(value.data.object->string);
            /* Hash with capacity - 1 to ensure it's within nodes array */
            return (size_t)(hash & (unsigned long)(cap - 1));
        }
    }

    return 0;
}

/* Create a new table representation */
struct vm_table *vm_table()
{
    /* Mem alloc */
    struct vm_table *table = malloc(sizeof(struct vm_table));
    assert(table);

    /* set default cap */

    table->cap = INITIAL_CAPACITY;
    table->size = 0;

    table->nodes = calloc(table->cap, sizeof(struct vm_pair *));

    /* Free the table before we return */
    if (!table->nodes) {
        free(table);
        return NULL;
    }

    return table;
}

struct vm_value *vm_table_get(struct vm_table *table, struct vm_value key)
{
    size_t index = get_hash_index(key, table->cap);

    /* Loop until we find an empty node (and return) */
    while (table->nodes[index]) {
        
        /* If we have the right key, return it's value */
        if (vm_value_is(key, table->nodes[index]->key))
            return &table->nodes[index]->value;

        /* Key wasn't in this slot, so move to the next one (linear probing) */
        if (++index >= table->cap)
            index = 0;
    }

    return NULL;
}

/* Expands a table to double it's current size */
bool expand(struct vm_table *table)
{
    const size_t new_cap = table->cap * 2;

    /* Overflow, capacity is too big */
    if (new_cap < table->cap)
        return false;

    table->nodes = realloc(table->nodes, new_cap * sizeof(struct vm_pair));
    assert(table->nodes);

    table->cap = new_cap;

    return true;
}

/* Updates or adds a node pair in the table */
void set_node(struct vm_table *table, struct vm_value key, struct vm_value value)
{
    size_t index = get_hash_index(key, table->cap);

    /* Loop until we find an empty node (set and return) */
    while (table->nodes[index]) {
        /* If we have the right key, return it's value */
        if (vm_value_is(key, table->nodes[index]->key)) {
            VM_SETOBJ(&table->nodes[index]->value, &value);
            return;
        }

        /* Key wasn't in this slot, so move to the next one (linear probing) */
        if (++index >= table->cap)
            index = 0;
    }

    table->nodes[index] = vm_pair(key, value);
}

void vm_table_add(struct vm_table *table, struct vm_value key, struct vm_value value)
{
    /* If the size exceeds half of the cap, expand the hashtable */
    if (table->size >= table->cap / 2)
        if (!expand(table))
            return;

    /* Set node */
    set_node(table, key, value);
}

/* Table destructor (called when gc is fired off) */
void vm_table_destroy(struct vm_table *table)
{
    /* Free each node individually */
    for (size_t i = 0; i < table->cap; ++i) 
        vm_pair_destroy(table->nodes[i]);

    free(table->nodes);
    free(table);
}

/* Pair destructor (called when gc is fired off) */
void vm_pair_destroy(struct vm_pair *pair) { free(pair); }

/* Value destructor (called when gc is fired off) */
void vm_value_destroy(struct vm_value *value)
{
    if (!value || !value->data.object)
        return;
    
    free(value->data.object);
}

/* Compares two vm_values and returns true if they are equal */
bool vm_value_is(struct vm_value first, struct vm_value second)
{
    /* Types must be of the same type */
    if (first.type != second.type)
        return false;

    switch (first.type) {
        case V_NUMBER:
            return first.data.number.value == second.data.number.value;
        case V_STRING:
            /* TODO: #3 */
            return !strcmp(first.data.object->string, second.data.object->string);
    }

    return false;
}

void lib_open(struct vm_context *context)
{
    context->env = vm_table();
    
    struct vm_value k;
    VM_SETSVALUE(&k, "stringgg");

    struct vm_value v;
    VM_SETSVALUE(&v, "val");

    vm_table_add(context->env, k, v);
}

void lib_close(struct vm_context *context)
{
    vm_table_destroy(context->env);
}