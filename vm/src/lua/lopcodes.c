/*
** $Id: lopcodes.c,v 1.37.1.1 2007/12/27 13:02:25 roberto Exp $
** See Copyright Notice in lua.h
*/

#define lopcodes_c
#define LUA_CORE

#include "lopcodes.h"

/* ORDER OP */

const char *const luaP_opnames[NUM_OPCODES + 1] = {
    "MOVE",     "LOADK",    "LOADBOOL", "LOADNIL", "GETUPVAL", "GETGLOBAL", "GETTABLE", "SETGLOBAL",
    "SETUPVAL", "SETTABLE", "NEWTABLE", "SELF",    "ADD",      "SUB",       "MUL",      "DIV",
    "MOD",      "POW",      "UNM",      "NOT",     "LEN",      "CONCAT",    "JMP",      "EQ",
    "LT",       "LE",       "TEST",     "TESTSET", "CALL",     "TAILCALL",  "RETURN",   "FORLOOP",
    "FORPREP",  "TFORLOOP", "SETLIST",  "CLOSE",   "CLOSURE",  "VARARG",    NULL};