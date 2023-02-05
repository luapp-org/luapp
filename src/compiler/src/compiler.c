/*  compiler.c - only version
 *      all utilities used throughout the compiler
 */

#include "compiler.h"
#include "codegen.h"
#include "ir.h"
#include "lexer.h"
#include "macro.h"
#include "node.h"
#include "parser.h"
#include "symbol.h"
#include "type.h"

#include <time.h>

/*  compiler_error - prints a compiler error to stdout based on params
 *      args: location of error, format, args
 *      rets: none
 */
void compiler_error(YYLTYPE location, const char *format, ...)
{
    va_list ap;
    printf("Error (%d, %d): ", location.first_line, location.first_column);
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
    printf("\n");
}

/*  lcompiler_error - prints a compiler error to stdout based on params (no location)
 *      args: format, args
 *      rets: none
 */
void lcompiler_error(const char *format, ...)
{
    va_list ap;
    printf("Error: ");
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
    printf("\n");
}

/*  clear - clears the given string
 *      args: string
 *      rets: none
 */
void clear(char arr[])
{
    int length = strlen(arr);
    /* remove all of the characters in the string */
    memmove(arr, arr + length, length + 1);
}

/*  compile() - compiles a file pointer of lua++ bytecode
 *      args: context, input file, output file
 *      returns: 1 on success 0 on failure
 *
 * Note: If the compiler fails on a stage, it will be saved in context->stage. So will the elapsed
 * time_t for the entire compilation process.
 */
bool compile(compiler_context_t *context, FILE *input, FILE *output)
{
    context->error_count = 0;
    context->time = clock();

    /* Run macro check */
    macro_init(context, input);

    if (context->error_count) {
        context->time = clock() - context->time;
        context->stage = "macro";
        return false;
    }

    /* Stop at macro stage if provided */
    if (strcmp(context->stage, "macro") == 0) {
        macro_print(context);
        return true;
    }

    yyscan_t lexer;
    lex_init(&lexer, context, input);

    /* Stop at lexer stage if provided */
    if (strcmp(context->stage, "lexer") == 0) {
        context->error_count = 0;
        context->time = clock();

        lex_print(lexer, &context->error_count, output);
        lex_destroy(&lexer);

        context->time = clock() - context->time; /* elapsed */
        return context->error_count ? false : true;
    }

    struct node *tree = parser_parse(&context->error_count, lexer);
    lex_destroy(&lexer);

    if (!tree) {
        context->time = clock() - context->time; /* elapsed */
        context->stage = "parser";
        return false;
    }

    /* Stop at parser stage if provided */
    if (strcmp("parser", context->stage) == 0) {
        print_ast(output, tree, true);

        context->time = clock() - context->time;
        return true;
    }

    struct type_context type_context = {context->is_strict, context->is_c_array, 0};
    type_init(&type_context);

    /* Run the type checker, it's needed for all later passes */
    type_ast_traversal(&type_context, tree, true);
    context->error_count = type_context.error_count;

    if (context->error_count) {
        context->time = clock() - context->time;
        context->stage = "type";

        type_destroy(&type_context);
        return false;
    }

    /* Stop at type stage if provided */
    if (strcmp("type", context->stage) == 0) {
        print_ast(output, tree, true);

        type_destroy(&type_context);

        context->time = clock() - context->time;
        return true;
    }

    type_destroy(&type_context);

    struct symbol_table symbol_table;
    symbol_initialize_table(&symbol_table);

    struct symbol_context symbol_context = {&symbol_table, 0};

    symbol_ast_traversal(&symbol_context, tree);
    context->error_count = symbol_context.error_count;

    if (context->error_count) {
        context->time = clock() - context->time;
        context->stage = "symbol";

        return false;
    }

    /* Stop at type symbol if provided */
    if (strcmp("symbol", context->stage) == 0) {
        symbol_print_table(output, &symbol_table);

        context->time = clock() - context->time;
        return false;
    }

    struct ir_context ir_context = {0, &symbol_table};
    ir_init(&ir_context);

    ir_context.main_proto = ir_build(&ir_context, tree);
    context->error_count = ir_context.error_count;

    ir_destroy(&ir_context);

    if (context->error_count) {
        context->time = clock() - context->time;
        context->stage = "ir";

        return false;
    }

    if (strcmp("ir", context->stage) == 0) {
        ir_print_context(output, &ir_context);

        context->time = clock() - context->time;
        return tree;
    }

    codegen_write_program(output, &ir_context);
    return true;
}

/*  usage - prints the usage for the program
 *      args: none
 *      rets: none
 */
void usage()
{
    printf("luappc -s [lexer|parser|type|symbol|ir|codgen] -o [outputfile] [inputfile]\n\n");
    printf(" -s : indicates the name of the stage to stop after.\n");
    printf("      Defaults to the last stage.\n");
    printf(" -o : name of the output file. Defaults to \"output.s\"\n\n");
    printf("You should pass the name of the file to compile.\n");
}