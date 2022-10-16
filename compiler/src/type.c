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

/* type_to_string() -- converts the given type struct to a string representation
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
            case TYPE_BASIC_VARARG:
                return "vararg";
            case TYPE_BASIC_NIL:
                return "nil";
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

/* type_node_is() -- determines whether two node type lists are equal
 *      args: first list, second list
 *      returns: yes or no
 */
bool type_node_is(struct node *first, struct node *second)
{
    while (true) {
        /* Both are still lists */
        if (first->type == NODE_TYPE_LIST && second->type == NODE_TYPE_LIST) {
            /* Check both types */
            if (!type_is(first->data.type_list.type->node_type,
                         second->data.type_list.type->node_type)) {
                return false;
            }

            first = first->data.type_list.init;
            second = second->data.type_list.init;
        }
        /* Both are not lists but not NULL */
        else if (first && second) {
            if (!type_is(first->node_type, second->node_type))
                return false;
            return true;
        } else
            return false;
    }
    return true;
}

/* type_is() -- determines whether two types are equal
 *      args: first type, second type
 *      returns: yes or no
 */
bool type_is(struct type *first, struct type *second)
{
    if (!first || !second)
        return false;

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
            case TYPE_FUNCTION:
                return type_node_is(first->data.function.args_list,
                                    second->data.function.args_list) &&
                       type_node_is(first->data.function.rets_list,
                                    second->data.function.rets_list);
            default:
                return false;
        }
    }
    return false;
}

static void type_add_name(map_t map, char *name, struct type *t)
{
    int res = hashmap_put(map, name, t);
    assert(res == MAP_OK);
}

void get_type(struct type_context *context, char *name, struct type **t, bool *is_global)
{
    if (hashmap_get(context->type_map, name, (void **)(*(&t))) == MAP_OK)
        *is_global = false;
    else if (hashmap_get(context->global_type_map, name, (void **)(*(&t))) == MAP_OK)
        *is_global = true;
    else
        *t = NULL;
}

bool type_name_exists(struct type_context *context, char *name)
{
    bool b;
    struct type *t;
    get_type(context, name, &t, &b);

    return t != NULL;
}

static void type_add(struct type_context *context, struct node *identifier, struct type *t)
{
    void *s;
    if (type_name_exists(context, identifier->data.identifier.name)) {
        compiler_error(identifier->location, "this variable has already been defined");
        hashmap_print(context->type_map);
        context->error_count++;
        return;
    }

    type_add_name(context->type_map, identifier->data.identifier.name, t);
}

/* type_init() -- initializes the type context by creating the type_map
 *      args: context
 *      returns: none
 */
void type_init(struct type_context *context)
{
    struct YYLTYPE loc;

    context->type_map = hashmap_new();
    context->global_type_map = hashmap_new();

    /* Todo add function calls! */
    type_add_name(context->global_type_map, "print",
                  type_function(node_type(loc, type_basic(TYPE_BASIC_VARARG)),
                                node_type(loc, type_basic(TYPE_BASIC_NIL))));
}

/* type_destroy() -- deallocates space for the type context
 *      args: context
 *      returns: none
 */
void type_destroy(struct type_context *context)
{
    hashmap_free(context->type_map);
    hashmap_free(context->global_type_map);
}

static void type_handle_local_assignment(struct type_context *context, struct node *name,
                                         struct node *expr)
{
    struct node *identifier;

    if (name && expr) {
        if (name->data.type_annotation.type->node_type == NULL) {
            free(name->node_type);
            name->node_type = expr->node_type;
            name->data.type_annotation.type->node_type = expr->node_type;
        } else if (name->type != NODE_TYPE_ANNOTATION) {
            free(name->node_type);
            name->node_type = expr->node_type;

            if (context->is_strict && name->type != NODE_TYPE_ANNOTATION) {
                compiler_error(name->location,
                               "expected type annotation; compiler is in \"strict\" mode");
                context->error_count++;
            }
        }

        identifier = name;
    } else if (name)
        identifier = name->data.type_annotation.identifier;

