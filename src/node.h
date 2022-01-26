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
    NODE_EXPRESSION_STATEMENT,
    NODE_STATEMENT_LIST
};

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
            char value[0];
        } string;
        struct {
            struct node *expression;
        } expression_statement;
        struct {
            struct node *init;      /* First statement */
            struct node *statement; /* Next statement */
        } statment_list;
    } data;
};

/* Node create method definition */
static struct node *node_create(YYLTYPE location, enum node_type type);

/* Node expression method definitions */
struct node *node_integer(YYLTYPE location, char *value);
struct node *node_identifier(YYLTYPE location, char *value, int length);
struct node *node_string(YYLTYPE location, char *value, int length);

/* Node statement method definitions */
struct node *node_expression_statement(YYLTYPE location,
                                       struct node *expression);
struct node *node_statement_list(YYLTYPE location, struct node *init,
                                 struct node *statement);

#endif