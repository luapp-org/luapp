/*  node.c - only version
 *       methods that construct the tree
 */

#include "node.h"
#include "type.h"
#include "util/flexstr.h"

/* Used for graphviz */
static int parent_id = 0;
static int id = 0;

/*  node_create - allocate and initialize a generic node
 *      args: location, node type
 *      rets: allocated node
 */
static struct node *node_create(YYLTYPE location, enum node_type type)
{
    struct node *node;

    node = malloc(sizeof(struct node));
    /* Ensure that we were able to allocate a new node */
    assert(node != NULL);

    /* Assign the member vars of node struct */
    node->type = type;
    node->location = location;
    node->node_type = type_basic(TYPE_BASIC_ANY);

    return node;
}

/*  node_number - allocate a node to represent an number
 *      args: location, value as string
 *      rets: number node
 */
struct node *node_number(YYLTYPE location, char *value)
{
    struct node *node = node_create(location, NODE_NUMBER);
    char *end;

    /* Convert value to a double and store _endptr in end */
    node->data.number.value = strtod(value, &end);

    /* Check for hexadecimal and convert to unsigned long in base 16 if so */
    if (*end == 'x' || *end == 'X')
        node->data.number.value = strtoul(value, &end, 16);

    node->data.number.overflow = *end == 0 ? false : true;
    node->node_type = type_basic(TYPE_BASIC_NUMBER);

    return node;
}

/*  node_identifier - allocate a node to represent an identifier
 *      args: location, name of identifier, length of name
 *      rets: identifier node
 */
struct node *node_identifier(YYLTYPE location, char *value)
{
    struct node *node = node_create(location, NODE_IDENTIFIER);

    /* Set the name by appending all of the characters in value */
    node->data.identifier.name = strdup(value);

    return node;
}

/*  node_string - allocate a node to represent a string
 *      args: location, name of identifier, length of name
 *      rets: string node
 */
struct node *node_string(YYLTYPE location, char *value)
{
    struct node *node = node_create(location, NODE_STRING);
    flexstr_t f;

    /* Initialize the string */
    fs_init(&f, 0);

    for (int i = 0; value[i] != '\0'; i++) {
        /* Is regular character? */
        if (value[i] != '\\') {
            fs_addch(&f, value[i]);
            continue;
        }
        i++;
        /* Handle all escape sequences */
        switch (value[i]) {
            case 't':
                fs_addch(&f, '\t');
                break;
            case 'n':
                fs_addch(&f, '\n');
                break;
            case 'a':
                fs_addch(&f, '\a');
                break;
            case 'b':
                fs_addch(&f, '\b');
                break;
            case 'f':
                fs_addch(&f, '\f');
                break;
            case 'r':
                fs_addch(&f, '\r');
                break;
            case 'v':
                fs_addch(&f, '\v');
                break;
            case '\\':
                fs_addch(&f, '\\');
                break;
        }
    }

    /* Set the name by appending all of the characters in value */
    node->data.string.value = fs_getstr(&f);
    node->node_type = type_basic(TYPE_BASIC_STRING);

    return node;
}

/*  node_boolean - allocate a node to represent a boolean
 *      args: location, value
 *      rets: boolean node
 */
struct node *node_boolean(YYLTYPE location, bool value)
{
    struct node *node = node_create(location, NODE_BOOLEAN);

    node->data.boolean.value = value;
    node->node_type = type_basic(TYPE_BASIC_BOOLEAN);

    return node;
}

/*  node_nil - allocate a node to represent a nil value
 *      args: location, value
 *      rets: boolean node
 */
struct node *node_nil(YYLTYPE location)
{
    struct node *node = node_create(location, NODE_NIL);

    node->node_type = type_basic(TYPE_BASIC_NIL);

    return node;
}

/*  node_nil - allocate a node to represent a type annotation
 *      args: location, identifier, type
 *      rets: type annotation node
 */
struct node *node_type_annotation(YYLTYPE location, struct node *identifier, struct node *type)
{
    struct node *node = node_create(location, NODE_TYPE_ANNOTATION);

