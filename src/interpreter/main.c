/*  main.c - entrypoint for the interpreter (combines VM and compiler)
 */

/* compiler dependencies */
#include "../compiler/src/compiler.h"

#include "../vm/src/lua/lauxlib.h"
#include "../vm/src/lua/lua.h"
#include "../vm/src/lua/lualib.h"

#include <getopt.h>

/*  print_summary - prints a quick summary of a pass (elapsed time and number of
 *  errors)
 *      args: pass name, numer of errors, start time
 *      rets: none
 */
static void print_summary(char *pass, int error_count)
{
    printf("\n%s encountered %d %s.\n", pass, error_count, (error_count == 1 ? "error" : "errors"));
}

int main(int argc, char **argv)
{
    int opt, error_count;
    size_t bufsize;
    char *dot, *buff;
    FILE *input, *output;

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

    compiler_context_t context = {"codegen", 0};
    if (!compile(&context, input, output))
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