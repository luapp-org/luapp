/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 14 "src/parser.y"

    #include <stdio.h>

    #include "compiler.h"
    #include "node.h"
    #include "type.h"

    #ifndef YY_TYPEDEF_YY_SCANNER_T
    #define YY_TYPEDEF_YY_SCANNER_T
    typedef void *yyscan_t;
    #endif

    #include "parser.tab.h"
    #include "lexer.yy.h"

    #define YYERROR_VERBOSE
    static void yyerror(YYLTYPE *loc, YYSTYPE *root,
                      int *error_count, yyscan_t scanner,
                      char const *s);

#line 91 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER_T = 258,
    NUMBER_T = 259,
    STRING_T = 260,
    AND_T = 261,
    BREAK_T = 262,
    DO_T = 263,
    ELSE_T = 264,
    ELSEIF_T = 265,
    END_T = 266,
    FALSE_T = 267,
    TRUE_T = 268,
    FOR_T = 269,
    FUNCTION_T = 270,
    IF_T = 271,
    IN_T = 272,
    LOCAL_T = 273,
    NIL_T = 274,
    NOT_T = 275,
    OR_T = 276,
    REPEAT_T = 277,
    RETURN_T = 278,
    THEN_T = 279,
    UNTIL_T = 280,
    WHILE_T = 281,
    TNUMBER_T = 282,
    TSTRING_T = 283,
    TBOOLEAN_T = 284,
    TANY_T = 285,
    TARRAY_T = 286,
    TTABLE_T = 287,
    PLUS_T = 288,
    MINUS_T = 289,
    ASTERISK_T = 290,
    SLASH_T = 291,
    PERCENT_T = 292,
    EQUAL_T = 293,
    LEFT_PARAN_T = 294,
    RIGHT_PARAN_T = 295,
    RIGHT_SQUARE_T = 296,
    LEFT_SQUARE_T = 297,
    CARROT_T = 298,
    GREATER_THAN_T = 299,
    LESS_THAN_T = 300,
    SQUIGGLE_T = 301,
    COLON_T = 302,
    POUND_T = 303,
    DOT_T = 304,
    COMMA_T = 305,
    LEFT_BRACKET_T = 306,
    RIGHT_BRACKET_T = 307,
    DOUBLE_EQUAL_T = 308,
    NOT_EQUAL_T = 309,
    GREATER_EQUAL_T = 310,
    LESS_EQUAL_T = 311,
    CONCAT_T = 312,
    VARARG_T = 313,
    PLUS_EQUAL_T = 314,
    MINUS_EQUAL_T = 315,
    ASTERISK_EQUAL_T = 316,
    SLASH_EQUAL_T = 317,
    MOD_EQUAL_T = 318,
    CARROT_EQUAL_T = 319,
    CONCAT_EQUAL_T = 320
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (YYSTYPE *root, int *error_count, yyscan_t lexer);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  61
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1155

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  228

#define YYUNDEFTOK  2
#define YYMAXUTOK   320


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   113,   113,   115,   117,   119,   121,   123,   125,   127,
     129,   131,   133,   135,   137,   139,   141,   146,   148,   150,
     155,   156,   161,   163,   165,   170,   171,   176,   177,   182,
     184,   186,   188,   190,   192,   194,   196,   201,   203,   207,
     209,   214,   219,   221,   222,   227,   232,   233,   235,   240,
     242,   243,   248,   250,   252,   256,   258,   263,   263,   263,
     263,   263,   263,   264,   264,   264,   264,   265,   266,   271,
     282,   284,   289,   291,   293,   308,   310,   312,   314,   322,
     324,   329,   331,   333,   335,   337,   339,   341,   343,   348,
     350,   352,   354,   356,   358,   360,   362,   364,   366,   368,
     370,   372,   374,   380,   382,   384,   389,   391,   393
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER_T", "NUMBER_T", "STRING_T",
  "AND_T", "BREAK_T", "DO_T", "ELSE_T", "ELSEIF_T", "END_T", "FALSE_T",
  "TRUE_T", "FOR_T", "FUNCTION_T", "IF_T", "IN_T", "LOCAL_T", "NIL_T",
  "NOT_T", "OR_T", "REPEAT_T", "RETURN_T", "THEN_T", "UNTIL_T", "WHILE_T",
  "TNUMBER_T", "TSTRING_T", "TBOOLEAN_T", "TANY_T", "TARRAY_T", "TTABLE_T",
  "PLUS_T", "MINUS_T", "ASTERISK_T", "SLASH_T", "PERCENT_T", "EQUAL_T",
  "LEFT_PARAN_T", "RIGHT_PARAN_T", "RIGHT_SQUARE_T", "LEFT_SQUARE_T",
  "CARROT_T", "GREATER_THAN_T", "LESS_THAN_T", "SQUIGGLE_T", "COLON_T",
  "POUND_T", "DOT_T", "COMMA_T", "LEFT_BRACKET_T", "RIGHT_BRACKET_T",
  "DOUBLE_EQUAL_T", "NOT_EQUAL_T", "GREATER_EQUAL_T", "LESS_EQUAL_T",
  "CONCAT_T", "VARARG_T", "PLUS_EQUAL_T", "MINUS_EQUAL_T",
  "ASTERISK_EQUAL_T", "SLASH_EQUAL_T", "MOD_EQUAL_T", "CARROT_EQUAL_T",
  "CONCAT_EQUAL_T", "$accept", "binary_operation", "unary_operation",
  "expression_list", "parameter_list", "name_list", "type_list", "type",
  "name_type", "array_constructor", "pair", "pair_list",
  "table_constructor", "variable", "prefix_expression", "arguments",
  "call", "expression", "program", "variable_list", "else_body",
  "function_body", "single_assignment", "assignment", "statement", "block",
  "last_statement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320
};
# endif

