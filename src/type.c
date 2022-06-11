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

/* type_to_string() -- converts the given type scruct to a string representation
 *      args: type
 *      returns: string version of type
 */
char *type_to_string(struct type *type)
{
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

    return "unknown";
}