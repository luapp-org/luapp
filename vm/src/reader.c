#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "reader.h"
#include "vm.h"

unsigned char read_byte(FILE *input)
{
    unsigned char byte;
    fread(&byte, sizeof(byte), 1, input);

    return byte;
}

unsigned int read_cint(FILE *input)
{
    unsigned int result = 0;
    unsigned int shift = 0;

    unsigned char byte;

    do
    {
        byte = read_byte(input);
        result |= (byte & 127) << shift;
        shift += 7;
    } while (byte & 128);

    return result;
}

unsigned int read_int(FILE *input)
{
    unsigned int integer;
    fread(&integer, sizeof(integer), 1, input);

    return integer;
}

char *read_string(FILE *input, char **strings)
{
    unsigned int index = read_cint(input);
;
    return index == 0 ? NULL : strings[index - 1];
}

struct vm_value get_env(struct vm_table *env, struct vm_value value)
{
    struct vm_value *ret;
    if (ret = vm_table_get(env, value))
        return *ret;
    else {
        struct vm_value nil;
        VM_SETNIL(&nil);

        return nil;
    }
}

char **read_strings(FILE *input)
{
    /* Create the main string array */
    int size = read_cint(input);

    char **strings = calloc(size, sizeof(char *));
    assert(strings);

    /* Read each string individually */
    for (int i = 0; i < size; i++) {
        int len = read_cint(input);

        /* + 1 for the end of string delimeter */
        strings[i] = calloc(len + 1, sizeof(char));
        assert(strings[i]);

        /* Read each char of the string and save in 'strings' */
        for (int j = 0; j < len; j++)
            strings[i][j] = (char)read_byte(input);

        strings[i][len] = '\0';
    }

    return strings;
}

struct vm_proto *read_protos(FILE *input, struct vm_context *context)
{
    /* Create ana allocate the function prototype list */
    int size = read_cint(input);
    struct vm_proto *protos = calloc(size, sizeof(struct vm_proto));
    assert(protos);

    /* Traverse through each function prototype */
    for (int i = 0; i < size; i++) {
        /* Read properties */
        protos[i].max_stack_size = read_byte(input);
        protos[i].parameters_size = read_byte(input);
        protos[i].is_vararg = read_byte(input);

        /* Create the instruction array */
        int sizecode = read_cint(input);
        protos[i].code = calloc(sizecode, sizeof(unsigned int));

        /* Read each instruction in the array */
        for (int j = 0; j < sizecode; j++)
            protos[i].code[j] = read_int(input);

        /* Create the constant array */
        protos[i].sizek = read_cint(input);

        protos[i].constants = calloc(protos[i].sizek, sizeof(struct vm_value));

        /* Read each constant */
        for (int k = 0; k < protos[i].sizek; k++) {

            /* Handle each constant type */
            switch (read_byte(input)) {
                case CONST_ENV: {
                    /* Attemp to load environment member, set nil otherwise */
                    const struct vm_value s = protos[i].constants[read_int(input)];
                    struct vm_value e = get_env(context->env, s);

                    VM_SETOBJ(&protos[i].constants[k], &e);
                    break;
                }
                case CONST_STRING: {
                    char *s = read_string(input, context->strings);
                    VM_SETSVALUE(&protos[i].constants[k], s);
                    break;
                }
                case CONST_NUMBER:
                    VM_SETNVALUE(&protos[i].constants[k], read_int(input));
                    break;
            }
        }
    }

    return protos;
}

void read_context(FILE *input, struct vm_context *context)
{
    context->strings = read_strings(input);
    context->protos = read_protos(input, context);
}