/*  node.c - only version
 *       methods that construct the tree
 */

#include "node.h"

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

    return node;
}

/*  node_integer - allocate a node to represent an integer
 *      args: location, value as string
 *      rets: integer node
 */
struct node *node_integer(YYLTYPE location, char *value)
{
    struct node *node = node_create(location, NODE_INTEGER);
    char *end;

    /* Convert value to a double and store _endptr in end */
    node->data.integer.value = strtod(value, &end);

    /* Check for hexadecimal and convert to unsigned long in base 16 if so */
    if (*end == 'x' || *end == 'X')
        node->data.integer.value = strtoul(value, &end, 16);

    node->data.integer.overflow = *end == 0 ? false : true;

    return node;
}

/*  node_identifier - allocate a node to represent an identifier
 *      args: location, name of identifier, length of name
 *      rets: identifier node
 */
struct node *node_identifier(YYLTYPE location, char *value, int length)
{
    struct node *node = node_create(location, NODE_IDENTIFIER);

    /* Set the name by appending all of the characters in value */
    strncat(node->data.identifier.name, value, length);

    return node;
}

/*  node_string - allocate a node to represent a string
 *      args: location, name of identifier, length of name
 *      rets: string node
 */
struct node *node_string(YYLTYPE location, char *value, int length)
{
    struct node *node = node_create(location, NODE_STRING);

    /* Set the name by appending all of the characters in value */
    strncat(node->data.identifier.name, value, length);

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
    
    return node;
}

/*  node_nil - allocate a node to represent a nil value
 *      args: location, value 
 *      rets: boolean node
 */
struct node *node_nil(YYLTYPE location)
{
    /* No data for this node, it's just a 'marker' */
    return node_create(location, NODE_NIL);
}

/*  node_binary_operation - allocate a node to represent a binary operation
 *      args: location, operation, left operand, right operand 
 *      rets: binary operation node
 */
struct node *node_binary_operation(YYLTYPE location,
                                   enum node_binary_operation operation,
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
 */
struct node *node_unary_operation(YYLTYPE location,
                                  enum node_unary_operation operation,
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
 */
struct node *node_expression_list(YYLTYPE location, struct node *init,
                                 struct node *expression)
{
    struct node *node = node_create(location, NODE_EXPRESSION_LIST);

    node->data.expression_list.init = init;
    node->data.expression_list.expression = expression;

    return node;
}

/*  node_expression_statement - allocate a node to represent an expression as a
 *  statement 
 *      args: location, expression node 
 *      rets: statement node
 */
struct node *node_expression_statement(YYLTYPE location,
                                       struct node *expression)
{
    struct node *node = node_create(location, NODE_EXPRESSION_STATEMENT);

    node->data.expression_statement.expression = expression;

    return node;
}

/*  node_statement_list - allocate a node to represent a statement list
 *      args: location, first statement, next statement 
 *      rets: statement list node
 */
struct node *node_statement_list(YYLTYPE location, struct node *init,
                                 struct node *statement)
{
    struct node *node = node_create(location, NODE_STATEMENT_LIST);

    node->data.statment_list.init = init;
    node->data.statment_list.statement = statement;

    return node;
}