#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common/bytecode.h"

#include "lua/lfunc.h"
#include "lua/lstate.h"
#include "lua/lstring.h"
#include "lua/luaconf.h"
#include "lua/ldebug.h"

/* Use global offset as we will need for Lua functions (luaS_newlstr) */
static size_t offset = 0;

#define read_type(data, type)                                                                      \
    ({                                                                                             \
        type value;                                                                                \
        fread(&value, sizeof(value), 1, data);                                                     \
                                                                                                   \
        value;                                                                                     \
    })

static uint32_t read_size(FILE *data)
{
    uint32_t result = 0, shift = 0;
    uint8_t byte;

    do {
        byte = read_type(data, uint8_t);
        result |= (byte & 127) << shift;
        shift += 7;
    } while (byte & 128);

    return result;
}

static TString *read_string(lua_State *L, FILE *input)
{
    uint32_t count = read_size(input);

    /* Very hacky but it works! */
    char str[LUAL_BUFFERSIZE];

    for (int32_t i = 0; i < count; i++)
        str[i] = read_type(input, uint8_t);

    return luaS_newlstr(L, str, count);
}

static TString **read_strings(lua_State *L, FILE *input, uint32_t count)
{
    /* Create new strings vector */
    TString **strings = luaM_newvector(L, count, TString *);

    for (int32_t i = 0; i < count; i++)
        strings[i] = read_string(L, input);

    return strings;
}

static Proto *read_proto(lua_State *L, FILE *input, TString **strings, TString *source)
{
    Proto *p = luaF_newproto(L);

    /* Read important proto information */
    p->source = source;
    p->maxstacksize = read_type(input, uint8_t);
    p->numparams = read_type(input, uint8_t);
    p->nups = read_type(input, uint8_t);
    p->is_vararg = read_type(input, uint8_t);

    /* Create our new instruction array */
    p->sizecode = read_size(input);
    p->code = luaM_newvector(L, p->sizecode, Instruction);

    /* Read the instruction array */
    for (int i = 0; i < p->sizecode; i++)
        p->code[i] = read_type(input, uint32_t);

    return p;
}

static Proto **read_protos(lua_State *L, FILE *input, uint32_t count, TString **strings,
                           TString *source)
{
    /* Create new protos vector */
    Proto **protos = luaM_newvector(L, count, Proto *);

    for (int32_t i = 0; i < count; i++)
        protos[i] = read_proto(L, input, strings, source);

    return protos;
}

int32_t luapp_loadfile(lua_State *L, const char *chunkname, FILE *input)
{
    /* Read version number */
    version_t version = read_type(input, uint8_t);

    /* Make sure the VM can process this bytecode version */
    if (!VERSION_ACCEPTABLE(version)) {
        lua_pushfstring(L, "incorrect version: expected version [%d..%d], got %d", MIN_VERSION,
                        MAX_VERSION, version);
        return 1;
    }

    TString *source = luaS_new(L, chunkname);

    /* Read the string table */
    uint32_t string_count = read_size(input);
    TString **strings = read_strings(L, input, string_count);

    /* Read function prototypes */
    uint32_t proto_count = read_size(input);
    Proto **protos = read_protos(L, input, proto_count, strings, source);

    /* Dispose of the string array as we don't need it anymore */
    luaM_free(L, strings);
    return 0;
}