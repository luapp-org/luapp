#include <assert.h>

#include "node.h"
#include "type.h"
#include "util/flexstr.h"

#define KEY_MAX_LENGTH (256)
#define KEY_COUNT (1024 * 1024)

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

/* type_table() -- creates a table type
 *      args: array type
 *      returns: created array
 */
struct type *type_table(struct type *key, struct type *value)
{
    struct type *t;

    t = smalloc(sizeof(struct type));

    t->kind = TYPE_TABLE;
    t->data.table.key = key;
    t->data.table.value = value;

    return t;
}

/* type_function() -- creates a function type
 *      args: args type list, rets type list
 *      returns: function type
 */
struct type *type_function(struct node *args_list, struct node *rets_list)
{
    struct type *t;

    t = smalloc(sizeof(struct type));

    t->kind = TYPE_FUNCTION;
    t->data.function.args_list = args_list;
    t->data.function.rets_list = rets_list;

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
        }
    } else if (type->kind == TYPE_ARRAY) {
        sprintf(buf, "Array<%s>", type_to_string(type->data.array.type));
        return strdup(buf); // Free this somehow, I have no idea
    } else if (type->kind == TYPE_TABLE) {
        sprintf(buf, "Table<%s, %s>", type_to_string(type->data.table.key),
                type_to_string(type->data.table.value));
        return strdup(buf); // Free this somehow, I have no idea
    } else if (type->kind == TYPE_FUNCTION) {
        flexstr_t str;
        fs_init(&str, 0);

        fs_addstr(&str, "Function(");
        fs_addstr(&str, node_to_string(type->data.function.args_list));
        fs_addstr(&str, "): ");
        fs_addstr(&str, node_to_string(type->data.function.rets_list));

        return fs_getstr(&str);
    }

    return "unknown";
}

/* type_is_primitive() -- determines whether a type is the given primitive type
 *      args: type, primitive type
 *      returns: yes or no
 */
bool type_is_primitive(struct type *type, enum type_primitive_kind kind)
{
    return type->kind == TYPE_PRIMITIVE && type->data.primitive.kind == kind;
}

/* type_is() -- determines whether two types are equal
 *      args: first type, second type
 *      returns: yes or no
 */
bool type_is(struct type *first, struct type *second)
{
    /* If either options are ANY then return true */
    if (type_is_primitive(first, TYPE_BASIC_ANY) || type_is_primitive(second, TYPE_BASIC_ANY))
        return true;

    if (first->kind == second->kind) {
        switch (first->kind) {
            case TYPE_PRIMITIVE:
                return first->data.primitive.kind == second->data.primitive.kind;
            case TYPE_ARRAY:
                return type_is(first->data.array.type, second->data.array.type);
            case TYPE_TABLE:
                return type_is(first->data.table.key, second->data.table.key) &&
                       type_is(first->data.table.value, second->data.table.value);
            default:
                return false;
        }
    }
    return false;
}

void type_add(struct type_context *context, struct node *identifier, struct type *t)
{
    void *s;
    if (hashmap_get(context->type_map, identifier->data.identifier.name, &s) == MAP_OK) {
        compiler_error(identifier->location, "this variable has already been defined");
        context->error_count++;
        return;
    }

    int res = hashmap_put(context->type_map, identifier->data.identifier.name, t);
    assert(res == MAP_OK);
}

/* type_init() -- initializes the type context by creating the type_map
 *      args: context
 *      returns: none
 */
void type_init(struct type_context *context) { context->type_map = hashmap_new(); }

/* type_destroy() -- deallocates space for the type context
 *      args: context
 *      returns: none
 */
