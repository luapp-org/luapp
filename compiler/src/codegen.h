#ifndef _CODEGEN_H
#define _CODEGEN_H

#include <stdio.h>

void codegen_write_program(FILE *output, struct ir_context *context, struct ir_section *section);

#endif