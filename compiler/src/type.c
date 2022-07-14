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
            case TYPE_BASIC_ANY:
                return "any";
        }
    }

    return "unknown";
}

/* type_is() -- determines whether two types are equal
 *      args: first type, second type
 *      returns: yes or no
 */
bool type_is(struct type *first, struct type *second)
{
    return first->data.primitive.kind == second->data.primitive.kind;
}

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
                    compiler_error(
                        var->location,
                        "type mismatch: variable of type \"%s\" can not be assigned a value "
                        "of type \"%s\"",
                        type_to_string(var->node_type), type_to_string(expr->node_type));
                    context->error_count++;
                }
            }
        }
        break;
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

        case NODE_LOCAL:
            type_handle_local(context, node);
            break;
        case NODE_BLOCK:
            type_ast_traversal(context, node->data.block.init);
            type_ast_traversal(context, node->data.block.statement);
            break;
    }
}