#define YYPACT_NINF (-130)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-51)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1116,  -130,  -130,  1116,     7,   458,     6,  1116,   458,   458,
     458,    19,    39,    40,    12,   395,  -130,  -130,  1116,  -130,
     872,   130,    -9,   -25,   -23,  -130,   -34,  -130,  -130,  -130,
    -130,   -22,  -130,   458,   458,   458,   433,  -130,  -130,  -130,
    -130,  -130,  -130,    39,   246,   -28,    20,   -16,   -21,   894,
    -130,   515,   555,   580,     8,  -130,    92,   458,    24,    25,
    -130,  -130,   458,   458,   458,   458,   458,   458,   458,   458,
    -130,  -130,   346,   458,   458,    27,   458,   458,     2,  -130,
     770,   770,   770,   458,  -130,   -12,   -19,   -11,   458,   458,
    1116,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   -22,   458,   458,   458,  1116,  -130,
    -130,  -130,    10,   620,     9,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,    17,    18,
     346,  -130,  -130,    43,   770,  -130,   770,   490,   107,  -130,
      13,    14,   645,  -130,    15,  -130,   770,   770,   828,   770,
     770,   770,   770,   770,   770,   770,   770,   770,   770,   770,
     770,   770,  -130,  -130,   685,  -130,   918,  -130,  -130,  -130,
     346,   346,    33,    26,  1116,  1116,   458,   346,   940,   794,
      22,    29,  -130,  1116,   458,  -130,  -130,  -130,  -130,    21,
      34,    36,   346,   962,   984,   725,  1116,  -130,   346,  1006,
    -130,   458,  1028,   730,  -130,   346,   346,  -130,  -130,  -130,
    1116,  1050,  1116,  -130,   770,  -130,  1116,    41,  -130,  1072,
    -130,  1094,   850,  -130,  -130,  -130,  -130,  -130
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
     103,    46,   108,   103,     0,     0,     0,   103,   107,     0,
       0,    70,     0,    90,     0,     0,    89,   104,    69,   102,
       0,    46,     0,    25,    49,    50,     0,    60,    61,    58,
      59,     0,    57,     0,     0,     0,     0,    62,    63,    64,
      66,    67,    49,    65,     0,    38,     0,    99,    25,     0,
     106,    20,     0,     0,     0,    54,     0,     0,     0,     0,
      55,     1,     0,     0,     0,     0,     0,     0,     0,     0,
     105,    91,     0,     0,     0,     0,     0,     0,     0,    68,
      18,    17,    19,     0,    40,     0,    43,     0,     0,     0,
     103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   103,    51,
      71,    52,     0,     0,     0,    48,    81,    82,    83,    84,
      85,    86,    87,    88,    29,    30,    31,    32,     0,     0,
       0,    33,    37,     0,    80,    26,    79,     0,   103,    24,
       0,    22,     0,    39,    42,    45,    15,    16,     0,     2,
       3,     4,     5,     7,     6,    10,     9,    14,    13,    11,
      12,     8,   101,   100,     0,    21,     0,    53,    47,    56,
       0,     0,     0,    27,   103,   103,     0,     0,     0,   103,
       0,     0,    44,   103,     0,    94,    95,    93,    92,     0,
       0,     0,     0,     0,     0,     0,   103,    78,     0,     0,
      23,     0,     0,     0,    34,     0,     0,    28,    98,    96,
     103,     0,   103,    76,    41,    74,   103,     0,    36,     0,
      77,     0,     0,    35,    97,    75,    73,    72
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,  -130,   -30,  -130,    -4,   -79,   -71,    87,  -130,
    -130,   -52,  -130,     0,    52,   -20,   149,   329,  -130,    48,
    -129,    -1,  -130,  -130,   188,   134,  -130
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    38,    39,    50,   140,    22,   172,   173,    48,    40,
      86,    87,    41,    42,    43,    60,    25,    51,    14,    15,
     186,    79,    26,    16,    17,    18,    19
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      11,   132,    47,    11,    24,    45,    85,    11,    73,    45,
      21,     1,    61,    74,    55,    76,    77,    78,    11,    72,
      11,    46,   105,   104,   -49,    75,   112,   114,   115,    75,
      45,   144,   116,   117,   118,   119,   120,   121,   122,   123,
     143,   145,   138,   133,    55,   -50,    10,    10,    56,    11,
     167,   174,    12,   179,    11,    12,    12,    83,   -49,    12,
     139,   -49,   170,   171,   180,   204,   -49,   201,   -49,    54,
      12,   135,    12,   191,   141,   163,   192,   165,    56,   -50,
     200,    57,   -50,   206,   205,   223,    58,   -50,    59,   -50,
      11,    23,   182,   227,   169,     1,    27,    28,   196,   189,
     190,    12,   110,   162,    29,    30,    12,    31,    11,     0,
       1,    32,    33,   207,     2,     3,     0,     0,     0,   212,
       0,     4,     0,     5,     0,     6,    34,   218,     0,     7,
       8,    10,   111,     9,   217,     0,     0,    20,    11,     0,
      35,    49,    12,    36,     0,     0,    10,   -38,    11,    13,
      37,     0,    13,     0,   177,     0,    13,     0,     0,     0,
      12,     0,     0,     0,     0,     0,    11,    13,   -38,    13,
       0,     0,     0,     0,    11,    11,     0,    72,    11,    11,
     -38,     0,     0,    11,     0,     0,     0,     0,     0,     0,
      12,     0,     0,    11,    11,     0,    11,     0,    13,    11,
      12,     0,    11,     0,     0,     0,    70,     0,    70,     0,
      11,    11,    11,     0,     0,     0,    11,     0,    12,    11,
       0,    11,    11,     0,   148,     0,    12,    12,     0,     0,
      12,    12,     0,     0,     0,    12,     0,    70,     0,    13,
       0,     0,   166,     0,     0,    12,    12,     0,    12,     0,
       0,    12,    88,     0,    12,     0,     0,    13,     0,     0,
       0,     0,    12,    12,    12,     0,     0,    89,    12,     0,
      90,    12,   178,    12,    12,     0,     0,     0,     0,    91,
      92,    93,    94,    95,     0,     0,     0,    13,     0,    96,
      97,    98,     0,     0,     0,     0,     0,    13,     0,    99,
     100,   101,   102,   103,     0,     0,     0,     0,   193,   194,
       0,     0,     0,   199,     0,    13,     0,   202,     0,     0,
       0,     0,     0,    13,    13,     0,     0,    13,    13,     0,
     211,     0,    13,     0,    44,     0,    70,     0,    52,    53,
       0,     0,    13,    13,   219,    13,   221,     0,    13,     0,
     222,    13,     0,     0,    70,     0,     0,     0,     0,    13,
      13,    13,    80,    81,    82,    13,    70,     0,    13,     0,
      13,    13,     0,   124,   125,   126,   127,   128,   129,     0,
       0,    70,    70,     0,     0,   130,   113,    70,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,    70,
       0,     0,     0,   134,   131,   136,   137,    70,     0,    70,
      70,     0,   142,     0,     0,     0,     0,   146,   147,     0,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,    62,     0,   164,     1,    27,    28,     0,
       0,     0,     0,     0,     0,    29,    30,     0,    31,     0,
       0,     0,    32,    33,    63,    64,    65,    66,    67,    68,
      69,     1,    27,    28,     0,     0,     0,    34,     0,     0,
      29,    30,    10,    31,     0,    83,     0,    32,    33,     0,
       0,    35,     0,     0,    36,    84,     0,     0,     0,     0,
       0,    37,    34,     0,     0,     0,    88,    10,   175,     0,
       0,     0,     0,     0,     0,   195,    35,     0,     0,    36,
       0,    89,     0,   203,     0,     0,    37,     0,     0,     0,
       0,    88,     0,    91,    92,    93,    94,    95,     0,     0,
     214,     0,     0,    96,    97,    98,    89,     0,     0,     0,
     176,     0,     0,    99,   100,   101,   102,   103,    91,    92,
      93,    94,    95,     0,     0,     0,     0,     0,    96,    97,
      98,    88,     0,   108,     0,   107,     0,     0,    99,   100,
     101,   102,   103,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,    91,    92,
      93,    94,    95,     0,     0,     0,     0,     0,    96,    97,
      98,    89,     0,     0,     0,     0,     0,     0,    99,   100,
     101,   102,   103,    91,    92,    93,    94,    95,     0,     0,
     109,     0,     0,    96,    97,    98,    88,     0,     0,     0,
       0,     0,     0,    99,   100,   101,   102,   103,     0,     0,
       0,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,     0,    91,    92,    93,    94,    95,     0,     0,
       0,   168,     0,    96,    97,    98,    89,     0,     0,     0,
       0,     0,     0,    99,   100,   101,   102,   103,    91,    92,
      93,    94,    95,     0,     0,     0,   181,     0,    96,    97,
      98,    88,     0,     0,     0,     0,   187,     0,    99,   100,
     101,   102,   103,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,    92,
      93,    94,    95,     0,     0,     0,     0,     0,    96,    97,
      98,    88,     0,   210,     0,     0,    88,     0,    99,   100,
     101,   102,   103,     0,     0,     0,    89,     0,     0,     0,
       0,    89,     0,     0,   216,     0,     0,     0,    91,    92,
      93,    94,    95,    91,    92,    93,    94,    95,    96,    97,
      98,     0,     0,    96,    97,    98,    88,     0,    99,   100,
     101,   102,   103,    99,   100,   101,   102,   103,     0,     0,
       0,    89,     0,     0,     0,     0,     0,     1,     0,     0,
       0,     2,     3,    91,    92,    93,    94,    95,     4,     0,
       5,     0,     6,    96,    97,    98,     7,     8,     0,     0,
       9,     0,     0,    99,   100,   101,   102,   103,     0,     0,
       0,     1,     0,    10,     0,     2,     3,   183,   184,   185,
       0,   198,     4,     0,     5,     0,     6,     0,     0,     0,
       7,     8,     0,     1,     9,     0,     0,     2,     3,   183,
     184,   226,     0,     0,     4,     0,     5,    10,     6,     0,
       0,     0,     7,     8,     0,     1,     9,     0,     0,     2,
       3,     0,     0,    71,     0,     0,     4,     0,     5,    10,
       6,     0,     0,     0,     7,     8,     0,     1,     9,     0,
       0,     2,     3,     0,     0,     0,     0,     0,     4,     0,
       5,    10,     6,     0,     0,     0,     7,     8,     0,   106,
       9,     1,     0,     0,     0,     2,     3,     0,     0,   188,
       0,     0,     4,    10,     5,     0,     6,     0,     0,     0,
       7,     8,     0,     1,     9,     0,     0,     2,     3,     0,
       0,   197,     0,     0,     4,     0,     5,    10,     6,     0,
       0,     0,     7,     8,     0,     1,     9,     0,     0,     2,
       3,     0,     0,   208,     0,     0,     4,     0,     5,    10,
       6,     0,     0,     0,     7,     8,     0,     1,     9,     0,
       0,     2,     3,     0,     0,   209,     0,     0,     4,     0,
       5,    10,     6,     0,     0,     0,     7,     8,     0,     1,
       9,     0,     0,     2,     3,     0,     0,   213,     0,     0,
       4,     0,     5,    10,     6,     0,     0,     0,     7,     8,
       0,     1,     9,     0,     0,     2,     3,     0,     0,   215,
       0,     0,     4,     0,     5,    10,     6,     0,     0,     0,
       7,     8,     0,     1,     9,     0,     0,     2,     3,     0,
       0,   220,     0,     0,     4,     0,     5,    10,     6,     0,
       0,     0,     7,     8,     0,     1,     9,     0,     0,     2,
       3,     0,     0,   224,     0,     0,     4,     0,     5,    10,
       6,     0,     0,     0,     7,     8,     0,     1,     9,     0,
       0,     2,     3,     0,     0,   225,     0,     0,     4,     0,
       5,    10,     6,     0,     0,     0,     7,     8,     0,     1,
       9,     0,     0,     2,     3,     0,     0,     0,     0,     0,
       4,     0,     5,    10,     6,     0,     0,     0,     7,     8,
       0,     0,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    10
};

