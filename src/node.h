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
    NODE_IDENTIFIER
};

struct node {
    enum node_type type;
    struct YYLTYPE location;
    union {
        struct {
            double value; 
            bool overflow;
        } integer;
        struct {
            char name[0];
        } identifier;
    } data;
};

static struct node *node_create(YYLTYPE location, enum node_type type);
struct node *node_integer(YYLTYPE location, char* value);
struct node *node_identifier(YYLTYPE location, char* value, int length);

#endif