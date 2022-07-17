#include <assert.h>

#include "node.h"
#include "type.h"
#include "util/flexstr.h"

#define KEY_MAX_LENGTH (256)
#define KEY_COUNT (1024 * 1024)

struct data_struct {
    struct type *type; /* Type of the identifier (when defined) */
};

// struct data_struct *create_data_entry(char *name, struct type *type)
// {
//     assert(strlen(name) < KEY_MAX_LENGTH);

//     struct data_struct *data = smalloc(sizeof(struct data_struct));
//     snprintf(data->key, KEY_MAX_LENGTH, "%s", name);
//     data->type = type;

//     return data;
// }

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

/* type_array() -- creates an array data type
 *      args: array type
 *      returns: created array
 */
struct type *type_array(struct type *type)
{
    struct type *t;

    t = smalloc(sizeof(struct type));

    t->kind = TYPE_ARRAY;
    t->data.array.type = type;

    return t;
}

/* type_to_string() -- converts the given type scruct to a string representation
 *      args: type
 *      returns: string version of type
 */
char *type_to_string(struct type *type)
{
    static char buf[BUFSIZ];
    bzero(buf, BUFSIZ); /* buffer needs to be empty */

    if (type->kind == TYPE_PRIMITIVE) {
        switch (type->data.primitive.kind) {
            case TYPE_BASIC_NUMBER:
                return "number";
            case TYPE_BASIC_STRING:
                return "string";
            case TYPE_BASIC_BOOLEAN:
                return "boolean";
            case TYPE_BASIC_ANY:
                return "any";
            case TYPE_BASIC_FUNCTION:
                return "function";
        }
    } else if (type->kind == TYPE_ARRAY) {
        sprintf(buf, "Array<%s>", type_to_string(type->data.array.type));
        return strdup(buf); // Free this somehow, I have no idea
    }

    return "unknown";
}

/* type_is() -- determines whether two types are equal
 *      args: first type, second type
 *      returns: yes or no
 */
bool type_is(struct type *first, struct type *second)
{
    if (first->kind == second->kind) {
        switch (first->kind) {
            case TYPE_PRIMITIVE:
                return first->data.primitive.kind == second->data.primitive.kind;
            case TYPE_ARRAY:
                return type_is(first->data.array.type, second->data.array.type);
            default:
                return false;
        }
    }
    return false;
}

/* type_init() -- initializes the type context by creating the type_map
 *      args: context
 *      returns: none
 */
void type_init(struct type_context *context)
{
    context->type_map = hashmap_new();

    /* Add all environment identifiers */
    hashmap_put(context->type_map, "print", type_basic(TYPE_BASIC_FUNCTION));
}

/* type_destroy() -- deallocates space for the type context
 *      args: context
 *      returns: none
 */
void type_destroy(struct type_context *context) { hashmap_free(context); }

static void type_handle_local(struct type_context *context, struct node *local)
{
    struct node *var = local->data.local.namelist;
    struct node *expr = local->data.local.exprlist;

    while (true) {
        /* We must have a name list and expression list, handle that. */
        if (expr && var->type == NODE_NAME_LIST && expr->type == NODE_EXPRESSION_LIST) {
            struct node *name = var->data.name_list.name;
            struct node *value = expr->data.expression_list.expression;

            /* Guess the type if no type is specified */
            if (type_is(name->node_type, type_basic(TYPE_BASIC_ANY))) {
                if (context->is_strict) {
                    compiler_error(name->location,
                                   "expected type annotation; compiler is in \"strict\" mode.");
                    context->error_count++;
                }

                name->node_type = value->node_type;
            }

            if (!type_is(name->node_type, value->node_type)) {
                compiler_error(name->location,
                               "type mismatch: variable of type \"%s\" can not be assigned a value "
                               "of type \"%s\"",
                               type_to_string(name->node_type), type_to_string(value->node_type));
                context->error_count++;
            }

            int res = hashmap_put(context->type_map,
                                  name->data.type_annotation.identifier->data.identifier.name,
                                  name->node_type);
            assert(res == MAP_OK);

            var = var->data.name_list.init;
            expr = expr->data.expression_list.init;
            continue;
            /* We have a singular namelist = expression */
        } else if (var->type == NODE_NAME_LIST) {
            struct node *name = var->data.name_list.name;

            /* Guess the type if no type is specified */
            if (type_is(name->node_type, type_basic(TYPE_BASIC_ANY))) {
                if (context->is_strict) {
                    compiler_error(var->location,
                                   "expected type annotation; compiler is in \"strict\" mode.");
                    context->error_count++;
                }

                if (expr)
                    name->node_type = expr->node_type;
                else
                    name->node_type = type_basic(TYPE_BASIC_NIL);
            }

            if (!expr && context->is_strict) {
                compiler_error(name->location, "local variable is inherently \"nil\".");
                context->error_count++;
            } else if (expr) {
                if (!type_is(name->node_type, expr->node_type)) {
                    compiler_error(
                        name->location,
                        "type mismatch: variable of type \"%s\" can not be assigned a value "
                        "of type \"%s\"",
                        type_to_string(name->node_type), type_to_string(expr->node_type));
                    context->error_count++;
                }
            }

            int res = hashmap_put(context->type_map,
                                  name->data.type_annotation.identifier->data.identifier.name,
                                  name->node_type);
            assert(res == MAP_OK);

            var = var->data.name_list.init;
            expr = NULL;
            continue;
            /* We must have a single assignment, handle that. */
        } else {
            /* Guess the type if no type is specified */
            if (type_is(var->node_type, type_basic(TYPE_BASIC_ANY))) {
                if (context->is_strict) {
                    compiler_error(var->location,
                                   "expected type annotation; compiler is in \"strict\" mode.");
                    context->error_count++;
                }

                if (expr)
                    var->node_type = expr->node_type;
                else
                    var->node_type = type_basic(TYPE_BASIC_NIL);
            }

            if (expr == NULL && context->is_strict) {
                compiler_error(var->location, "local variable is inherently \"nil\".");
                context->error_count++;
            } else if (expr) {
                if (!type_is(var->node_type, expr->node_type)) {
                    char *varstr = type_to_string(var->node_type);
                    char *exprstr = type_to_string(expr->node_type);

                    compiler_error(var->location,
                                   "type mismatch: variable of type \"%s\" can not be assigned a "
                                   "value of type \"%s\"",
                                   varstr, exprstr);
                    context->error_count++;
                }
            }
            int res = hashmap_put(context->type_map,
                                  var->data.type_annotation.identifier->data.identifier.name,
                                  var->node_type);
            assert(res == MAP_OK);
        }
        break;
    }
}