static const yytype_int16 yycheck[] =
{
       0,    72,     6,     3,     4,     3,    36,     7,    17,     3,
       3,     3,     0,    38,     5,    38,    50,    39,    18,    47,
      20,    15,    38,     3,     5,    50,    56,     3,     3,    50,
       3,    50,    62,    63,    64,    65,    66,    67,    68,    69,
      52,    52,    40,    73,     5,     5,    39,    39,    39,    49,
      40,     8,     0,    40,    54,     3,     4,    42,    39,     7,
      58,    42,    45,    45,    50,    44,    47,    38,    49,    50,
      18,    75,    20,    40,    78,   105,    50,   107,    39,    39,
      58,    42,    42,    47,    50,    44,    47,    47,    49,    49,
      90,     4,   144,   222,   114,     3,     4,     5,   177,   170,
     171,    49,    54,   104,    12,    13,    54,    15,   108,    -1,
       3,    19,    20,   192,     7,     8,    -1,    -1,    -1,   198,
      -1,    14,    -1,    16,    -1,    18,    34,   206,    -1,    22,
      23,    39,    40,    26,   205,    -1,    -1,     3,   138,    -1,
      48,     7,    90,    51,    -1,    -1,    39,    17,   148,     0,
      58,    -1,     3,    -1,    47,    -1,     7,    -1,    -1,    -1,
     108,    -1,    -1,    -1,    -1,    -1,   166,    18,    38,    20,
      -1,    -1,    -1,    -1,   174,   175,    -1,    47,   178,   179,
      50,    -1,    -1,   183,    -1,    -1,    -1,    -1,    -1,    -1,
     138,    -1,    -1,   193,   194,    -1,   196,    -1,    49,   199,
     148,    -1,   202,    -1,    -1,    -1,    18,    -1,    20,    -1,
     210,   211,   212,    -1,    -1,    -1,   216,    -1,   166,   219,
      -1,   221,   222,    -1,    90,    -1,   174,   175,    -1,    -1,
     178,   179,    -1,    -1,    -1,   183,    -1,    49,    -1,    90,
      -1,    -1,   108,    -1,    -1,   193,   194,    -1,   196,    -1,
      -1,   199,     6,    -1,   202,    -1,    -1,   108,    -1,    -1,
      -1,    -1,   210,   211,   212,    -1,    -1,    21,   216,    -1,
      24,   219,   138,   221,   222,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    -1,    -1,    -1,   138,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,   148,    -1,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,   174,   175,
      -1,    -1,    -1,   179,    -1,   166,    -1,   183,    -1,    -1,
      -1,    -1,    -1,   174,   175,    -1,    -1,   178,   179,    -1,
     196,    -1,   183,    -1,     5,    -1,   148,    -1,     9,    10,
      -1,    -1,   193,   194,   210,   196,   212,    -1,   199,    -1,
     216,   202,    -1,    -1,   166,    -1,    -1,    -1,    -1,   210,
     211,   212,    33,    34,    35,   216,   178,    -1,   219,    -1,
     221,   222,    -1,    27,    28,    29,    30,    31,    32,    -1,
      -1,   193,   194,    -1,    -1,    39,    57,   199,    -1,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    74,    58,    76,    77,   219,    -1,   221,
     222,    -1,    83,    -1,    -1,    -1,    -1,    88,    89,    -1,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    38,    -1,   106,     3,     4,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    -1,    15,    -1,
      -1,    -1,    19,    20,    59,    60,    61,    62,    63,    64,
      65,     3,     4,     5,    -1,    -1,    -1,    34,    -1,    -1,
      12,    13,    39,    15,    -1,    42,    -1,    19,    20,    -1,
      -1,    48,    -1,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    34,    -1,    -1,    -1,     6,    39,     8,    -1,
      -1,    -1,    -1,    -1,    -1,   176,    48,    -1,    -1,    51,
      -1,    21,    -1,   184,    -1,    -1,    58,    -1,    -1,    -1,
      -1,     6,    -1,    33,    34,    35,    36,    37,    -1,    -1,
     201,    -1,    -1,    43,    44,    45,    21,    -1,    -1,    -1,
      50,    -1,    -1,    53,    54,    55,    56,    57,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,     6,    -1,     8,    -1,    50,    -1,    -1,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,    -1,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    21,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    33,    34,    35,    36,    37,    -1,    -1,
      40,    -1,    -1,    43,    44,    45,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,    -1,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    41,    -1,    43,    44,    45,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    41,    -1,    43,    44,
      45,     6,    -1,    -1,    -1,    -1,    11,    -1,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,     6,    -1,     8,    -1,    -1,     6,    -1,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    21,    -1,    -1,    24,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    33,    34,    35,    36,    37,    43,    44,
      45,    -1,    -1,    43,    44,    45,     6,    -1,    53,    54,
      55,    56,    57,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    21,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      -1,     7,     8,    33,    34,    35,    36,    37,    14,    -1,
      16,    -1,    18,    43,    44,    45,    22,    23,    -1,    -1,
      26,    -1,    -1,    53,    54,    55,    56,    57,    -1,    -1,
      -1,     3,    -1,    39,    -1,     7,     8,     9,    10,    11,
      -1,    47,    14,    -1,    16,    -1,    18,    -1,    -1,    -1,
      22,    23,    -1,     3,    26,    -1,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    14,    -1,    16,    39,    18,    -1,
      -1,    -1,    22,    23,    -1,     3,    26,    -1,    -1,     7,
       8,    -1,    -1,    11,    -1,    -1,    14,    -1,    16,    39,
      18,    -1,    -1,    -1,    22,    23,    -1,     3,    26,    -1,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      16,    39,    18,    -1,    -1,    -1,    22,    23,    -1,    25,
      26,     3,    -1,    -1,    -1,     7,     8,    -1,    -1,    11,
      -1,    -1,    14,    39,    16,    -1,    18,    -1,    -1,    -1,
      22,    23,    -1,     3,    26,    -1,    -1,     7,     8,    -1,
      -1,    11,    -1,    -1,    14,    -1,    16,    39,    18,    -1,
      -1,    -1,    22,    23,    -1,     3,    26,    -1,    -1,     7,
       8,    -1,    -1,    11,    -1,    -1,    14,    -1,    16,    39,
      18,    -1,    -1,    -1,    22,    23,    -1,     3,    26,    -1,
      -1,     7,     8,    -1,    -1,    11,    -1,    -1,    14,    -1,
      16,    39,    18,    -1,    -1,    -1,    22,    23,    -1,     3,
      26,    -1,    -1,     7,     8,    -1,    -1,    11,    -1,    -1,
      14,    -1,    16,    39,    18,    -1,    -1,    -1,    22,    23,
      -1,     3,    26,    -1,    -1,     7,     8,    -1,    -1,    11,
      -1,    -1,    14,    -1,    16,    39,    18,    -1,    -1,    -1,
      22,    23,    -1,     3,    26,    -1,    -1,     7,     8,    -1,
      -1,    11,    -1,    -1,    14,    -1,    16,    39,    18,    -1,
      -1,    -1,    22,    23,    -1,     3,    26,    -1,    -1,     7,
       8,    -1,    -1,    11,    -1,    -1,    14,    -1,    16,    39,
      18,    -1,    -1,    -1,    22,    23,    -1,     3,    26,    -1,
      -1,     7,     8,    -1,    -1,    11,    -1,    -1,    14,    -1,
      16,    39,    18,    -1,    -1,    -1,    22,    23,    -1,     3,
      26,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    16,    39,    18,    -1,    -1,    -1,    22,    23,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,     8,    14,    16,    18,    22,    23,    26,
      39,    79,    80,    82,    84,    85,    89,    90,    91,    92,
      91,     3,    71,    74,    79,    82,    88,     4,     5,    12,
      13,    15,    19,    20,    34,    48,    51,    58,    67,    68,
      75,    78,    79,    80,    83,     3,    15,    71,    74,    91,
      69,    83,    83,    83,    50,     5,    39,    42,    47,    49,
      81,     0,    38,    59,    60,    61,    62,    63,    64,    65,
      90,    11,    47,    17,    38,    50,    38,    50,    39,    87,
      83,    83,    83,    42,    52,    69,    76,    77,     6,    21,
      24,    33,    34,    35,    36,    37,    43,    44,    45,    53,
      54,    55,    56,    57,     3,    38,    25,    50,     8,    40,
      85,    40,    69,    83,     3,     3,    69,    69,    69,    69,
      69,    69,    69,    69,    27,    28,    29,    30,    31,    32,
      39,    58,    73,    69,    83,    71,    83,    83,    40,    58,
      70,    71,    83,    52,    50,    52,    83,    83,    91,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    87,    69,    83,    69,    91,    40,    41,    81,
      45,    45,    72,    73,     8,     8,    50,    47,    91,    40,
      50,    41,    77,     9,    10,    11,    86,    11,    11,    73,
      73,    40,    50,    91,    91,    83,    72,    11,    47,    91,
      58,    38,    91,    83,    44,    50,    47,    72,    11,    11,
       8,    91,    72,    11,    83,    11,    24,    73,    72,    91,
      11,    91,    91,    44,    11,    11,    11,    86
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    68,    68,
      69,    69,    70,    70,    70,    71,    71,    72,    72,    73,
      73,    73,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    76,    77,    77,    77,    78,    79,    79,    79,    80,
      80,    80,    81,    81,    81,    82,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    84,
      85,    85,    86,    86,    86,    87,    87,    87,    87,    88,
      88,    89,    89,    89,    89,    89,    89,    89,    89,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    92,    92,    92
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       1,     3,     1,     3,     1,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     4,     6,     5,     3,     1,     3,
       2,     5,     0,     1,     3,     3,     1,     4,     3,     1,
       1,     3,     2,     3,     1,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     3,     5,     5,     3,     7,     5,     6,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     5,     5,     5,     5,     7,     9,     7,     2,
       4,     4,     1,     0,     1,     2,     2,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, root, error_count, lexer, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, root, error_count, lexer); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, YYSTYPE *root, int *error_count, yyscan_t lexer)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (root);
  YYUSE (error_count);
  YYUSE (lexer);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, YYSTYPE *root, int *error_count, yyscan_t lexer)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, root, error_count, lexer);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, YYSTYPE *root, int *error_count, yyscan_t lexer)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , root, error_count, lexer);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, root, error_count, lexer); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, YYSTYPE *root, int *error_count, yyscan_t lexer)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (root);
  YYUSE (error_count);
  YYUSE (lexer);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (YYSTYPE *root, int *error_count, yyscan_t lexer)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, lexer);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 114 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_ADD, yyvsp[-2], yyvsp[0]); }
