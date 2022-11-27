#ifndef _OPCODES_H
#define _OPCODES_H

#include <stdio.h>

/* Main file for instruction manipulation */
enum opcode {
    OP_MOVE,

    /* OP_LOADPN: sets a target register to a positive number literal
     * A: target register
     * D: the value (0 .. 65535)
     */
    OP_LOADPN,

    /* OP_LOADNN: sets a target register to a negative number literal
     * A: target register
     * D: the value (65535 .. 0)
     * 
     * Note: The D operand is represented as an unsigned 
     */
    OP_LOADNN,
    OP_LOADK,

    /* OP_LOADKX: loads a constant from the constant list into a register
     * A: target register
     * SUB: the index in the constant table
     */
    OP_LOADKX,

    OP_LOADBOOL,
    OP_LOADNIL,
    OP_GETUPVAL,

    /* OP_GETENV: retrieves an object defined in the environment table.
     * A: target register
     * D: index in the constant table
     */
    OP_GETENV,

    OP_GETGLOBAL,
    OP_GETTABLE,

    OP_SETGLOBAL,
    OP_SETUPVAL,
    OP_SETTABLE,

    OP_NEWTABLE,

    OP_SELF,

    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_POW,
    OP_UNM,
    OP_NOT,
    OP_LEN,

    OP_CONCAT,

    OP_JMP,

    OP_EQ,
    OP_LT,
    OP_LE,

    OP_TEST,
    OP_TESTSET,

    OP_CALL,
    OP_TAILCALL,
    OP_RETURN,

    OP_FORLOOP,
    OP_FORPREP,

    OP_TFORLOOP,
    OP_SETLIST,

    OP_CLOSE,
    OP_CLOSURE,

    /* OP_VARARGPREP: prepare stack for variadic functions
     * A: number of fixed arguments
     */
    OP_VARARGPREP,
    OP_VARARG
};

/* Retrieve the one byte instruction operation code */
#define GET_OPCODE(i) ((i)&0xFF)

/* iABC
 * A:    8 bits
 * B:    8 bits
 * C:    8 bits
 */
#define GETARG_A(i) (((i) >> 8) & 0xFF)
#define GETARG_B(i) (((i) >> 16) & 0xFF)
#define GETARG_C(i) (((i) >> 24) & 0xFF)

/* iAD
 * A:    8 bits
 * D:    16 bits
 */
#define GETARG_D(i) ((int32_t)i >> 16)

/* iADu
 * A:    8 bits
 * D:    16 bits (unsigned)
 */
#define GETARG_Du(i) ((uint32_t)i >> 16)

/* iE
 * E:    24 bits
 */
#define GETARG_E(i) ((int32_t)i >> 24)

#define NUM_OPCODES (int32_t)OP_VARARG + 1

const char *const opcode_names[NUM_OPCODES + 1] = {
    "MOVE",    "LOADPN",    "LOADNN",   "LOADK",     "LOADKX",   "LOADBOOL", "LOADNIL",  "GETUPVAL",
    "GETENV",  "GETGLOBAL", "GETTABLE", "SETGLOBAL", "SETUPVAL", "SETTABLE", "NEWTABLE", "SELF",
    "ADD",     "SUB",       "MUL",      "DIV",       "MOD",      "POW",      "UNM",      "NOT",
    "LEN",     "CONCAT",    "JMP",      "EQ",        "LT",       "LE",       "TEST",     "TESTSET",
    "CALL",    "TAILCALL",  "RETURN",   "FORLOOP",   "FORPREP",  "TFORLOOP", "SETLIST",  "CLOSE",
    "CLOSURE", "VARARG",    NULL};

enum opcode_mode { iABC, iAD, iADu, iE, SUB };

#endif