/*  luapp.c - only version
 *      main entry point for the compiler
 */

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "compiler.h"
#include "ir.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"
#include "symbol.h"
#include "type.h"
#include "codegen.h"

/*  print_summary - prints a quick summary of a pass (elapsed time and number of
 *  errors)
 *      args: pass name, numer of errors, start time
 *      rets: none
 */
static void print_summary(char *pass, int error_count, clock_t start)
{
    /* Calculate the total time that the pass took (seconds) */
    double sec = ((clock() - start) * 1000);

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
            lex_init(&lexer, fopen(argv[optind], "r"));
        } else {
            printf("Incorrect file type.\n");
            return 1;
        }
    } else if (optind >= argc)
        lex_init(&lexer, stdin);
    else {
        printf("Expected 1 input file, found %d.\n", argc - optind);
        return 1;
    }

    /* Only enable lexer pass */
    if (!strcmp(stage, "lexer")) {
        error_count = 0;
        start = clock();
        lex_print(lexer, &error_count, output);
        lex_destroy(&lexer);

        print_summary("Lexer", error_count, start);
        return (error_count > 0) ? 1 : 0;
    }

    error_count = 0;
    start = clock();
    /* Run the parser, it's needed for all later passes */
    tree = parser_parse(&error_count, lexer);
    lex_destroy(&lexer);

    /* Make sure the parser did not return any errors */
    if (tree == NULL) {
        print_summary("Parser", error_count, start);
        return 1;
    }

    /* If the stage is "parser" print the AST */
    if (!strcmp("parser", stage)) {
        print_ast(output, tree, true);
        print_summary("Parser", error_count, start);
        return 0;
    }

    struct type_context type_context = {true, 0};
    type_init(&type_context);

    /* Run the parser, it's needed for all later passes */
    type_ast_traversal(&type_context, tree, true);
    error_count = type_context.error_count;

    if (error_count) {
        print_summary("Type checker", error_count, start);
        type_destroy(&type_context);
        return 1;
    }

    /* If the stage is "type" print the type tree */
    if (!strcmp("type", stage)) {
        print_ast(output, tree, true);
        print_summary("Type checker", error_count, start);
        type_destroy(&type_context);
        return 0;
    }

    type_destroy(&type_context);

    symbol_initialize_table(&symbol_table);
    struct symbol_context context = {&symbol_table, error_count};

    symbol_ast_traversal(&context, tree);
    error_count = context.error_count;

    if (error_count) {
        print_summary("Symbol table", error_count, start);
        return 1;
    }

    /* If the stage is "symbol" print the table */
    if (!strcmp("symbol", stage)) {
        symbol_print_table(output, &symbol_table);
        print_summary("Symbol table", error_count, start);
        return 0;
    }

    struct ir_context ir_context = {0, &symbol_table};
    ir_init(&ir_context);

    ir_context.main_proto = ir_build(&ir_context, tree);
    error_count = context.error_count;

    if (error_count) {
        print_summary("IR", error_count, start);
        return 1;
    }

    /* If the stage is "ir" then print the instructions */
    if (!strcmp("ir", stage)) {
        ir_print_context(output, &ir_context);
        print_summary("IR", error_count, start);
        return 0;
    }

    codegen_write_program(output, &ir_context);
    return 0;
}