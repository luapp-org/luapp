#ifndef _COMPILER_H
#define _COMPILER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common/bytecode.h"
#include "../../common/opcodes.h"

#define COMPILER_VERSION "1.0"

typedef struct node *YYSTYPE;
#define YYSTYPE struct node *

#if !defined YYLTYPE && !defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1
#endif

typedef struct compiler_context {
    char *stage;
    int error_count;
    time_t time;

    /* Compiler settings */
    bool is_strict;    /* Strict type context  */
    bool is_c_array;   /* Arrays start at 0 not 1 */
    bool is_c_comment; /* C-style comments (//) */
} compiler_context_t;

void compiler_error(YYLTYPE location, const char *format, ...);
void lcompiler_error(const char *format, ...);

bool compile(compiler_context_t *context, FILE *input, FILE *output);

const char *token_to_string(int token);
void clear(char arr[]);
void usage();

#endif