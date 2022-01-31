#ifndef _NODE_H
#define _NODE_H

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

#include <assert.h>
#include <float.h>
#include <stdbool.h>

#include "compiler.h"

enum node_type {
    NODE_INTEGER,
    NODE_IDENTIFIER,
    NODE_STRING,
    NODE_BOOLEAN,
    NODE_NIL,
    NODE_BINARY_OPERATION,
    NODE_UNARY_OPERATION,
    NODE_EXPRESSION_LIST,
    NODE_CALL,
    NODE_EXPRESSION_GROUP,
    NODE_NAME_INDEX,
    NODE_EXPRESSION_INDEX,
    NODE_EXPRESSION_STATEMENT,
    NODE_BLOCK
};

/* Binary operations */
enum node_binary_operation {
    /* Arithmetic operations */
    BINOP_MUL,
    BINOP_DIV,
    BINOP_ADD,
    BINOP_SUB,
    BINOP_POW,
    BINOP_MOD,
    BINOP_CONCAT,
    /* Comparative */
    BINOP_GT,
    BINOP_LT,
    BINOP_GE,
    BINOP_LE,
    BINOP_EQ,
    BINOP_NE,
    BINOP_AND,
    BINOP_OR
};

/* Unary operations (-, not, #) */
enum node_unary_operation { UNOP_NEG, UNOP_NOT, UNOP_LEN };

/* Node struct with data unions */
struct node {
    enum node_type type;
    struct YYLTYPE location;
    union {
        struct {
            double value;
            bool overflow; /* Indicates double overflow */
        } integer;
        struct {
            char name[0];
        } identifier;
        struct {
            char *value;
        } string;
        struct {
            bool value;
        } boolean;
        struct {
            enum node_binary_operation operation;
            struct node *left;  /* Left operand */
            struct node *right; /* Right operand */
        } binary_operation;
        struct {
            enum node_unary_operation operation;
            struct node *expression; /* Operand */
        } unary_operation;
        struct {
            struct node *init;       /* First expression */
            struct node *expression; /* Next expression */
        } expression_list;
        struct {
            struct node *expression;
        } expression_statement;
        struct {
            struct node *prefix_expression;
            struct node *args;
            bool self_call; /* Depricated: self syntax only for tables */
        } call;
        struct {
            struct node *expression;
        } expression_group;
        struct {
            struct node *expression;
            struct node *index;
            bool self_index; /* prefixexp `:´ Name  ->  only in self-calls*/
        } name_index;
        struct {
            struct node *expression;
            struct node *index;
        } expression_index;
        struct {
            struct node *init;      /* First statement */
            struct node *statement; /* Next statement */
        } block;
    } data;
};

/* Node create method constructor */
static struct node *node_create(YYLTYPE location, enum node_type type);

/* Node expression constructors */
struct node *node_integer(YYLTYPE location, char *value);
struct node *node_identifier(YYLTYPE location, char *value, int length);
struct node *node_string(YYLTYPE location, char *value, int length);
struct node *node_boolean(YYLTYPE location, bool value);
struct node *node_nil(YYLTYPE location);
struct node *node_binary_operation(YYLTYPE location, enum node_binary_operation operation,
                                   struct node *left, struct node *right);
struct node *node_unary_operation(YYLTYPE location, enum node_unary_operation operation,
                                  struct node *expression);
struct node *node_expression_list(YYLTYPE location, struct node *init, struct node *expression);
struct node *node_call(YYLTYPE location, struct node *prefix_expression, struct node *args,
                       bool self_call);
struct node *node_expression_group(YYLTYPE location, struct node *expression);
struct node *node_name_index(YYLTYPE location, struct node *expression, struct node *index,
                             bool self_index);
struct node *node_expression_index(YYLTYPE location, struct node *expression, struct node *index);

/* Node statement constructors */
struct node *node_expression_statement(YYLTYPE location, struct node *expression);
struct node *node_block(YYLTYPE location, struct node *init, struct node *statement);

/* AST traversal methods */
void print_ast(FILE *output, struct node *node);

#endif