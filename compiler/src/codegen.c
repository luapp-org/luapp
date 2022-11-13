#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen.h"
#include "ir.h"
#include "symbol.h"
#include "type.h"

void codegen_write_byte(FILE *output, unsigned char value)
{
    fwrite(&value, sizeof(value), 1, output);
}

void codegen_write_int(FILE *output, unsigned int value)
{
    fwrite(&value, sizeof(value), 1, output);
}

void codegen_write_size(FILE *output, unsigned int value)
{
    do {
        codegen_write_byte(output, (value & 127) | ((value > 127) << 7));
        printf("just wrote value: %d\n", (value & 127) | ((value > 127) << 7));
        value >>= 7;
    } while (value);
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

    for (struct symbol_list *iter = table->first; iter != NULL; iter = iter->next)
        codegen_write_string(output, iter->symbol.name);
}

void codegen_write_proto(FILE *output, struct ir_proto *proto)
{
    /* Write the important information about the function */
    codegen_write_byte(output, proto->max_stack_size);
    codegen_write_byte(output, proto->parameters_size);
    codegen_write_byte(output, proto->is_vararg);

    codegen_write_size(output, proto->code->size);

    /* Write all of the instructions to the stream */
    for (struct ir_instruction *iter = proto->code->first; iter != NULL; iter = iter->next) {
        codegen_write_int(output, iter->value);
    }

    codegen_write_size(output, proto->constant_list->size);

    int id = 0;
    for (struct ir_constant *iter = proto->constant_list->first; iter != NULL; iter = iter->next) {
        codegen_write_byte(output, iter->type);
        /* Write individual constants */
        switch (iter->type) {
            case CONSTANT_STRING:
                //fprintf(stdout, "[%d]   string { %d }\n", id++, iter->data.symbol.symbol_id);
                codegen_write_size(output, iter->data.symbol.symbol_id + 1);
                break;
            case CONSTANT_ENV:
                //fprintf(stdout, "[%d]   global { k(%d) }\n", id++, iter->data.env.index);
                codegen_write_int(output, iter->data.env.index);
                break;
            case CONSTANT_NUMBER:
                //fprintf(stdout, "[%d]   number { %f }\n", id++, iter->data.number.value);
                codegen_write_int(output, iter->data.number.value);
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