    node->data.type_annotation.identifier = identifier;
    node->data.type_annotation.type = type;
    node->node_type = type->node_type;

    return node;
}

/*  node_type_list - allocate a node to represent a type list
 *      args: location, initial list, type
 *      rets: type list node
 */
struct node *node_type_list(YYLTYPE location, struct node *init, struct node *type)
{
    struct node *node = node_create(location, NODE_TYPE_LIST);

    node->data.type_list.init = init;
    node->data.type_list.type = type;

    return node;
}

/*  node_type - allocate a node to represent a type node
 *      args: location, type
 *      rets: type node
 */
struct node *node_type(YYLTYPE location, struct type *type)
{
    struct node *node = node_create(location, NODE_TYPE);

    node->node_type = type;

    return node;
}

/*  node_type_array - allocate a node to represent an array type node
 *      args: location, type
 *      rets: array type node
 */
struct node *node_type_array(YYLTYPE location, struct node *type)
{
    struct node *node = node_create(location, NODE_TYPE_ARRAY);

    node->node_type = type_array(type->node_type);

    return node;
}

/*  node_type_array - allocate a node to represent an array type node
 *      args: location, type
 *      rets: array type node
 */
struct node *node_type_table(YYLTYPE location, struct node *left, struct node *right)
{
    struct node *node = node_create(location, NODE_TYPE_TABLE);

    node->node_type = type_table(left->node_type, right->node_type);

    return node;
}

/*  node_type_function - allocate a node to represent a function type
 *      args: location, type args, return args
 *      rets: function type node
 */
struct node *node_type_function(YYLTYPE location, struct node *args, struct node *rets)
{
    struct node *node = node_create(location, NODE_TYPE_FUNCTION);

    node->node_type = type_function(args, rets);

    return node;
}

/*  node_binary_operation - allocate a node to represent a binary operation
 *      args: location, operation, left operand, right operand
 *      rets: binary operation node
 *
 *  BNF -> `+´ | `-´ | `*´ | `/´ | `^´ | `%´ | `..´ |
 *	 `<´ | `<=´ | `>´ | `>=´ | `==´ | `~=´ |
 *	 and | or
 */
struct node *node_binary_operation(YYLTYPE location, enum node_binary_operation operation,
                                   struct node *left, struct node *right)
{
    struct node *node = node_create(location, NODE_BINARY_OPERATION);

    node->data.binary_operation.operation = operation;
    node->data.binary_operation.left = left;
    node->data.binary_operation.right = right;

    return node;
}

/*  node_unary_operation - allocate a node to represent a unary operation
 *      args: location, operation, operand
 *      rets: unary operation node
 *
 *  BNF -> `-´ | not | `#´
 */
struct node *node_unary_operation(YYLTYPE location, enum node_unary_operation operation,
                                  struct node *expression)
{
    struct node *node = node_create(location, NODE_UNARY_OPERATION);

    node->data.unary_operation.operation = operation;
    node->data.unary_operation.expression = expression;

    return node;
}

/*  node_expression_list - allocate a node to represent an expression list
 *      args: location, first expression, next expression
 *      rets: expression list node
 *
 *  BNF -> {exp `,´} exp
 */
struct node *node_expression_list(YYLTYPE location, struct node *init, struct node *expression)
{
    struct node *node = node_create(location, NODE_EXPRESSION_LIST);

    node->data.expression_list.init = init;
    node->data.expression_list.expression = expression;

    return node;
}

/*  node_name_list - allocate a node to represent a name list
 *      args: location, first name, next name (if any)
 *      rets: name list node
 *
 *  BNF -> Name {`,´ Name}
 */
struct node *node_name_list(YYLTYPE location, struct node *init, struct node *name)
{
    struct node *node = node_create(location, NODE_NAME_LIST);

    node->data.name_list.init = init;
    node->data.name_list.name = name;

    return node;
}

