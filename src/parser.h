#ifndef _PARSER_H
#define _PARSER_H

#include "lexer.yy.h"

struct node *parser_parse(int *error_count, yyscan_t lexer);

#endif