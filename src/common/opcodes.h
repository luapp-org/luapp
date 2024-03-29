#ifndef _OPCODES_H
#define _OPCODES_H

#include <stdint.h>
#include <stdio.h>

#if defined(luaall_c)
#define LUAI_FUNC static
#define LUAI_DATA /* empty */

#elif defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 302) && defined(__ELF__)
#define LUAI_FUNC __attribute__((visibility("hidden"))) extern
#define LUAI_DATA LUAI_FUNC

#else
#define LUAI_FUNC extern
#define LUAI_DATA extern
#endif

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

    /* OP_GETTABLEN: gets a value in a table with key as number (arrays)
     * A: result register
     * B: table register
     * C: index number (0 .. 256)
     */
    OP_GETTABLEN,

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

    /* OP_Ks: sets a target register to an arithmetic operation of two integers
     * A: target register
     * B: register containing first arg
     * C: constant index (0 to 255)
     */
    OP_ADDK,
    OP_SUBK,
    OP_MULK,
    OP_DIVK,
    OP_MODK,
    OP_POWK,

    OP_UNM,
    OP_NOT,
    OP_LEN,

    OP_CONCAT,

    /* OP_JMPBACK: jumps back x instructions
     * E: amount of instructions to jump
     */
    OP_JMPBACK,

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

    /* OP_EQJMP: compares two registers, jumps if equal
     * A: result
     * B: first register
     * C: second register
     * SUB: pc jump size
     */
    OP_NEJMP,
    OP_EQJMP,

    /* OP_LTJMP: compares two registers, jumps if less than
     * A: result
     * B: first register
     * C: second register
     * SUB: pc jump size
     */
    OP_LTJMP,

    /* OP_LTJMP: compares two registers, jumps if less than or equals
     * A: result
     * B: first register
     * C: second register
     * SUB: pc jump size
     */
    OP_LEJMP,

    /* OP_JMPIF: performs a jump if R(A) is true
     * A: register
     * D: jump
     */
    OP_JMPIF,

    /* OP_JMPIFNOT: performs a jump if R(A) is not true
     * A: register
     * D: jump
     */
    OP_JMPIFNOT,

    OP_VARARG,
    OP_NOP
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
#define GETARG_Du(i) (((uint32_t)i >> 16))

/* iE
 * E:    24 bits
 */
#define GETARG_E(i) ((int32_t)i >> 8)

#define CREATE_iABC(i, a, b, c) ((uint32_t)i | (a << 8) | (b << 16) | (c << 24))
#define CREATE_iAD(i, a, d) ((uint32_t)i | (a << 8) | ((uint16_t)d << 16))
#define CREATE_iADu(i, a, du) ((uint32_t)i | (a << 8) | ((int16_t)du << 16))
#define CREATE_iE(i, e) ((uint32_t)i | ((uint32_t)e << 8))

#define NUM_OPCODES (int32_t) OP_NOP + 1

LUAI_DATA const char *const opcode_names[NUM_OPCODES + 1];

typedef enum opcode_mode { iABC, iAD, iADu, iE, SUB } opcode_t;

/* Number of list items to accumulate before a SETLIST instruction */
#define LFIELDS_PER_FLUSH 50

#endif