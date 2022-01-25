#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

typedef struct node *YYSTYPE;
#define YYSTYPE struct node *

#include "parser.tab.h"
#include "lexer.yy.h"