#ifndef _COMPILER_H
#define _COMPILER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/* Errors */
#define LEX_UNKCHAR -1
#define LEX_UNFSTR -2

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

void compiler_error(YYLTYPE location, const char *format, ...);
const char *token_to_string(int token);
char* concat(const char* s1, const char* s2);
void clear(char arr[]);

#endif