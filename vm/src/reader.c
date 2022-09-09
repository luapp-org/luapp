#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    printf("%d\n", size);
    char **strings = malloc((size + 1) * sizeof(char *));
    assert(strings);

    /* Read each string individually */
    for (int i = 0; i < size; i++) {
        int len = read_cint(input);

        strings[i] = malloc((len + 1) * sizeof(char));
        assert(strings[i]);

        /* Read each char of the string and save in 'strings' */
        for (int j = 0; j < len; j++) 
            strings[i][j] = (char)read_byte(input);

        strings[len] = '\0';
    }

    return strings;
}

struct vm_proto *read_protos(FILE *input)
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

        printf("p->max_stack_size: %d\n", proto->max_stack_size);
        printf("p->parameters_size: %d\n", proto->parameters_size);
        printf("p->is_vararg: %d\n", proto->is_vararg);

        /* Create the instruction array */
        int sizecode = read_cint(input);
        proto->code = malloc((sizecode + 1) * sizeof(unsigned int));
        assert(proto->code);

        /* Read each instruction in the array */
        for (int j = 0; j < sizecode; j++) {
            proto->code[j] = read_int(input);
            printf("p->code[%d]: %u\n", j, proto->code[j]);
        }

        /* Create the constant array */
        int sizek = read_cint(input);
        printf("p->sizek = %d\n", sizek);
        proto->constants = malloc((sizek + 1) * sizeof(struct vm_constant));
        assert(proto->constants);

        /* Read each constant */
        for (int k = 0; k < sizek; k++) {
            /* Get the constant type to process it */
            proto->constants[k].type = read_byte(input);

            /* Handle each constant type */
            switch (proto->constants[k].type) {
                case CONSTANT_STRING:
                    proto->constants[k].data.string.symbol_id = read_int(input);
                    break;
                case CONSTANT_NUMBER:
                    proto->constants[k].data.number.value = read_int(input);
                    break;
            }
        }
    }

    return protos;
}

void read_context(FILE *input, struct vm_context *context)
{
    context->strings = read_strings(input);
    context->protos = read_protos(input);
}