static void type_handle_name_reference(struct type_context *context, struct node *name_reference)
{
    struct node *value = name_reference->data.name_reference.identifier;
    struct type *s;
    int res = 0;

    switch (value->type) {
        case NODE_IDENTIFIER:
            res = hashmap_get(context->type_map, value->data.identifier.name, (void **)(&s));

            /* Ensure that this identifier exists in this context */
            if (res == MAP_MISSING && context->is_strict) {
                compiler_error(value->location, "\"%s\" is not defined in this context",
                               value->data.identifier.name);
                context->error_count++;

                /* If the identifier has been defined */
            } else if (res == MAP_OK) {
                value->node_type = s;
                name_reference->node_type = s;
            }
            break;
        case NODE_EXPRESSION_INDEX:
            /* code */
            break;
        case NODE_NAME_INDEX:
            /* code */
            break;
    }
}

static void type_handle_binary_operation(struct type_context *context,
                                         struct node *binary_operation)
{
    struct node *right = binary_operation->data.binary_operation.right;
    struct node *left = binary_operation->data.binary_operation.left;

    switch (binary_operation->data.binary_operation.operation) {
        case BINOP_ADD:
            if (!type_is(right->node_type, type_basic(TYPE_BASIC_NUMBER)) ||
                !type_is(left->node_type, type_basic(TYPE_BASIC_NUMBER))) {
                compiler_error(binary_operation->location,
                               "unable to perform '+' on values of type \"%s\" and \"%s\"",
                               type_to_string(right->node_type), type_to_string(left->node_type));
                context->error_count++;
            } else {
                binary_operation->node_type = type_basic(TYPE_BASIC_NUMBER);
            }
            break;
    }
}

static void type_handle_array_constructor(struct type_context *context,
                                          struct node *array_constructor)
{
    struct node *expr = array_constructor->data.array_constructor.exprlist;
    struct type *type = NULL;

    while (true) {
        switch (expr->type) {
            case NODE_EXPRESSION_LIST:
                if (type) {
                    if (!type_is(expr->data.expression_list.expression->node_type, type)) {
                        array_constructor->node_type = type_array(type_basic(TYPE_BASIC_ANY));
                        return;
                    }
                } else
                    type = expr->data.expression_list.expression->node_type;

                expr = expr->data.expression_list.init;
                break;
            default:
                if (type) {
                    if (!type_is(expr->node_type, type)) {
                        array_constructor->node_type = type_array(type_basic(TYPE_BASIC_ANY));
                        return;
                    }
                    array_constructor->node_type = type_array(type);
                } else
                    array_constructor->node_type =
                        type_array(expr->data.expression_list.expression->node_type);
                return;
        }
    }
}

/* type_ast_traversal() -- traverses the AST and ensures that there are no type mismatches
 *      args: context, node
 *      returns: none
 */
void type_ast_traversal(struct type_context *context, struct node *node)
{
    if (!node)
        return;

    switch (node->type) {
        case NODE_EXPRESSION_STATEMENT:
            type_ast_traversal(context, node->data.expression_statement.expression);
            break;
        case NODE_NAME_REFERENCE:
            type_handle_name_reference(context, node);
            break;
        case NODE_LOCAL:
            /* Visit children */
            type_ast_traversal(context, node->data.local.namelist);
            type_ast_traversal(context, node->data.local.exprlist);

            /* Handle everything */
            type_handle_local(context, node);
            break;
        case NODE_ARRAY_CONSTRUCTOR:
            type_ast_traversal(context, node->data.array_constructor.exprlist);

            type_handle_array_constructor(context, node);

            break;
        case NODE_BINARY_OPERATION:
            type_ast_traversal(context, node->data.binary_operation.left);
            type_ast_traversal(context, node->data.binary_operation.right);

            type_handle_binary_operation(context, node);
            break;
        case NODE_BLOCK:
            type_ast_traversal(context, node->data.block.init);
            type_ast_traversal(context, node->data.block.statement);
            break;
    }
}