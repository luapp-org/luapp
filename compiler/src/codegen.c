#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "type.h"
#include "symbol.h"
#include "ir.h"
#include "codegen.h"

void codegen_write_byte(FILE *output, unsigned char value) { fprintf(output, "%02X", value); }

void codegen_write_size(FILE *output, unsigned int size)
{
    /* Check if we can write the size as one byte */
    if (size < 0xFF)
        codegen_write_byte(output, size);
    else {
        codegen_write_byte(output, 0xFF);
        codegen_write_size(output, size - 0xFF);
    }
}

void codegen_write_string(FILE *output, char *value)
{
    int size = strlen(value);
    codegen_write_size(output, size);

    /* Write each character individually */
    for (int i = 0; i < size; i++)
        codegen_write_byte(output, value[i]);
}

void codegen_write_symbol_table(FILE *output, struct symbol_table *table)
{
    codegen_write_size(output, table->size);

    for (struct symbol_list *iter = table->variables; iter != NULL; iter = iter->next) 
        codegen_write_string(output, iter->symbol.name);
}

void codegen_write_program(FILE *output, struct ir_context *context, struct ir_section *section)
{
    codegen_write_symbol_table(output, context->table);
    fprintf(output, "\n\n");
}