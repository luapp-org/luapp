#ifndef _LEXER_H
#define _LEXER_H

#include "includes.h"

void lex_init(yyscan_t *lexer, FILE *input);
void lex_destroy(yyscan_t *lexer);
void lex_print(yyscan_t lexer, int *error_count, FILE *output);

#endif