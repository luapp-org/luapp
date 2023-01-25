/*  luapp.c - only version
 *      main entry point for the compiler
 */

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "codegen.h"
#include "compiler.h"
#include "ir.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"
#include "symbol.h"
#include "type.h"

/*  print_summary - prints a quick summary of a pass (elapsed time and number of
 *  errors)
 *      args: pass name, numer of errors, elapsed time
 *      rets: none
 */
static void print_summary(char *pass, int error_count, clock_t elapsed)
{
    /* Calculate the total time that the pass took (seconds) */
    double sec = (elapsed * 1000);

    printf("\n%s encountered %d %s, elapsed time: %lf second(s).\n", pass, error_count,
           (error_count == 1 ? "error" : "errors"), (sec / 1000000) / 1000);
}

/*
 * Entrypoint for the compiler.
 *
 * luapp -s [lexer|parser|type|ir|codgen] -o [outputfile] [inputfile]
 *
 * -s : indicates the name of the stage to stop after.
 *      Defaults to the last stage.
 * -o : name of the output file. Defaults to "output.s"
 *
 * You should pass the name of the file to compile.
 */
int main(int argc, char **argv)
{
    int opt, error_count;
    char *stage, *dot;
    FILE *input, *output;
    struct symbol_table symbol_table;
    yyscan_t lexer;
    time_t start;
    struct node *tree;

    stage = "codegen";
    output = stdout;
    /* Parse the command line args and store them in their corresponding vars */
    while ((opt = getopt(argc, argv, "o:s:")) != -1) {
        switch (opt) {
            case 'o':
                if (!(output = fopen(optarg, "w"))) {
                    fprintf(stdout, "Error: Unable to open output file %s: %s\n", optarg,
                            strerror(errno));
                    return 1;
                }
                break;
            case 's':
                stage = optarg;
                break;
            case ':':
            default:
                putchar('\n');
                usage();
                return 0;
        }
    }

    /* Determine if we are using stdin or file in. */
    if (optind == argc - 1) {
        /* Check if the input file is a .lpp or .lua file */
        dot = strrchr(argv[optind], '.');

        /* If the given file is of the correct type, init the lexer */
        if (dot && !strcmp(dot, ".lpp") || !strcmp(dot, ".lua")) {
            input = fopen(argv[optind], "r");
        } else {
            printf("Incorrect file type.\n");
            return 1;
        }
    } else if (optind >= argc)
        input = stdin;
    else {
        printf("Expected 1 input file, found %d.\n", argc - optind);
        return 1;
    }

    compiler_context_t context = {stage, 0};
    bool result = compile(&context, input, output);
    
    print_summary(stage, context.error_count, context.time);

    return result;
}