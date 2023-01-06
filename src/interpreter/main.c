/*  main.c - entrypoint for the interpreter (combines VM and compiler)
 */

/* compiler dependencies */
#include "../compiler/src/codegen.h"
#include "../compiler/src/compiler.h"
#include "../compiler/src/ir.h"
#include "../compiler/src/lexer.h"
#include "../compiler/src/node.h"
#include "../compiler/src/parser.h"
#include "../compiler/src/symbol.h"
#include "../compiler/src/type.h"

#include "../vm/src/lua/lauxlib.h"
#include "../vm/src/lua/lua.h"
#include "../vm/src/lua/lualib.h"

/*  print_summary - prints a quick summary of a pass (elapsed time and number of
 *  errors)
 *      args: pass name, numer of errors, start time
 *      rets: none
 */
static void print_summary(char *pass, int error_count)
{
    printf("\n%s encountered %d %s.\n", pass, error_count, (error_count == 1 ? "error" : "errors"));
}

int compile(FILE *input, FILE *output)
{
    yyscan_t lexer;
    int error_count = 0;
    struct node *tree;
    struct symbol_table symbol_table;

    lex_init(&lexer, input);

    /* Run the parser, it's needed for all later passes */
    tree = parser_parse(&error_count, lexer);
    lex_destroy(&lexer);

    /* Make sure the parser did not return any errors */
    if (tree == NULL) {
        print_summary("Parser", error_count);
        return 1;
    }

    struct type_context type_context = {true, 0};
    type_init(&type_context);

    /* Run the parser, it's needed for all later passes */
    type_ast_traversal(&type_context, tree, true);
    error_count = type_context.error_count;

    if (error_count) {
        print_summary("Type checker", error_count);
        type_destroy(&type_context);
        return 1;
    }

    type_destroy(&type_context);

    symbol_initialize_table(&symbol_table);
    struct symbol_context context = {&symbol_table, error_count};

    symbol_ast_traversal(&context, tree);
    error_count = context.error_count;

    if (error_count) {
        print_summary("Symbol table", error_count);
        return 1;
    }

    struct ir_context ir_context = {0, &symbol_table};
    ir_init(&ir_context);

    ir_context.main_proto = ir_build(&ir_context, tree);
    error_count = context.error_count;

    if (error_count) {
        print_summary("IR", error_count);
        return 1;
    }

    codegen_write_program(output, &ir_context);
    return 0;
}

int main(int argc, char **argv)
{
    int opt, error_count;
    size_t bufsize;
    char *stage, *dot, *buff;
    FILE *input, *output;
    struct symbol_table symbol_table;

    time_t start;
    struct node *tree;

    /* Determine if we are using stdin or file in. */
    if (optind == argc - 1) {
        /* Check if the input file is a .lpp or .lua file */
        dot = strrchr(argv[optind], '.');

        /* If the given file is of the correct type, init the lexer */
        if (dot && !strcmp(dot, ".lpp") || !strcmp(dot, ".lua")) {
            if (!(input = fopen(argv[optind], "r"))) {
                printf("Error: unable to open file '%s'\n", argv[optind]);
                return 1;
            }
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

    if (!(output = open_memstream(&buff, &bufsize))) {
        printf("Error: unable to write to memory stream.\n");
        return 1;
    }

    if (compile(input, output))
        return 1;

    fclose(output);

    if (!(input = fmemopen(buff, bufsize, "r"))) {
        printf("Error: unable to read memory stream.\n");
        return 1;
    }

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if (luapp_loadfile(L, "=lua++", input)) {
        /* An error occured, display it and pop it from the stack */
        printf("Error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);

        /* Close everything and return */
        lua_close(L);
        return 1;
    }

    /* Run the closure at L->top + 0 */
    lua_resume(L, 0);
    lua_close(L);
    fclose(input);
    free(buff);
    return 0;
}