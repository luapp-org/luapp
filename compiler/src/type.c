#include "type.h"
#include "node.h"
#include "util/flexstr.h"

/* type_basic() -- creates a basic data type
 *      args: kind of data type
 *      returns: created type
 */
struct type *type_basic(enum type_primitive_kind kind)
{
    struct type *t;

    t = smalloc(sizeof(struct type));

    t->kind = TYPE_PRIMITIVE;
    t->data.primitive.kind = kind;

    return t;
}

/* type_list() -- creates a list data type (a list of primitives/customs)
 *      args: first type, next type
 *      returns: created type
 */
struct type *type_list(struct type *first, struct type *next)
{
    struct type *t;

    t = smalloc(sizeof(struct type));

    t->kind = TYPE_LIST;
    t->data.list.first = first;
    t->data.list.next = next;

    return t;
}

/* type_to_string() -- converts the given type scruct to a string representation
 *      args: type
 *      returns: string version of type
 */
char *type_to_string(struct type *type)
{
    flexstr_t s;
    
    fs_init(&s, 0);

    if (type->kind == TYPE_PRIMITIVE) {
        switch (type->data.primitive.kind) {
            case TYPE_BASIC_NUMBER:
                return "number";
            case TYPE_BASIC_STRING: 
                return "string";
            case TYPE_BASIC_BOOLEAN: 
                return "boolean";
        }
    } 
    // else if (type->kind == TYPE_LIST) {
    //     /* Make a big string */   
    //     for (struct type* t = type->data.list.first; t != NULL; t = type->data.list.next) {
    //         fs_addstr(&s, type_to_string(type));

    //         if (type->data.list.next != NULL)
    //             fs_addstr(&s, ", ");
    //     }

    //     return fs_getstr(&s);
    // }

    return "unknown";
}