#line 1849 "parser.tab.c"
    break;

  case 3:
#line 116 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_SUB, yyvsp[-2], yyvsp[0]); }
#line 1855 "parser.tab.c"
    break;

  case 4:
#line 118 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_MUL, yyvsp[-2], yyvsp[0]); }
#line 1861 "parser.tab.c"
    break;

  case 5:
#line 120 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_DIV, yyvsp[-2], yyvsp[0]); }
#line 1867 "parser.tab.c"
    break;

  case 6:
#line 122 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_POW, yyvsp[-2], yyvsp[0]); }
#line 1873 "parser.tab.c"
    break;

  case 7:
#line 124 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_MOD, yyvsp[-2], yyvsp[0]); }
#line 1879 "parser.tab.c"
    break;

  case 8:
#line 126 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_CONCAT, yyvsp[-2], yyvsp[0]); }
#line 1885 "parser.tab.c"
    break;

  case 9:
#line 128 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_LT, yyvsp[-2], yyvsp[0]); }
#line 1891 "parser.tab.c"
    break;

  case 10:
#line 130 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_GT, yyvsp[-2], yyvsp[0]); }
#line 1897 "parser.tab.c"
    break;

  case 11:
#line 132 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_GE, yyvsp[-2], yyvsp[0]); }
#line 1903 "parser.tab.c"
    break;

  case 12:
