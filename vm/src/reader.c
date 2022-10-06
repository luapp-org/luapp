#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "lib.h"
#include "vm.h"

unsigned char read_byte(FILE *input)
{
    unsigned char byte;
    fread(&byte, sizeof(byte), 1, input);

    return byte;
}

unsigned int read_cint(FILE *input)
{
    int result = 0, a = 0, b = 0;
    unsigned char byte;

    do {
        /* Uncompress the integer with this weird math */
        byte = read_byte(input);
        a = (byte & 0x7F) << b;
        b += 7;
        result |= a;

    } while (byte < 0);

    return result;
}

unsigned int read_int(FILE *input)
{
    unsigned int integer;
    fread(&integer, sizeof(integer), 1, input);

    return integer;
}

char **read_strings(FILE *input)
{
    /* Create the main string array */
    int size = read_cint(input);

    char **strings = malloc((size + 1) * sizeof(char *));
    assert(strings);

    /* Read each string individually */
    for (int i = 0; i < size; i++) {
        int len = read_cint(input);

        strings[i] = calloc(sizeof(char), len);
        assert(strings[i]);

        /* Read each char of the string and save in 'strings' */
        for (int j = 0; j < len; j++) 
            strings[i][j] = (char)read_byte(input);

        strings[len] = '\0';
    }

    return strings;
}

struct vm_proto *read_protos(FILE *input, struct vm_context *context)
{
    /* Create ana allocate the function prototype list */
    int size = read_cint(input);
    struct vm_proto *protos = malloc((size + 1) * sizeof(struct vm_proto));
    assert(protos);

    /* Traverse through each function prototype */
    for (int i = 0; i < size; i++) {
        /* Create our new function prototype */
        struct vm_proto *proto = malloc(sizeof(struct vm_proto));
        assert(proto);

        /* Read properties */
        proto->max_stack_size = read_byte(input);
        proto->parameters_size = read_byte(input);
        proto->is_vararg = read_byte(input);

        /* Create the instruction array */
        int sizecode = read_cint(input);
        proto->code = calloc(sizecode, sizeof(unsigned int));
        assert(proto->code);

        /* Read each instruction in the array */
        for (int j = 0; j < sizecode; j++) 
            proto->code[j] = read_int(input);

        /* Create the constant array */
        proto->sizek = read_cint(input);

        proto->constants = calloc(proto->sizek, sizeof(struct vm_value *));
        assert(proto->constants);

        /* Read each constant */
        for (int k = 0; k < proto->sizek; k++) {
            /* Handle each constant type */
            switch (read_byte(input)) {
                case CONST_STRING:
                    VM_SETSVALUE(&proto->constants[k], context->strings[read_int(input)]);
                    break;
                case CONST_NUMBER:
                    VM_SETNVALUE(&proto->constants[k], read_int(input));
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