#ifndef _MACRO_H
#define _MACRO_H

#include "compiler.h"

/* WARNING! This function does not close the file pointer. */
void macro_init(compiler_context_t *context, FILE *input);
void macro_print(compiler_context_t* context);
#endif