/*  node_variable_list - allocate a node to represent an variable list
 *      args: location, first variable, next variable
 *      rets: variable list node
 *
 *  BNF -> var {`,´ var}
 */
struct node *node_variable_list(YYLTYPE location, struct node *init, struct node *variable)
{
    struct node *node = node_create(location, NODE_VARIABLE_LIST);

    node->data.variable_list.init = init;
    node->data.variable_list.variable = variable;

    return node;
}

/*  node_call - allocate a node to represent a call (function or constructor)
 *      args: location, prefix expression, arguments, self call
 *      rets: call node
 *
 *  BNF -> prefixexp args | prefixexp `:´ Name args
 */
struct node *node_call(YYLTYPE location, struct node *prefix_expression, struct node *args,
                       bool self_call)
{
    struct node *node = node_create(location, NODE_CALL);

    /* NOTE: call arguments will always be an expression list */
    node->data.call.prefix_expression = prefix_expression;
    node->data.call.args = args;

    return node;
}

/*  node_expression_group - allocate a node to represent an expression group
 *      args: location, expression in group
 *      rets: expression group node
 *
 *  BNF -> `(´ exp `)´
 */
struct node *node_expression_group(YYLTYPE location, struct node *expression)
{
    struct node *node = node_create(location, NODE_EXPRESSION_GROUP);

    node->data.expression_group.expression = expression;

    return node;
}

/*  node_name_index - allocate a node to represent a name index
 *      args: location, expression, index name
 *      rets: name index node
 *
 *  BNF -> prefixexp `.´ Name
 */
struct node *node_name_index(YYLTYPE location, struct node *expression, struct node *index,
                             bool self_index)
{
    struct node *node = node_create(location, NODE_NAME_INDEX);

    node->data.name_index.expression = expression;
    node->data.name_index.index = index;
    node->data.name_index.self_index = self_index;

    return node;
}

/*  node_expression_index - allocate a node to represent an expression index node
 *      args: location, expression, index expression
 *      rets: expression index node
 *
 *  BNF -> prefixexp `[´ exp `]´
 */
struct node *node_expression_index(YYLTYPE location, struct node *expression, struct node *index)
{
    struct node *node = node_create(location, NODE_EXPRESSION_INDEX);

    node->data.name_index.expression = expression;
    node->data.name_index.index = index;

    return node;
}

/*  node_expression_statement - allocate a node to represent an expression as a
 *  statement
 *      args: location, expression node
 *      rets: statement node
 */
struct node *node_expression_statement(YYLTYPE location, struct node *expression)
{
    struct node *node = node_create(location, NODE_EXPRESSION_STATEMENT);

    node->data.expression_statement.expression = expression;

    return node;
}

/*  node_statement_list - allocate a node to represent a statement list
 *      args: location, first statement, next statement
 *      rets: statement list node
 */
struct node *node_block(YYLTYPE location, struct node *init, struct node *statement)
{
    struct node *node = node_create(location, NODE_BLOCK);

    node->data.block.init = init;
    node->data.block.statement = statement;

    return node;
}

/*  node_assignment - allocate a node to represent an assignment node
 *      args: location, list of variables, assignment type, list of values
 *      rets: assignment node
 *
 *  BNF -> varlist assigntype explist
 */
struct node *node_assignment(YYLTYPE location, struct node *variables,
                             enum node_assignment_type type, struct node *values)
{
    struct node *node = node_create(location, NODE_ASSIGNMENT);

    node->data.assignment.variables = variables;
    node->data.assignment.type = type;
    node->data.assignment.values = values;

    return node;
}

/*  node_while_loop - allocate a node to represent a while loop statement
 *      args: location, loop condition, body of loop
 *      rets: while loop node
 *
 *  BNF -> while exp do block end
 */
struct node *node_while_loop(YYLTYPE location, struct node *condition, struct node *body)
{
    struct node *node = node_create(location, NODE_WHILELOOP);

    node->data.while_loop.condition = condition;
    node->data.while_loop.body = body;

    return node;
}