#line 134 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_LE, yyvsp[-2], yyvsp[0]); }
#line 1909 "parser.tab.c"
    break;

  case 13:
#line 136 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_NE, yyvsp[-2], yyvsp[0]); }
#line 1915 "parser.tab.c"
    break;

  case 14:
#line 138 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_EQ, yyvsp[-2], yyvsp[0]); }
#line 1921 "parser.tab.c"
    break;

  case 15:
#line 140 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_AND, yyvsp[-2], yyvsp[0]); }
#line 1927 "parser.tab.c"
    break;

  case 16:
#line 142 "src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_OR, yyvsp[-2], yyvsp[0]); }
#line 1933 "parser.tab.c"
    break;

  case 17:
#line 147 "src/parser.y"
      { yyval = node_unary_operation((yyloc), UNOP_NEG, yyvsp[0]); }
#line 1939 "parser.tab.c"
    break;

  case 18:
#line 149 "src/parser.y"
      { yyval = node_unary_operation((yyloc), UNOP_NOT, yyvsp[0]); }
#line 1945 "parser.tab.c"
    break;

  case 19:
#line 151 "src/parser.y"
      { yyval = node_unary_operation((yyloc), UNOP_LEN, yyvsp[0]); }
#line 1951 "parser.tab.c"
    break;

  case 21:
