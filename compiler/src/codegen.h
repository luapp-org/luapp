#ifndef _CODEGEN_H
#define _CODEGEN_H

#include <stdio.h>

struct ir_context;

void codegen_write_program(FILE *output, struct ir_context *context);

#endif