/*  node_repeat_loop - allocate a node to represent a repeat loop statement
 *      args: location, body of loop, loop condition
 *      rets: repeat loop node
 *
 *  BNF -> repeat block until exp
 */
struct node *node_repeat_loop(YYLTYPE location, struct node *body, struct node *condition)
{
    struct node *node = node_create(location, NODE_REPEATLOOP);

    node->data.repeat_loop.body = body;
    node->data.repeat_loop.condition = condition;

    return node;
}

/*  node_if_statement - allocate a node to represent an if statement
 *      args: location, condition, body, else
 *      rets: if statement node
 *
 *  BNF -> if exp then block {elseif exp then block} [else block] end
 */
struct node *node_if_statement(YYLTYPE location, struct node *condition, struct node *body,
                               struct node *else_body)
{
    struct node *node = node_create(location, NODE_IF);

    node->data.if_statement.condition = condition;
    node->data.if_statement.body = body;
    node->data.if_statement.else_body = else_body;

    return node;
}

/*  node_numerical_for_loop - allocate a node to represent a numerical for loop
 *      args: location, init variable, target value, increment value
 *      rets: numerical for loop statement node
 *
 *  BNF -> for Name `=´ exp `,´ exp [`,´ exp] do block end
 */
struct node *node_numerical_for_loop(YYLTYPE location, struct node *init, struct node *target,
                                     struct node *increment, struct node *body)
{
    struct node *node = node_create(location, NODE_NUMERICFORLOOP);

    node->data.numerical_for_loop.init = init;
    node->data.numerical_for_loop.target = target;
    node->data.numerical_for_loop.increment = increment;
    node->data.numerical_for_loop.body = body;

    return node;
}

/*  node_generic_for_loop - allocate a node to represent a generic for loop
 *      args: location, iterators, expressions
 *      rets: generic for loop statement node
 *
 *  BNF -> for namelist in explist do block end
 */
struct node *node_generic_for_loop(YYLTYPE location, struct node *local, struct node *body)
{
    struct node *node = node_create(location, NODE_GENERICFORLOOP);

    node->data.generic_for_loop.local = local;
    node->data.generic_for_loop.body = body;

    return node;
}

/*  node_local - allocate a node to represent a local assignment
 *      args: location, var list, expressions
 *      rets: local statement node
 *
 *  BNF -> local namelist [`=´ explist]
 */
struct node *node_local(YYLTYPE location, struct node *namelist, struct node *exprlist)
{
    struct node *node = node_create(location, NODE_LOCAL);

    node->data.local.namelist = namelist;
    node->data.local.exprlist = exprlist;

    return node;
}

/*  node_return - allocate a node to represent a return statement
 *      args: location, expressions
 *      rets: return statement node
 *
 *  BNF -> return [explist]
 */
struct node *node_return(YYLTYPE location, struct node *exprlist)
{
    struct node *node = node_create(location, NODE_RETURN);

    node->data.return_statement.exprlist = exprlist;

    return node;
}

/*  node_break - allocate a node to represent a break statement
 *      args: location
 *      rets: break statement node
 *
 *  BNF -> break
 */
struct node *node_break(YYLTYPE location)
{
    /* No data for this node, it's just a 'marker' */
    return node_create(location, NODE_BREAK);
}

/*  node_function_body - allocate a node to represent a function body
 *      args: location, parameters, list of return types, function body
 *      rets: function body node
 *
 *  BNF -> `(´ [parlist] `)´ `:´ typelist block end
 */
struct node *node_function_body(YYLTYPE location, struct node *exprlist, struct node *type_list,
                                struct node *body)
{
    struct node *node = node_create(location, NODE_FUNCTION_BODY);

    node->data.function_body.exprlist = exprlist;
    node->data.function_body.type_list = type_list;
    node->data.function_body.body = body;

    return node;
}

/*  node_function_body - allocate a node to represent a parameter list
 *      args: location, parameters, vararg
 *      rets: parameter list node
 *
 *  BNF -> parlist ::= namelist [`,´ `...´] | `...´
 */
