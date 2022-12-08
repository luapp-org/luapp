#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua/lua.h"

/* Use global offset as we will need for Lua functions (luaS_newlstr) */
static size_t offset = 0;

#define READ_TYPE(data, type)                                                                      \
    ({                                                                                             \
        type value;                                                                                \
        fread(&value, sizeof(value), 1, data);                                                     \
                                                                                                   \
        value;                                                                                     \
    })

LUA_API int luapp_load(lua_State *L, const char *chunkname, FILE *input)
{
    return 0;
}