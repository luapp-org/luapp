/*  vm.c - only version
 *      main entry point for the VM (virtual machine)
 */

#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "reader.h"
#include "vm.h"
#include "lib.h"

/* main() -- entry point for the VM */
int main(int argc, char **argv)
{
    char *dot;
    FILE *input;

    /* Determine if we are using stdin or file in. */
    if (optind == argc - 1) {
        /* Check if the input file is a .lpp or .lua file */
        dot = strrchr(argv[optind], '.');

        /* If the given file is of the correct type, init the reader */
        if (dot && !strcmp(dot, ".out"))
            input = fopen(argv[optind], "r");
        else {
            printf("Error: incorrect file type.\n");
            return 1;
        }
    } else {
        printf("Error: expected one input file, found %d files.\n", argc - optind);
        return 1;
    }

    struct vm_context context;
    context.error_count = 0;

    lib_open(&context);

    read_context(input, &context);

    /* Handle any errors that come up */
    if (context.error_count) 
        return 1;

    /* Execute the instructions */
    vm_execute(&context);

    lib_close(&context);

    if (context.error_count) 
        return 1;

    return 0;
}