    if (name && expr) {
        if (!type_is(name->node_type, expr->node_type)) {
            if (name->node_type) {
                compiler_error(name->location,
                               "type mismatch: unable to assign variable with type \"%s\" a value "
                               "of type \"%s\"",
                               type_to_string(name->node_type), type_to_string(expr->node_type));
                context->error_count++;
            } else
                name->node_type = expr->node_type;
        }
        type_add(context, identifier, name->node_type);
    } else if (name) {
        if (context->is_strict) {
            compiler_error(name->location, "variable is inherently \"nil\"");
            context->error_count++;
        }
        free(name->node_type);
        name->node_type = type_basic(TYPE_BASIC_NIL);
        type_add(context, identifier, name->node_type);
    } else if (expr) {
        compiler_error(expr->location, "expression is not assigned to a variable");
        context->error_count++;
    }
}

static void type_handle_local(struct type_context *context, struct node *local)
{
    struct node *vars = local->data.local.namelist;
    struct node *values = local->data.local.exprlist;

    while (true) {

        /* Both are lists -> check first values of each */
        if ((vars && values) && vars->type == NODE_VARIABLE_LIST &&
            values->type == NODE_EXPRESSION_LIST) {

            type_handle_local_assignment(context, vars->data.name_list.name,
                                         values->data.expression_list.expression);

            vars = vars->data.name_list.init;
            values = values->data.expression_list.init;
        }
        /* first is list second is NULL -> continue first */
        else if ((vars) && vars->type == NODE_VARIABLE_LIST) {
            type_handle_local_assignment(context, vars->data.name_list.name, values);

            vars = vars->data.variable_list.init;
            values = NULL;
        }
        /* first is NULL second is list -> continue second */
        else if ((values) && values->type == NODE_EXPRESSION_LIST) {
            type_handle_local_assignment(context, vars, values->data.expression_list.expression);

            values = values->data.expression_list.init;
            vars = NULL;
        }
        /* Both are singular or NULL */
        else {
            type_handle_local_assignment(context, vars, values);
            return;
        }
    }
}