struct node *node_parameter_list(YYLTYPE location, struct node *namelist, struct node *vararg)
{
    struct node *node = node_create(location, NODE_PARAMETER_LIST);

    node->data.parameter_list.namelist = namelist;

    node->data.parameter_list.vararg = vararg;

    return node;
}

/*  node_name_reference - allocate a node to represent a name reference
 *      args: location, identifier
 *      rets: name refrence node
 *
 *  BNF -> Name | prefixexp `[´ exp `]´ | prefixexp `.´ Name
 */
struct node *node_name_reference(YYLTYPE location, struct node *nameref)
{
    struct node *node = node_create(location, NODE_NAME_REFERENCE);

    node->data.name_reference.identifier = nameref;
    node->node_type = nameref->node_type;

    return node;
}

/*  node_array_constructor - allocate a node to represent an array constructor
 *      args: location, expression list
 *      rets: array constructor
 *
 *  BNF -> `{´ [exprlist] `}´
 */
struct node *node_array_constructor(YYLTYPE location, struct node *exprlist)
{
    struct node *node = node_create(location, NODE_ARRAY_CONSTRUCTOR);

    node->data.array_constructor.exprlist = exprlist;

    return node;
}

/*  node_table_constructor - allocate a node to represent a table constructor
 *      args: location, pair list
 *      rets: table constructor
 *
 *  BNF -> `{´ [pairlist] `}´
 */
struct node *node_table_constructor(YYLTYPE location, struct node *pairlist)
{
    struct node *node = node_create(location, NODE_TABLE_CONSTRUCTOR);

    node->data.table_constructor.pairlist = pairlist;

    return node;
}

/*  node_key_value_pair - allocate a node to represent key value pair
 *      args: location, key, value
 *      rets: key value pair
 *
 *  BNF -> `[´ exp `]´ `=´ exp
 */
struct node *node_key_value_pair(YYLTYPE location, struct node *key, struct node *value)
{
    struct node *node = node_create(location, NODE_KEY_VALUE_PAIR);

    node->data.key_value_pair.key = key;
    node->data.key_value_pair.value = value;

    return node;
}

/*  node_vararg - allocate a node to represent a vararg node ('...')
 *      args: location
 *      rets: vararg node
 *
 *  BNF -> `...´
 */
struct node *node_vararg(YYLTYPE location)
{
    struct node *node = node_create(location, NODE_VARARG);

    node->node_type = type_basic(TYPE_BASIC_VARARG);

    return node;
}

/*  write_node - writes a node to a file in graphviz format
 *      args: output file, name of the node
 *      rets: none
 */
void write_node(FILE *output, char *name, bool highlight)
{
    write_parentless_node(output, name, highlight);
    fprintf(output, "\tn%i->n%i\n", parent_id, id);
}

/*  write_parentless_node - writes a parentless node to a file in graphviz format
 *      args: output file, name of the node
 *      rets: none
 */
void write_parentless_node(FILE *output, char *name, bool highlight)
{
    if (highlight) {
        fprintf(output, "\tn%i[label=\"%s\"]\n", id, name);
        fprintf(output, "\tn%i[color=green3]\n", id);
        fprintf(output, "\tn%i[fontcolor=green3]\n", id);
    } else
        fprintf(output, "\tn%i[label=\"%s\"]\n", id, name);
}

/*  format_node - formats the 'data' value of the given node
 *      args: node to be formatted
 *      rets: formatted string
 *
 *  Note: Yes, I know, this code is horrible. I'm going to leave this here until I find a
 *  good workaround. For now this is the only way I could think of formatting the nodes correctly.
 */
