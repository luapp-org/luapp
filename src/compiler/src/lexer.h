#ifndef _LEXER_H
#define _LEXER_H

#include "lexer.yy.h"

typedef struct compiler_context compiler_context_t;

void lex_init(yyscan_t *lexer, compiler_context_t *context, FILE *input);
void lex_destroy(yyscan_t *lexer);
void lex_print(yyscan_t lexer, int *error_count, FILE *output);

#endif