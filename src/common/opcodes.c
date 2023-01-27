#include "opcodes.h"

const char *const opcode_names[NUM_OPCODES + 1] = {
    "MOVE",     "LOADPN",   "LOADNN",     "LOADK",    "LOADKX",    "LOADBOOL", "LOADNIL",
    "GETUPVAL", "GETENV",   "GETGLOBAL",  "GETTABLE", "SETGLOBAL", "SETUPVAL", "SETTABLE",
    "NEWTABLE", "SELF",     "ADD",        "SUB",      "MUL",       "DIV",      "MOD",
    "POW",      "ADDK",     "SUBK",       "MULK",     "DIVK",      "MODK",     "POWK",
    "UNM",      "NOT",      "LEN",        "CONCAT",   "JMP",       "TEST",     "TESTSET",
    "CALL",     "TAILCALL", "RETURN",     "FORLOOP",  "FORPREP",   "TFORLOOP", "SETLIST",
    "CLOSE",    "CLOSURE",  "VARARGPREP", "NEJMP",    "EQJMP",     "LTJMP",    "LEJMP",
    "JMPIF",    "VARARG",   NULL};