char *format_node(struct node *node)
{
    char *str;
    size_t len;

    /* Get the size of the formatted string */
    switch (node->type) {
        case NODE_NUMBER:
            len = (size_t)snprintf(NULL, 0, "number\\n\\\"%lf\\\"", node->data.number.value);
            break;
        case NODE_IDENTIFIER:
            len = (size_t)snprintf(NULL, 0, "identifier\\n\\\"%s\\\"", node->data.identifier.name);
            break;
        case NODE_STRING:
            len = (size_t)snprintf(NULL, 0, "string\\n\\\"%s\\\"", node->data.string.value);
            break;
        case NODE_BOOLEAN:
            len = (size_t)snprintf(NULL, 0, "boolean\\n\\\"%s\\\"",
                                   node->data.boolean.value ? "true" : "false");
            break;
    }

    /* Allocate memory for our new string using len */
    if ((str = malloc(len)) == NULL) {
        fprintf(stderr, "format_node(): Unable to allocate memory");
        exit(EXIT_FAILURE);
    }

    /* TODO: Not sure why we need len + 1? I tried with just len, but it cut off the last character.
     * Find and research a better way to do this (this function is actually surprisingly fast).
     *
     * Idea ---> Maybe I can just make a buffer with a massive size (e.g char buffer[MAX_SIZE]). If
     * a string is greater than that size, just shorten it or rely on it never being that big? This
     * seems like a BS method, but it is the only real workaround I could think of.
     *
     * Try MAX_SIZE 1000-9999
     */

    /* Format the string and store it in the newly allocated memory in str */
    switch (node->type) {
        case NODE_NUMBER:
            snprintf(str, len + 1, "number\\n\\\"%lf\\\"", node->data.number.value);
            break;
        case NODE_IDENTIFIER:
            snprintf(str, len + 1, "identifier\\n\\\"%s\\\"", node->data.identifier.name);
            break;
        case NODE_STRING:
            snprintf(str, len + 1, "string\\n\\\"%s\\\"", node->data.string.value);
            break;
        case NODE_BOOLEAN:
            snprintf(str, len + 1, "boolean\\n\\\"%s\\\"",
                     node->data.boolean.value ? "true" : "false");
            break;
    }

    return str;
}

/*  print_ast - traverses through the AST and prints every node via graphviz
 *      args: output file, node to be printed, boolean indicating node is root
 *      rets: none
 */
