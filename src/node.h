#ifndef _NODE_H
#define _NODE_H

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

#include "compiler.h"

enum node_type {
    NODE_NUMBER
}

struct node {
    enum node_type type;
    struct YYLTYPE *location;
    union {
        struct {
            
        } integer;
    } data;
}

#endif