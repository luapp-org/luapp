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
struct node *node_identifier(YYLTYPE location, char* value, int length)
{
    struct node *node = node_create(location, NODE_IDENTIFIER);

    /* Set the name by appending all of the characters in value */
    strncat(node->data.identifier.name, value, length);

    return node;
}