#line 157 "src/parser.y"
        { yyval = node_expression_list((yyloc), yyvsp[0], yyvsp[-2]); }
#line 1957 "parser.tab.c"
    break;

  case 22:
#line 162 "src/parser.y"
        { yyval = node_parameter_list((yyloc), yyvsp[0], NULL); }
#line 1963 "parser.tab.c"
    break;

  case 23:
#line 164 "src/parser.y"
        { yyval = node_parameter_list((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1969 "parser.tab.c"
    break;

  case 24:
#line 166 "src/parser.y"
        { yyval = node_parameter_list((yyloc), NULL, yyvsp[0]); }
#line 1975 "parser.tab.c"
    break;

  case 26:
#line 172 "src/parser.y"
        { yyval = node_name_list((yyloc), yyvsp[0], yyvsp[-2]); }
#line 1981 "parser.tab.c"
    break;

  case 28:
#line 178 "src/parser.y"
        { yyval = node_type_list((yyloc), yyvsp[0], yyvsp[-2]); }
#line 1987 "parser.tab.c"
    break;

  case 29:
#line 183 "src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_NUMBER)); }
#line 1993 "parser.tab.c"
    break;

  case 30:
#line 185 "src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_STRING)); }
#line 1999 "parser.tab.c"
    break;

  case 31:
#line 187 "src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_BOOLEAN)); }
#line 2005 "parser.tab.c"
    break;

  case 32:
#line 189 "src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_ANY)); }
#line 2011 "parser.tab.c"
    break;

  case 33:
#line 191 "src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_VARARG)); }
#line 2017 "parser.tab.c"
    break;

  case 34:
#line 193 "src/parser.y"
        { yyval = node_type_array((yyloc), yyvsp[-1]); }
#line 2023 "parser.tab.c"
    break;

  case 35:
#line 195 "src/parser.y"
        { yyval = node_type_table((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 2029 "parser.tab.c"
    break;

  case 36:
#line 197 "src/parser.y"
        { yyval = node_type_function((yyloc), yyvsp[-3], yyvsp[0]); }
#line 2035 "parser.tab.c"
    break;

  case 37:
#line 202 "src/parser.y"
        { yyval = node_type_annotation((yyloc), yyvsp[-2], yyvsp[0]); }
#line 2041 "parser.tab.c"
    break;

  case 39:
#line 208 "src/parser.y"
        { yyval = node_array_constructor((yyloc), yyvsp[-1]); }
#line 2047 "parser.tab.c"
    break;

  case 40:
#line 210 "src/parser.y"
        { yyval = node_array_constructor((yyloc), NULL); }
#line 2053 "parser.tab.c"
    break;

  case 41:
#line 215 "src/parser.y"
        { yyval = node_key_value_pair((yyloc), yyvsp[-3], yyvsp[0]); }
#line 2059 "parser.tab.c"
    break;

  case 42:
#line 220 "src/parser.y"
        { yyval = NULL; }
#line 2065 "parser.tab.c"
    break;

  case 44:
#line 223 "src/parser.y"
        { yyval = node_expression_list((yyloc), yyvsp[-2], yyvsp[0]); }
#line 2071 "parser.tab.c"
    break;

  case 45:
#line 228 "src/parser.y"
        { yyval = node_table_constructor((yyloc), yyvsp[-1]); }
#line 2077 "parser.tab.c"
    break;

  case 47:
#line 234 "src/parser.y"
        { yyval = node_expression_index((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 2083 "parser.tab.c"
    break;

  case 48:
#line 236 "src/parser.y"
        { yyval = node_name_index((yyloc), yyvsp[-2], yyvsp[0], false); }
#line 2089 "parser.tab.c"
    break;

  case 49:
#line 241 "src/parser.y"
        { yyval = node_name_reference((yyloc), yyvsp[0]); }
#line 2095 "parser.tab.c"
    break;

  case 51:
#line 244 "src/parser.y"
        { yyval = node_expression_group((yyloc), yyvsp[-1]); }
#line 2101 "parser.tab.c"
    break;

  case 52:
#line 249 "src/parser.y"
        { yyval = NULL; }
#line 2107 "parser.tab.c"
    break;

  case 53:
#line 251 "src/parser.y"
        { yyval = yyvsp[-1]; }
#line 2113 "parser.tab.c"
    break;

  case 55:
#line 257 "src/parser.y"
        { yyval = node_call((yyloc), yyvsp[-1], yyvsp[0], false); }
#line 2119 "parser.tab.c"
    break;

  case 56:
#line 259 "src/parser.y"
        { yyval = node_call((yyloc), node_name_index((yyloc), yyvsp[-3], yyvsp[-1], true), yyvsp[0], true); }
#line 2125 "parser.tab.c"
    break;

  case 68:
#line 267 "src/parser.y"
    { yyval = yyvsp[0]; }
#line 2131 "parser.tab.c"
    break;

  case 69:
#line 272 "src/parser.y"
        { 
            // *root = node_function_body(@$, node_parameter_list(@$, NULL, node_vararg(@$)), node_type(@$, type_basic(TYPE_BASIC_ANY)), $1);
            //*root = $1;
            struct node *params = node_parameter_list((yyloc), NULL, node_vararg((yyloc)));
            struct node *type = node_type((yyloc), type_basic(TYPE_BASIC_ANY)); 
            *root = node_function_body((yyloc), params, type, yyvsp[0]);
        }
#line 2143 "parser.tab.c"
    break;

  case 70:
#line 283 "src/parser.y"
        { yyval = node_name_reference((yyloc), yyvsp[0]); }
#line 2149 "parser.tab.c"
    break;

  case 71:
#line 285 "src/parser.y"
        { yyval = node_variable_list((yyloc), yyvsp[0], yyvsp[-2]); }
#line 2155 "parser.tab.c"
    break;

  case 72:
#line 290 "src/parser.y"
        { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 2161 "parser.tab.c"
    break;

  case 73:
#line 292 "src/parser.y"
        { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], NULL); }
#line 2167 "parser.tab.c"
    break;

  case 74:
#line 294 "src/parser.y"
        { yyval = yyvsp[-1]; }
#line 2173 "parser.tab.c"
    break;

  case 75:
#line 309 "src/parser.y"
        { yyval = node_function_body((yyloc), yyvsp[-5], yyvsp[-2], yyvsp[-1]); }
#line 2179 "parser.tab.c"
    break;

  case 76:
#line 311 "src/parser.y"
        { yyval = node_function_body((yyloc), yyvsp[-3], NULL, yyvsp[-1]); }
#line 2185 "parser.tab.c"
    break;

  case 77:
#line 313 "src/parser.y"
        { yyval = node_function_body((yyloc), NULL, yyvsp[-2], yyvsp[-1]); }
#line 2191 "parser.tab.c"
    break;

  case 78:
#line 315 "src/parser.y"
        { yyval = node_function_body((yyloc), NULL, NULL, yyvsp[-1]); }
#line 2197 "parser.tab.c"
    break;

  case 79:
#line 323 "src/parser.y"
        { yyval = node_assignment((yyloc), node_name_reference((yyloc), yyvsp[-2]), ASSIGN, yyvsp[0]); }
#line 2203 "parser.tab.c"
    break;

  case 80:
#line 325 "src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN, yyvsp[0]); }
#line 2209 "parser.tab.c"
    break;

  case 81:
#line 330 "src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN, yyvsp[0]); }
#line 2215 "parser.tab.c"
    break;

  case 82:
#line 332 "src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_ADD, yyvsp[0]); }
#line 2221 "parser.tab.c"
    break;

  case 83:
#line 334 "src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_SUB, yyvsp[0]); }
#line 2227 "parser.tab.c"
    break;

  case 84:
#line 336 "src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_MUL, yyvsp[0]); }
#line 2233 "parser.tab.c"
    break;

  case 85:
#line 338 "src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_DIV, yyvsp[0]); }
#line 2239 "parser.tab.c"
    break;

  case 86:
#line 340 "src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_MOD, yyvsp[0]); }
#line 2245 "parser.tab.c"
    break;

  case 87:
#line 342 "src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_POW, yyvsp[0]); }
#line 2251 "parser.tab.c"
    break;

  case 88:
#line 344 "src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_CON, yyvsp[0]); }
#line 2257 "parser.tab.c"
    break;

  case 89:
#line 349 "src/parser.y"
        { yyval = yyvsp[0]; }
#line 2263 "parser.tab.c"
    break;

  case 90:
#line 351 "src/parser.y"
        { yyval = node_expression_statement((yyloc), yyvsp[0]); }
#line 2269 "parser.tab.c"
    break;

  case 91:
#line 353 "src/parser.y"
        { yyval = node_block((yyloc), yyvsp[-1], NULL); }
#line 2275 "parser.tab.c"
    break;

  case 92:
#line 355 "src/parser.y"
        { yyval = node_while_loop((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 2281 "parser.tab.c"
    break;

  case 93:
#line 357 "src/parser.y"
        { yyval = node_repeat_loop((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 2287 "parser.tab.c"
    break;

  case 94:
#line 359 "src/parser.y"
        { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], NULL); }
#line 2293 "parser.tab.c"
    break;

  case 95:
#line 361 "src/parser.y"
         { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 2299 "parser.tab.c"
    break;

  case 96:
#line 363 "src/parser.y"
        { yyval = node_numerical_for_loop((yyloc), yyvsp[-5], yyvsp[-3], node_number((yyloc), "1"), yyvsp[-1]); }
#line 2305 "parser.tab.c"
    break;

  case 97:
#line 365 "src/parser.y"
        { yyval = node_numerical_for_loop((yyloc), yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[-1]); }
#line 2311 "parser.tab.c"
    break;

  case 98:
#line 367 "src/parser.y"
        { yyval = node_generic_for_loop((yyloc), node_local((yyloc), yyvsp[-5], yyvsp[-3]), yyvsp[-1]); }
#line 2317 "parser.tab.c"
    break;

  case 99:
#line 369 "src/parser.y"
        { yyval = node_local((yyloc), yyvsp[0], NULL); }
#line 2323 "parser.tab.c"
    break;

  case 100:
#line 371 "src/parser.y"
        { yyval = node_local((yyloc), yyvsp[-2], yyvsp[0]); }
#line 2329 "parser.tab.c"
    break;

  case 101:
#line 373 "src/parser.y"
        { yyval = node_local((yyloc), node_type_annotation((yyloc), yyvsp[-1], node_type((yyloc), NULL)), yyvsp[0]); }
#line 2335 "parser.tab.c"
    break;

  case 102:
#line 375 "src/parser.y"
        { yyval = yyvsp[0]; }
#line 2341 "parser.tab.c"
    break;

  case 103:
#line 381 "src/parser.y"
        { yyval = NULL; }
#line 2347 "parser.tab.c"
    break;

  case 104:
#line 383 "src/parser.y"
        { yyval = node_block((yyloc), yyvsp[0], NULL); }
#line 2353 "parser.tab.c"
    break;

  case 105:
#line 385 "src/parser.y"
        { yyval = node_block((yyloc), yyvsp[-1], yyvsp[0]); }
#line 2359 "parser.tab.c"
    break;

  case 106:
#line 390 "src/parser.y"
        { yyval = node_return((yyloc), yyvsp[0]); }
#line 2365 "parser.tab.c"
    break;

  case 107:
#line 392 "src/parser.y"
        { yyval = node_return((yyloc), node_nil((yyloc))); }
#line 2371 "parser.tab.c"
    break;

  case 108:
#line 394 "src/parser.y"
        { yyval = node_break((yyloc)); }
#line 2377 "parser.tab.c"
    break;


#line 2381 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, root, error_count, lexer, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, root, error_count, lexer, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, root, error_count, lexer);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, root, error_count, lexer);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, root, error_count, lexer, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, root, error_count, lexer);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp, root, error_count, lexer);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 397 "src/parser.y"


static void yyerror(YYLTYPE *loc,
                    YYSTYPE *root __attribute__((unused)),
                    int *error_count,
                    yyscan_t scanner __attribute__((unused)),
                    char const *s)
{
  compiler_error(*loc, s);
  (*error_count)++;
}

/*  parser_parse - creates a tree of nodes
 *      args: pointer to error count, lexer instance
 *      rets: token name
 */
struct node *parser_parse(int *error_count, yyscan_t lexer)
{
    struct node *tree;

    int result = yyparse(&tree, error_count, lexer);

    /* Handle any errors that came up in the pass */
    if (result == 1 || *error_count > 0) 
        return NULL;
    else if (result == 2) {
        printf("Parser ran out of memory. Try restarting the compiler.\n");
        return NULL;
    }

    return tree;
}

/*  token_to_string - converts the given token to it's corresponding string name
 *      args: token
 *      rets: token name
 */
const char *token_to_string(int token) 
{
    return yytname[token - 255];
}