void type_destroy(struct type_context *context) { hashmap_free(context->type_map); }

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
            if (name->type != NODE_TYPE_ANNOTATION) {
                if (context->is_strict) {
                    compiler_error(name->location,
                                   "expected type annotation; compiler is in \"strict\" mode");
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
            if (name->type != NODE_TYPE_ANNOTATION) {
                if (context->is_strict) {
                    compiler_error(var->location,
                                   "expected type annotation; compiler is in \"strict\" mode");
                    context->error_count++;
                }

                if (expr)
                    name->node_type = expr->node_type;
                else
                    name->node_type = type_basic(TYPE_BASIC_NIL);
            }

            if (!expr && context->is_strict) {
                compiler_error(name->location, "local variable is inherently \"nil\"");
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
            if (type_is_primitive(var->node_type, TYPE_BASIC_ANY)) {
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
    struct node *expression, *index;
    struct type *s;
    int res = 0;
    bool types_equal;

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
            expression = value->data.expression_index.expression;
            index = value->data.expression_index.index;

            type_ast_traversal(context, expression);
            type_ast_traversal(context, index);

            switch (expression->node_type->kind) {
                case TYPE_PRIMITIVE:
                    compiler_error(expression->location,
                                   "incorrect type usage: unable to index type \"%s\"",
                                   type_to_string(expression->node_type));
                    context->error_count++;
                    break;
                case TYPE_TABLE:
                case TYPE_ARRAY:
                    types_equal =
                        expression->node_type->kind == TYPE_ARRAY
                            ? type_is_primitive(index->node_type, TYPE_BASIC_NUMBER)
                            : type_is(index->node_type, expression->node_type->data.table.key);

                    if (!types_equal) {
                        compiler_error(
                            expression->location,
                            "incorrect type usage: unable to index type \"%s\" with type \"%s\"",
                            type_to_string(expression->node_type),
                            type_to_string(index->node_type));
                        context->error_count++;
                    }
                    free(name_reference->node_type);
                    name_reference->node_type = expression->node_type->kind == TYPE_ARRAY
                                                    ? expression->node_type->data.array.type
                                                    : expression->node_type->data.table.value;
                    break;
            }
            break;
        case NODE_NAME_INDEX:
            /* later, for classes */
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
        case BINOP_SUB:
        case BINOP_MUL:
        case BINOP_DIV:
        case BINOP_MOD:
        case BINOP_POW:
            /* Free the default type assigned */
            free(binary_operation->node_type);

            if (!type_is_primitive(right->node_type, TYPE_BASIC_NUMBER) ||
                !type_is_primitive(left->node_type, TYPE_BASIC_NUMBER)) {
                compiler_error(binary_operation->location,
                               "unable to perform '%c' on values of type \"%s\" and \"%s\"",
                               binary_operations[binary_operation->data.binary_operation.operation],
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
                        free(array_constructor->node_type);
                        array_constructor->node_type = type_array(type_basic(TYPE_BASIC_ANY));
                        return;
                    }
                } else
                    type = expr->data.expression_list.expression->node_type;

                expr = expr->data.expression_list.init;
                break;
            default:
                free(array_constructor->node_type);
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

static void type_handle_table_constructor(struct type_context *context,
                                          struct node *table_constructor)
{
    struct node *expr = table_constructor->data.table_constructor.pairlist;
    struct type *keytype = NULL;
    struct type *valuetype = NULL;
    struct node *pair = NULL;

    while (true) {
        switch (expr->type) {
            case NODE_EXPRESSION_LIST:
                pair = expr->data.expression_list.expression;

                if (keytype && valuetype) {
                    if (!type_is(pair->data.key_value_pair.key->node_type, keytype)) {
                        free(keytype);
                        keytype = type_basic(TYPE_BASIC_ANY);
                    }
                    if (!type_is(pair->data.key_value_pair.value->node_type, valuetype)) {
                        free(valuetype);
                        valuetype = type_basic(TYPE_BASIC_ANY);
                    }
                } else {
                    keytype = pair->data.key_value_pair.key->node_type;
                    valuetype = pair->data.key_value_pair.value->node_type;
                }

                expr = expr->data.expression_list.init;
                break;
            default:
                if (keytype && valuetype) {
                    // Free existing type, as we will override it
                    free(table_constructor->node_type);

                    if (!type_is(expr->data.key_value_pair.key->node_type, keytype)) {
                        free(keytype);
                        keytype = type_basic(TYPE_BASIC_ANY);
                    }
                    if (!type_is(expr->data.key_value_pair.value->node_type, valuetype)) {
                        free(valuetype);
                        valuetype = type_basic(TYPE_BASIC_ANY);
                    }
                    table_constructor->node_type = type_table(keytype, valuetype);
                } else {
                    // Free existing type, as we will override it
                    free(table_constructor->node_type);

                    table_constructor->node_type =
                        type_table(expr->data.key_value_pair.key->node_type,
                                   expr->data.key_value_pair.value->node_type);
                }
                return;
        }
    }
}

static void type_handle_single_assignment(struct type_context *context, struct node *variable,
                                          struct node *value)
{
    if (variable && value) {
        if (!type_is(variable->node_type, value->node_type)) {
            compiler_error(
                variable->location,
                "type mismatch: unable to assign variable with type \"%s\" a value of type \"%s\"",
                type_to_string(variable->node_type), type_to_string(value->node_type));
            context->error_count++;
        }
    } else if (variable && context->is_strict) {
        compiler_error(variable->location, "variable is inherently \"nil\"");
        context->error_count++;
    } else if (value) {
        compiler_error(value->location, "expression is not assigned to a variable");
        context->error_count++;
    }
}

static void type_handle_assignment(struct type_context *context, struct node *assignment)
{
    struct node *vars = assignment->data.assignment.variables;
    struct node *values = assignment->data.assignment.values;

    while (true) {

        /* Both are lists -> check first values of each */
        if ((vars && values) && vars->type == NODE_VARIABLE_LIST &&
            values->type == NODE_EXPRESSION_LIST) {

            type_handle_single_assignment(context, vars->data.variable_list.variable,
                                          values->data.expression_list.expression);

            vars = vars->data.variable_list.init;
            values = values->data.expression_list.init;
        }
        /* first is list second is NULL -> continue first */
        else if ((vars) && vars->type == NODE_VARIABLE_LIST) {
            type_handle_single_assignment(context, vars->data.variable_list.variable, values);

            vars = vars->data.variable_list.init;
            values = NULL;
        }
        /* first is NULL second is list -> continue second */
        else if ((values) && values->type == NODE_EXPRESSION_LIST) {
            type_handle_single_assignment(context, vars, values->data.expression_list.expression);

            values = values->data.expression_list.init;
            vars = NULL;
        }
        /* Both are singular or NULL */
        else {
            type_handle_single_assignment(context, vars, values);
            return;
        }
    }
}

static void type_handle_generic_for_assign(struct type_context *context, struct node *variable,
                                           struct node *value)
{
    if (variable->type != NODE_TYPE_ANNOTATION) {
        if (context->is_strict) {
            compiler_error(variable->location,
                           "expected type annotation; compiler is in \"strict\" mode");
            context->error_count++;
        } else {
            type_add(context, variable->data.type_annotation.identifier, variable->node_type);
        }
    } else
        type_add(context, variable, variable->node_type);

    if (variable && value) {
        struct type *t = NULL;

        /* Determine what type we have */
        switch (value->node_type->kind) {
            case TYPE_ARRAY:
                t = value->node_type->data.array.type;
                break;
            default:
                compiler_error(variable->location, "unable to iterate \"%s\"",
                               type_to_string(value->node_type));
                context->error_count++;
                return;
        }
        if (!type_is(variable->node_type, t)) {
            compiler_error(variable->location,
                           "type mismatch: unable to iterate \"%s\" with \"%s\"",
                           type_to_string(variable->node_type), type_to_string(value->node_type));
            context->error_count++;
        }
    } else if (variable && context->is_strict) {
        compiler_error(variable->location, "variable is inherently \"nil\"");
        context->error_count++;
    } else if (value) {
        compiler_error(value->location, "expression is not assigned to a variable");
        context->error_count++;
    }
}

static void type_handle_generic_for_loop(struct type_context *context, struct node *local)
{
    struct node *vars = local->data.local.namelist;
    struct node *values = local->data.local.exprlist;

    while (true) {
        /* Both are lists -> check first values of each */
        if ((vars && values) && vars->type == NODE_VARIABLE_LIST &&
            values->type == NODE_EXPRESSION_LIST) {

            type_handle_generic_for_assign(context, vars->data.variable_list.variable,
                                           values->data.expression_list.expression);

            vars = vars->data.variable_list.init;
            values = values->data.expression_list.init;
        }
        /* first is list second is NULL -> continue first */
        else if ((vars) && vars->type == NODE_VARIABLE_LIST) {
            type_handle_generic_for_assign(context, vars->data.variable_list.variable, values);

            vars = vars->data.variable_list.init;
            values = NULL;
        }
        /* first is NULL second is list -> continue second */
        else if ((values) && values->type == NODE_EXPRESSION_LIST) {
            type_handle_generic_for_assign(context, vars, values->data.expression_list.expression);

            values = values->data.expression_list.init;
            vars = NULL;
        }
        /* Both are singular or NULL */
        else {
            type_handle_generic_for_assign(context, vars, values);
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

    struct type_context new_context = {true, 0};
    
    switch (node->type) {
        case NODE_EXPRESSION_STATEMENT:
            type_ast_traversal(context, node->data.expression_statement.expression);
            break;
        case NODE_NAME_REFERENCE:
            type_ast_traversal(context, node->data.name_reference.identifier);

            type_handle_name_reference(context, node);
            break;
        case NODE_EXPRESSION_INDEX:
            type_ast_traversal(context, node->data.expression_index.expression);
            type_ast_traversal(context, node->data.expression_index.index);
            break;
        case NODE_LOCAL:
            /* Visit children */
            type_ast_traversal(context, node->data.local.namelist);
            type_ast_traversal(context, node->data.local.exprlist);

            /* Handle everything */
            type_handle_local(context, node);
            break;
        case NODE_ASSIGNMENT:
            type_ast_traversal(context, node->data.assignment.variables);
            type_ast_traversal(context, node->data.assignment.values);

            type_handle_assignment(context, node);
            break;
        case NODE_VARIABLE_LIST:
            type_ast_traversal(context, node->data.variable_list.init);
            type_ast_traversal(context, node->data.variable_list.variable);
            break;
        case NODE_ARRAY_CONSTRUCTOR:
            type_ast_traversal(context, node->data.array_constructor.exprlist);

            type_handle_array_constructor(context, node);
            break;
        case NODE_TABLE_CONSTRUCTOR:
            type_ast_traversal(context, node->data.table_constructor.pairlist);

            type_handle_table_constructor(context, node);
            break;
        case NODE_KEY_VALUE_PAIR:
            type_ast_traversal(context, node->data.key_value_pair.key);
            type_ast_traversal(context, node->data.key_value_pair.value);
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
        case NODE_GENERICFORLOOP:
            //printf("Size before = %d\n", hashmap_length(context->type_map));
            /* Copy the old context */
            new_context.type_map = hashmap_duplicate(context->type_map);
        
            //printf("Size of new map = %d\n", hashmap_length(new_context.type_map));

            type_ast_traversal(&new_context, node->data.generic_for_loop.local->data.local.namelist);
            type_ast_traversal(&new_context, node->data.generic_for_loop.local->data.local.exprlist);

            type_handle_generic_for_loop(&new_context, node->data.generic_for_loop.local);

            type_ast_traversal(&new_context, node->data.generic_for_loop.body);
            //printf("Size after = %d\n", hashmap_length(context->type_map));
            free(new_context.type_map);
            break;
    }
}