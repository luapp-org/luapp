/*  vm.c - only version
 *      main entry point for the VM (virtual machine)
 */

#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "lua/lauxlib.h"
#include "lua/lua.h"
#include "lua/lualib.h"

/* main() -- entry point for the VM */
int main(int argc, char **argv)
{
    char *dot;
    FILE *input;

    /* Determine if we are using stdin or file in. */
    if (optind == argc - 1) {
        dot = strrchr(argv[optind], '.');

        /* If the given file is of the correct type, init the reader */
        if (dot && (!strcmp(dot, ".out") || !strcmp(dot, ".bin")))
            input = fopen(argv[optind], "r");
        else {
            printf("Error: incorrect file type.\n");
            return 1;
        }
    } else {
        printf("Error: expected one input file, found %d files.\n", argc - optind);
        return 1;
    }

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if (luapp_loadfile(L, "?=lua", input)) {
        /* An error occured, display it and pop it from the stack */
        printf("Error: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_close(L);
    return 0;
}