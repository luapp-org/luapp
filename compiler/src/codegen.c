#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen.h"
#include "ir.h"
#include "symbol.h"
#include "type.h"

void codegen_write_byte(FILE *output, unsigned char value) { fprintf(output, "%02X", value); }

void codegen_write_size(FILE *output, unsigned int size)
{
    do {
        /* Extract a byte from the int */
        int val = size & 0x7F;
        size >>= 7;

        if (size)
            val |= 0x80;

        /* Write the byte to the stream */
        codegen_write_byte(output, val);

    } while (size);
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

void codegen_write_proto(FILE *output, struct ir_proto *proto)
{
    /* Write the important information about the function */
    codegen_write_byte(output, proto->max_stack_size);
    codegen_write_byte(output, proto->parameters_size);
    codegen_write_byte(output, proto->is_vararg);

    /* Write all of the instructions to the stream */
    for (struct ir_instruction *iter = proto->code->first; iter != NULL; iter = iter->next)
        codegen_write_size(output, iter->value);

    /* Write all of the constants to the stream */
    for (struct ir_constant *iter = proto->constant_list->first; iter != NULL; iter = iter->next) {
        /* Handle each constant type */
        switch (iter->type) {
            case CONSTANT_STRING:
                codegen_write_size(output, iter->data.string.symbol_id);
                break;
            case CONSTANT_NUMBER:
                codegen_write_size(output, iter->data.number.value);
                break;
        }
    }
}

void codegen_write_program(FILE *output, struct ir_context *context)
{
    codegen_write_symbol_table(output, context->table);

    /* Collect the protos */
    struct ir_proto_list *protos = ir_collect_protos(context->main_proto);
    
    /* Write the proto list to the stream */
    codegen_write_size(output, protos->size);

    for (struct ir_proto *iter = protos->first; iter != NULL; iter = iter->next)
        codegen_write_proto(output, iter);

    fprintf(output, "\n\n");
}