static void type_handle_name_reference(struct type_context *context, struct node *name_reference)
{
    struct node *value = name_reference->data.name_reference.identifier;
    struct node *expression, *index;
    struct type *t;
    bool res = false;
    bool types_equal;

    switch (value->type) {
        case NODE_IDENTIFIER:
            get_type(context, value->data.identifier.name, &t, &res);

            /* Ensure that this identifier exists in this context */
            if (!t && context->is_strict) {
                compiler_error(value->location, "\"%s\" is not defined in this context",
                               value->data.identifier.name);
                context->error_count++;

                /* If the identifier has been defined */
            } else if (t) {
                value->node_type = t;
                value->data.identifier.is_global = res;
                name_reference->node_type = t;
            }
            break;
        case NODE_EXPRESSION_INDEX:
            expression = value->data.expression_index.expression;
            index = value->data.expression_index.index;

            type_ast_traversal(context, expression, false);
            type_ast_traversal(context, index, false);

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
        case BINOP_GE:
        case BINOP_LE:
        case BINOP_GT:
        case BINOP_LT:
            if (!type_is(right->node_type, left->node_type)) {
                compiler_error(binary_operation->location,
                               "attempt to compare value of type \"%s\" with value of type \"%s\"",
                               type_to_string(right->node_type), type_to_string(left->node_type));
                context->error_count++;
            }
        case BINOP_CONCAT:
        case BINOP_EQ:
        case BINOP_NE:
            free(binary_operation->node_type);
            binary_operation->node_type =
                type_basic(binary_operation->data.binary_operation.operation == BINOP_CONCAT
                               ? TYPE_BASIC_STRING
                               : TYPE_BASIC_BOOLEAN);
            break;
        /* Lua has some weird 'and' and 'or' operations */
        case BINOP_AND:
        case BINOP_OR:
            free(binary_operation->node_type);
            binary_operation->node_type =
                binary_operation->data.binary_operation.operation == BINOP_AND ? right->node_type
                                                                               : left->node_type;
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
                    array_constructor->node_type = type_array(expr->node_type);
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

static void type_handle_numeric_for_loop(struct type_context *context, struct node *for_loop)
{
    struct node *init = for_loop->data.numerical_for_loop.init;
    const struct node *target = for_loop->data.numerical_for_loop.target;
    const struct node *increment = for_loop->data.numerical_for_loop.increment;

    /* We can assume that this is a single assignment due to lang grammar */
    struct node *var = init->data.assignment.variables;
    struct node *val = init->data.assignment.values;

    if (var->type == NODE_TYPE_ANNOTATION) {
        /* Check if types are equal */
        if (!type_is(var->node_type, val->node_type)) {
            compiler_error(
                init->location,
                "type mismatch: unable to assign variable or type \"%s\" a value of type \"%s\"",
                type_to_string(var->node_type), type_to_string(val->node_type));
            context->error_count++;
        }

        type_add(context, var->data.type_annotation.identifier, var->node_type);
        return;
    } else if (var->type == NODE_IDENTIFIER) {
        /* See if this identifier exists */

        struct type *t;

        if (!type_name_exists(context, var->data.identifier.name)) {
            if (context->is_strict) {
                compiler_error(var->location,
                               "expected type annotation; compiler is in \"strict\" mode");
                context->error_count++;
            }

            free(var->node_type);
            var->node_type = val->node_type;

            type_add(context, var, var->node_type);
        }

        return;
    }

    type_ast_traversal(context, init, false);

    /* Ensure that all types are numbers or else we have a problem! */
    if (!type_is_primitive(var->node_type, TYPE_BASIC_NUMBER)) {
        compiler_error(var->location, "'for' variable must be a \"number\"");
        context->error_count++;
    }

    if (!type_is_primitive(target->node_type, TYPE_BASIC_NUMBER)) {
        compiler_error(target->location, "'for' target value must be a \"number\"");
        context->error_count++;
    }

    if (!type_is_primitive(increment->node_type, TYPE_BASIC_NUMBER)) {
        compiler_error(increment->location, "'for' step must be a \"number\"");
        context->error_count++;
    }
}

static void type_handle_unary(struct type_context *context, struct node *unary)
{
    struct node *expr = unary->data.unary_operation.expression;

    switch (unary->data.unary_operation.operation) {
        case UNOP_LEN:
            /* expr can be array, table, or string */
            if (!(expr->node_type->kind == TYPE_ARRAY || expr->node_type->kind == TYPE_TABLE ||
                  type_is_primitive(expr->node_type, TYPE_BASIC_STRING))) {
                compiler_error(unary->location,
                               "unable to calculate length of value of \"%s\" type",
                               type_to_string(expr->node_type));
                context->error_count++;
            }

            free(unary->node_type);
            unary->node_type = expr->node_type;
            break;
        case UNOP_NEG:
            /* Can only be number */
            if (!type_is_primitive(expr->node_type, TYPE_BASIC_NUMBER)) {
                compiler_error(unary->location,
                               "unable to perform arithmetic on value of \"%s\" type",
                               type_to_string(expr->node_type));
                context->error_count++;
            }

            free(unary->node_type);
            unary->node_type = expr->node_type;
            break;
        case UNOP_NOT:
            free(unary->node_type);
            unary->node_type = type_basic(TYPE_BASIC_BOOLEAN);
            break;
    }
}

static struct node *type_build_type_list(struct type_context *context, struct node *namelist,
                                         struct node *vararg)
{
    struct node *t = NULL;

    if (namelist == NULL && vararg)
        return node_type(vararg->location, vararg->node_type);

    if (namelist->type == NODE_NAME_LIST)
        t = namelist->data.name_list.name;
    else
        t = namelist;

    if (t->type != NODE_TYPE_ANNOTATION && context->is_strict) {
        compiler_error(t->location, "expected type annotation; compiler is in \"strict\" mode %d",
                       t->type);
        context->error_count++;
    }

    if (namelist->type == NODE_NAME_LIST)
        return node_type_list(namelist->location,
                              type_build_type_list(context, namelist->data.name_list.init, vararg),
                              t);
    else {
        if (vararg)
            return node_type_list(namelist->location, t, vararg);
        else {
            return node_type(t->location, t->node_type);
        }
    }
}

static void type_handle_function_body(struct type_context *context, struct node *funcbody)
{
    struct node *typelist = funcbody->data.function_body.type_list;
    struct node *parameters = funcbody->data.function_body.exprlist;

    struct node *vararg = parameters->data.parameter_list.vararg;
    struct node *namelist = parameters->data.parameter_list.namelist;

    if (funcbody->node_type)
        free(funcbody->node_type);

    funcbody->node_type = type_function(type_build_type_list(context, namelist, vararg), typelist);

    while (true) {
        struct node *p = NULL;

        if (namelist == NULL)
            break;
        else if (namelist->type == NODE_NAME_LIST) {
            p = namelist->data.name_list.name;
        } else
            p = namelist;

        if (p->type != NODE_TYPE_ANNOTATION) {
            if (context->is_strict) {
                /* Scream */
                compiler_error(p->location,
                               "expected type annotation; compiler is in \"strict\" mode");
                context->error_count++;
            }
            type_add(context, p, p->node_type);
        } else
            type_add(context, p->data.type_annotation.identifier, p->node_type);

        if (namelist->type == NODE_NAME_LIST)
            namelist = namelist->data.name_list.init;
        else
            namelist = NULL;
    }
}

static void type_handle_single_call(struct type_context *context, struct node *arg,
                                    struct node *type, YYLTYPE location)
{
    if (arg && type) {
        if (!type_is(arg->node_type, type->node_type) &&
            !type_is_primitive(type->node_type, TYPE_BASIC_VARARG)) {
            compiler_error(arg->location,
                           "type mismatch: argument of type \"%s\" is incompatible with parameter "
                           "of argument \"%s\"",
                           type_to_string(arg->node_type), type_to_string(type->node_type));
            context->error_count++;
        }
    } else if (arg) {
        compiler_error(arg->location, "too many arguments in function call");
        context->error_count++;
    } else if (type && !type_is_primitive(type->node_type, TYPE_BASIC_VARARG)) {
        compiler_error(location, "too few arguments in function call");
        context->error_count++;
    }
}

static void type_handle_call(struct type_context *context, struct node *call)
{
    struct node *f = call->data.call.prefix_expression;
    struct node *args = call->data.call.args;

    if (f->node_type->kind != TYPE_FUNCTION) {
        compiler_error(f->location, "attempt to call a %s value", type_to_string(f->node_type));
        context->error_count++;
    } else {
        struct node *fargs = f->node_type->data.function.args_list;

        while (true) {
            if (args && fargs && args->type == NODE_EXPRESSION_LIST &&
                fargs->type == NODE_TYPE_LIST) {
                type_handle_single_call(context, args->data.expression_list.expression,
                                        fargs->data.type_list.type, call->location);

                args = args->data.expression_list.init;
                fargs = fargs->data.type_list.init;
            } else if (args && args->type == NODE_EXPRESSION_LIST) {
                type_handle_single_call(context, args->data.expression_list.expression, fargs,
                                        call->location);

                args = args->data.expression_list.init;

                if (fargs && !type_is_primitive(fargs->node_type, TYPE_BASIC_VARARG))
                    fargs = NULL;
            } else if (args && args->type == NODE_EXPRESSION_LIST) {
                type_handle_single_call(context, args, fargs->data.type_list.type, call->location);

                fargs = fargs->data.type_list.init;

                if (args && args->type != NODE_VARARG)
                    args = NULL;
            } else {
                type_handle_single_call(context, args, fargs, call->location);
                break;
            }
        }
    }
}

/* type_ast_traversal() -- traverses the AST and ensures that there are no type mismatches
 *      args: context, node, flag that determines whether to not copy the context.
 *      returns: none
 */
void type_ast_traversal(struct type_context *context, struct node *node, bool main)
{
    if (!node)
        return;

    int last_count;

    struct type_context new_context = {context->is_strict, context->error_count, NULL,
                                       context->global_type_map};

    switch (node->type) {
        case NODE_EXPRESSION_STATEMENT:
            type_ast_traversal(context, node->data.expression_statement.expression, false);
            break;
        case NODE_NAME_REFERENCE:
            type_ast_traversal(context, node->data.name_reference.identifier, false);

            type_handle_name_reference(context, node);
            break;
        case NODE_EXPRESSION_INDEX:
            type_ast_traversal(context, node->data.expression_index.expression, false);
            type_ast_traversal(context, node->data.expression_index.index, false);
            break;
        case NODE_LOCAL:
            /* Visit children */
            type_ast_traversal(context, node->data.local.namelist, false);
            type_ast_traversal(context, node->data.local.exprlist, false);
            /* Handle everything */
            type_handle_local(context, node);
            break;
        case NODE_ASSIGNMENT:
            type_ast_traversal(context, node->data.assignment.variables, false);
            type_ast_traversal(context, node->data.assignment.values, false);

            type_handle_assignment(context, node);
            break;
        case NODE_VARIABLE_LIST:
            type_ast_traversal(context, node->data.variable_list.init, false);
            type_ast_traversal(context, node->data.variable_list.variable, false);
            break;
        case NODE_ARRAY_CONSTRUCTOR:
            type_ast_traversal(context, node->data.array_constructor.exprlist, false);

            type_handle_array_constructor(context, node);
            break;
        case NODE_TABLE_CONSTRUCTOR:
            type_ast_traversal(context, node->data.table_constructor.pairlist, false);

            type_handle_table_constructor(context, node);
            break;
        case NODE_KEY_VALUE_PAIR:
            type_ast_traversal(context, node->data.key_value_pair.key, false);
            type_ast_traversal(context, node->data.key_value_pair.value, false);
            break;
        case NODE_BINARY_OPERATION:
            type_ast_traversal(context, node->data.binary_operation.left, false);
            type_ast_traversal(context, node->data.binary_operation.right, false);

            type_handle_binary_operation(context, node);
            break;
        case NODE_BLOCK:
            if (main) {
                type_ast_traversal(context, node->data.block.init, true);
                type_ast_traversal(context, node->data.block.statement, false);
            } else {
                new_context.type_map = hashmap_duplicate(context->type_map);

                type_ast_traversal(&new_context, node->data.block.init, true);
                type_ast_traversal(&new_context, node->data.block.statement, false);

                free(new_context.type_map);
                context->error_count = new_context.error_count;
            }
            break;
        case NODE_CALL:
            last_count = context->error_count;

            type_ast_traversal(context, node->data.call.args, false);
            type_ast_traversal(context, node->data.call.prefix_expression, false);

            if (context->error_count > last_count)
                break;

            /* Check if everything is legal */
            type_handle_call(context, node);
        case NODE_IF:
            type_ast_traversal(context, node->data.if_statement.condition, false);
            type_ast_traversal(context, node->data.if_statement.body, false);
            type_ast_traversal(context, node->data.if_statement.else_body, false);
            break;
        case NODE_REPEATLOOP:
            type_ast_traversal(context, node->data.repeat_loop.body,
                               true); // Variables defined in the body can be used in the condition.
            type_ast_traversal(context, node->data.repeat_loop.condition, false);
            break;
        case NODE_WHILELOOP:
            type_ast_traversal(context, node->data.while_loop.condition, false);
            type_ast_traversal(context, node->data.while_loop.body, false);
            break;
        case NODE_NUMERICFORLOOP:
            new_context.type_map = hashmap_duplicate(context->type_map);

            type_ast_traversal(&new_context, node->data.numerical_for_loop.increment, false);
            type_ast_traversal(&new_context, node->data.numerical_for_loop.target, false);

            type_handle_numeric_for_loop(&new_context, node);

            type_ast_traversal(&new_context, node->data.numerical_for_loop.body, true);

            free(new_context.type_map);
            context->error_count = new_context.error_count;
            break;
        case NODE_GENERICFORLOOP:
            /* Copy the old context (find better way to do this, the current way eats your ram) */
            new_context.type_map = hashmap_duplicate(context->type_map);

            type_ast_traversal(&new_context, node->data.generic_for_loop.local->data.local.namelist,
                               false);
            type_ast_traversal(&new_context, node->data.generic_for_loop.local->data.local.exprlist,
                               false);

            type_handle_generic_for_loop(&new_context, node->data.generic_for_loop.local);

            type_ast_traversal(&new_context, node->data.generic_for_loop.body, true);

            free(new_context.type_map);
            context->error_count = new_context.error_count;
            break;
        case NODE_UNARY_OPERATION:
            type_ast_traversal(context, node->data.unary_operation.expression, false);

            type_handle_unary(context, node);
            break;
        case NODE_FUNCTION_BODY:
            if (main)
                new_context.type_map = context->type_map;
            else
                new_context.type_map = hashmap_duplicate(context->type_map);

            type_ast_traversal(&new_context, node->data.function_body.exprlist, false);
            type_ast_traversal(&new_context, node->data.function_body.type_list, false);

            type_handle_function_body(&new_context, node);

            type_ast_traversal(&new_context, node->data.function_body.body, true);

            if (!main)
                free(new_context.type_map);

            context->error_count = new_context.error_count;
            break;
    }
}