void print_ast(FILE *output, struct node *node, bool first)
{
    int previous;
    char buff[50];
    char *valbuff;

    /* Don't use assert. This is how we detect empty nodes (e.g. print() -- no arguments) */
    if (node == NULL)
        return;

    switch (node->type) {
        case NODE_BOOLEAN:
        case NODE_STRING:
        case NODE_IDENTIFIER:
        case NODE_NUMBER:
            valbuff = format_node(node);

            /* Write the formatted value */
            write_node(output, valbuff, false);
            id++;

            /* Free all the memory we allocated for the buffer */
            free(valbuff);
            break;
        case NODE_NIL:
            write_node(output, "nil", false);
            id++;
            break;
        case NODE_TYPE_ANNOTATION:
            /* Fromat name of node: "binary operation \n op" */
            write_node(output, "type annotation", false);

            /* Save and increment the id of the current node */
            previous = parent_id;
            parent_id = id++;

            /* Print expressions */
            print_ast(output, node->data.type_annotation.identifier, false);
            print_ast(output, node->data.type_annotation.type, false);

            parent_id = previous;
            break;
        case NODE_TYPE:
        case NODE_TYPE_ARRAY:
        case NODE_TYPE_TABLE:
        case NODE_TYPE_FUNCTION:
            write_node(output, type_to_string(node->node_type), true);
            id++;
            break;
        case NODE_BINARY_OPERATION:
            /* Fromat name of node: "binary operation \n op" */
            sprintf(buff, "binary operation\\n%s",
                    binary_operations[node->data.binary_operation.operation]);

            write_node(output, buff, false);

            /* Save and increment the id of the current node */
            previous = parent_id;
            parent_id = id++;

            /* Print expressions (left and right) */
            print_ast(output, node->data.binary_operation.left, false);
            print_ast(output, node->data.binary_operation.right, false);

            parent_id = previous;
            break;
        case NODE_UNARY_OPERATION:
            /* Fromat name of node: "unary operation \n op" */
            sprintf(buff, "unary operation\\n%s",
                    unary_operations[node->data.unary_operation.operation]);

            write_node(output, buff, false);

            /* Save and increment the id of the current node */
            previous = parent_id;
            parent_id = id++;

            /* Print unary expression */
            print_ast(output, node->data.unary_operation.expression, false);

            parent_id = previous;
            break;
        case NODE_EXPRESSION_LIST:
            /* No graphviz needed */
            print_ast(output, node->data.expression_list.init, false);

            if (node->data.expression_list.expression != NULL)
                print_ast(output, node->data.expression_list.expression, false);
            break;
        case NODE_NAME_LIST:
            /* No graphviz needed */
            print_ast(output, node->data.name_list.init, false);

            if (node->data.name_list.name != NULL)
                print_ast(output, node->data.name_list.name, false);
            break;
        case NODE_VARIABLE_LIST:
            /* No graphviz needed */
            print_ast(output, node->data.variable_list.init, false);

            if (node->data.variable_list.variable != NULL)
                print_ast(output, node->data.variable_list.variable, false);
            break;
        case NODE_TYPE_LIST:
            /* No graphviz needed */
            print_ast(output, node->data.type_list.init, false);

            if (node->data.type_list.type != NULL)
                print_ast(output, node->data.type_list.type, false);
            break;
        case NODE_PARAMETER_LIST:
            write_node(output, "parameter_list", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            print_ast(output, node->data.parameter_list.namelist, false);
            print_ast(output, node->data.parameter_list.vararg, false);

            parent_id = previous;
            break;
        case NODE_CALL:
            write_node(output, "call", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the call */
            print_ast(output, node->data.call.prefix_expression, false);
            print_ast(output, node->data.call.args, false);

            parent_id = previous;
            break;
        case NODE_EXPRESSION_INDEX:
            write_node(output, "expression index", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the expression index */
            print_ast(output, node->data.expression_index.expression, false);
            print_ast(output, node->data.expression_index.index, false);

            parent_id = previous;
            break;
        case NODE_NAME_INDEX:
            write_node(output, "name index", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the name index */
            print_ast(output, node->data.name_index.expression, false);
            print_ast(output, node->data.name_index.index, false);

            parent_id = previous;
            break;
        case NODE_EXPRESSION_GROUP:
            write_node(output, "expression group", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit the child expression */
            print_ast(output, node->data.expression_group.expression, false);

            parent_id = previous;
            break;
        case NODE_EXPRESSION_STATEMENT:
            /* No graphviz needed */
            print_ast(output, node->data.expression_statement.expression, false);
            break;
        case NODE_BLOCK:
            previous = 0;

            /* Check if we are in the root node */
            if (first) {
                fprintf(output, "digraph G\n{\n");
                fprintf(output, "\tnode[fontname=Monospace]\n");

                /* Write the parentless node and increment id */
                write_parentless_node(output, "program", false);
                id++;
            } else {
                /* Save parent id for reset later */
                previous = parent_id;
                id++;
            }

            print_ast(output, node->data.block.init, false);

            if (node->data.block.statement != NULL)
                print_ast(output, node->data.block.statement, false);

            /* Reset parent ID for next node */
            parent_id = previous;

            /* Close diagraph */
            if (first)
                fprintf(output, "}\n");
            break;
        case NODE_ASSIGNMENT:
            /* Fromat name of node: "binary operation \n op" */
            sprintf(buff, "assignment\\n%s", assignment_types[node->data.assignment.type]);

            write_node(output, buff, false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the assignment node */
            print_ast(output, node->data.assignment.variables, false);
            print_ast(output, node->data.assignment.values, false);

            parent_id = previous;
            break;
        case NODE_WHILELOOP:
            write_node(output, "while", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the while node */
            print_ast(output, node->data.while_loop.condition, false);
            print_ast(output, node->data.while_loop.body, false);

            parent_id = previous;
            break;
        case NODE_REPEATLOOP:
            write_node(output, "repeat", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the repeat node */
            print_ast(output, node->data.repeat_loop.body, false);
            print_ast(output, node->data.repeat_loop.condition, false);

            parent_id = previous;
            break;
        case NODE_IF:
            write_node(output, "if", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the if node */
            print_ast(output, node->data.if_statement.condition, false);
            print_ast(output, node->data.if_statement.body, false);
            print_ast(output, node->data.if_statement.else_body, false);

            parent_id = previous;
            break;
        case NODE_NUMERICFORLOOP:
            write_node(output, "for", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the for node */
            print_ast(output, node->data.numerical_for_loop.init, false);
            print_ast(output, node->data.numerical_for_loop.target, false);
            print_ast(output, node->data.numerical_for_loop.increment, false);
            print_ast(output, node->data.numerical_for_loop.body, false);

            parent_id = previous;
            break;
        case NODE_GENERICFORLOOP:
            write_node(output, "for", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the for node */
            print_ast(output, node->data.generic_for_loop.local, false);
            print_ast(output, node->data.generic_for_loop.body, false);

            parent_id = previous;
            break;
        case NODE_LOCAL:
            write_node(output, "local", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the for node */
            print_ast(output, node->data.local.namelist, false);
            print_ast(output, node->data.local.exprlist, false);

            parent_id = previous;
            break;
        case NODE_RETURN:
            write_node(output, "return", false);

            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            /* Visit children nodes of the for node */
            print_ast(output, node->data.return_statement.exprlist, false);

            parent_id = previous;
            break;
        case NODE_BREAK:
            write_node(output, "break", false);
            id++;
            break;
        case NODE_FUNCTION_BODY:
            write_node(output, "function_body", false);
            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            printf("BODY: %d\n", node->data.function_body.body == NULL);

            /* Visit children nodes of the for node */
            print_ast(output, node->data.function_body.exprlist, false);
            print_ast(output, node->data.function_body.type_list, false);
            print_ast(output, node->data.function_body.body, false);

            parent_id = previous;
            break;
        case NODE_NAME_REFERENCE:
            write_node(output, "name_reference", false);
            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            print_ast(output, node->data.name_reference.identifier, false);

            parent_id = previous;
            break;
        case NODE_ARRAY_CONSTRUCTOR:
            write_node(output, "array_constructor", false);
            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            print_ast(output, node->data.array_constructor.exprlist, false);

            parent_id = previous;
            break;
        case NODE_KEY_VALUE_PAIR:
            write_node(output, "key_value_pair", false);
            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            print_ast(output, node->data.key_value_pair.key, false);
            print_ast(output, node->data.key_value_pair.value, false);

            parent_id = previous;
            break;
        case NODE_TABLE_CONSTRUCTOR:
            write_node(output, "table_constructor", false);
            /* Save and increment ids */
            previous = parent_id;
            parent_id = id++;

            print_ast(output, node->data.table_constructor.pairlist, false);

            parent_id = previous;
            break;
        case NODE_VARARG:
            write_node(output, "...", false);
            break;
        default:
            break;
    }
}

/* node_to_string() -- convert the given node to a string representation.
 *     args: ast node
 *     rets: string representation
 *
 * Node: not all nodes are supported as this function is only required for certain
 * node types.
 */
char *node_to_string(struct node *node)
{
    flexstr_t s;
    fs_init(&s, 0);

    switch (node->type) {
        case NODE_TYPE_LIST:
            for (node; node != NULL; node = node->data.type_list.init) {
                /* Must be any other type (number, string, boolean, Table, Array, or function) */
                if (node->type != NODE_TYPE_LIST) {
                    fs_addstr(&s, type_to_string(node->node_type));
                    return fs_getstr(&s);
                }
                /* We must have a type list, so just process the first one */
                else {
                    fs_addstr(&s, type_to_string(node->data.type_list.type->node_type));
                    fs_addstr(&s, ", ");
                }
            }
        case NODE_TYPE:
            return type_to_string(node->node_type);
        default:
            printf("%d\n", node->type);
            return "none";
    }
}