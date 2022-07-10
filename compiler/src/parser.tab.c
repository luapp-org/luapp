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
#line 14 "parser.y"

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
    PLUS_T = 285,
    MINUS_T = 286,
    ASTERISK_T = 287,
    SLASH_T = 288,
    PERCENT_T = 289,
    EQUAL_T = 290,
    LEFT_PARAN_T = 291,
    RIGHT_PARAN_T = 292,
    RIGHT_SQUARE_T = 293,
    LEFT_SQUARE_T = 294,
    CARROT_T = 295,
    GREATER_THAN_T = 296,
    LESS_THAN_T = 297,
    SQUIGGLE_T = 298,
    COLON_T = 299,
    POUND_T = 300,
    DOT_T = 301,
    COMMA_T = 302,
    DOUBLE_EQUAL_T = 303,
    NOT_EQUAL_T = 304,
    GREATER_EQUAL_T = 305,
    LESS_EQUAL_T = 306,
    CONCAT_T = 307,
    VARARG_T = 308,
    PLUS_EQUAL_T = 309,
    MINUS_EQUAL_T = 310,
    ASTERISK_EQUAL_T = 311,
    SLASH_EQUAL_T = 312,
    MOD_EQUAL_T = 313,
    CARROT_EQUAL_T = 314,
    CONCAT_EQUAL_T = 315
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
#define YYFINAL  55
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   907

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  184

#define YYUNDEFTOK  2
#define YYMAXUTOK   315


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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   108,   108,   110,   112,   114,   116,   118,   120,   122,
     124,   126,   128,   130,   132,   134,   136,   141,   143,   145,
     150,   151,   156,   158,   160,   165,   166,   171,   172,   177,
     179,   181,   186,   188,   192,   193,   195,   200,   201,   202,
     207,   209,   211,   215,   217,   222,   222,   222,   222,   222,
     222,   223,   223,   223,   224,   229,   234,   235,   240,   242,
     244,   259,   261,   263,   265,   273,   278,   280,   282,   284,
     286,   288,   290,   292,   297,   299,   301,   303,   305,   307,
     309,   311,   313,   315,   317,   319,   325,   326,   328,   333,
     335,   337
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
  "TNUMBER_T", "TSTRING_T", "TBOOLEAN_T", "PLUS_T", "MINUS_T",
  "ASTERISK_T", "SLASH_T", "PERCENT_T", "EQUAL_T", "LEFT_PARAN_T",
  "RIGHT_PARAN_T", "RIGHT_SQUARE_T", "LEFT_SQUARE_T", "CARROT_T",
  "GREATER_THAN_T", "LESS_THAN_T", "SQUIGGLE_T", "COLON_T", "POUND_T",
  "DOT_T", "COMMA_T", "DOUBLE_EQUAL_T", "NOT_EQUAL_T", "GREATER_EQUAL_T",
  "LESS_EQUAL_T", "CONCAT_T", "VARARG_T", "PLUS_EQUAL_T", "MINUS_EQUAL_T",
  "ASTERISK_EQUAL_T", "SLASH_EQUAL_T", "MOD_EQUAL_T", "CARROT_EQUAL_T",
  "CONCAT_EQUAL_T", "$accept", "binary_operation", "unary_operation",
  "expression_list", "parameter_list", "name_list", "type_list", "type",
  "name_type", "variable", "prefix_expression", "arguments", "call",
  "expression", "program", "variable_list", "else_body", "function_body",
  "single_assignment", "assignment", "statement", "block",
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
     315
};
# endif

#define YYPACT_NINF (-110)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-39)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     871,  -110,  -110,   871,     3,    47,     5,   871,    47,    47,
      47,    29,   110,   187,    19,   234,  -110,  -110,   871,  -110,
     697,    69,    23,  -110,    -9,  -110,   -19,  -110,  -110,  -110,
    -110,    -5,  -110,    47,    47,    47,  -110,  -110,  -110,  -110,
     110,   357,   -12,   -23,   714,   -11,   551,   362,   395,  -110,
      99,    47,    32,    34,  -110,  -110,    47,    13,    47,    47,
      47,    47,    47,    47,    47,  -110,  -110,    70,    47,     5,
      47,    47,    10,  -110,   551,   551,   551,    47,    47,   871,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,   871,  -110,  -110,   -20,
     427,    17,  -110,   -11,    29,   -11,   -11,   -11,   -11,   -11,
     -11,   -11,  -110,  -110,  -110,  -110,     1,  -110,   551,   464,
     610,  -110,     9,    22,   551,   551,   659,   551,   551,   551,
     551,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     -11,   496,   551,   735,  -110,  -110,  -110,   871,   871,    70,
     752,   635,     8,   871,    47,  -110,  -110,  -110,  -110,   769,
     786,     7,  -110,  -110,    70,   803,  -110,   820,   519,  -110,
    -110,    70,   837,     7,  -110,  -110,   871,  -110,  -110,   854,
     680,  -110,  -110,  -110
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      86,    34,    91,    86,     0,     0,     0,    86,    90,     0,
       0,    56,     0,    75,     0,     0,    74,    87,    55,    85,
       0,    34,     0,    25,    37,    38,     0,    48,    49,    46,
      47,     0,    45,     0,     0,     0,    50,    51,    52,    37,
      53,     0,    33,    83,     0,    89,    20,     0,     0,    42,
       0,     0,     0,     0,    43,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,    76,     0,     0,     0,
       0,     0,     0,    54,    18,    17,    19,     0,     0,    86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    86,    39,    40,     0,
       0,     0,    36,    66,    57,    67,    68,    69,    70,    71,
      72,    73,    29,    30,    31,    32,     0,    26,    65,     0,
      86,    24,     0,    22,    15,    16,     0,     2,     3,     4,
       5,     7,     6,    10,     9,    14,    13,    11,    12,     8,
      84,     0,    21,     0,    41,    35,    44,    86,    86,     0,
       0,    86,     0,    86,     0,    79,    80,    78,    77,     0,
       0,    86,    27,    64,     0,     0,    23,     0,     0,    82,
      81,     0,     0,    86,    62,    60,    86,    28,    63,     0,
       0,    61,    59,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -110,  -110,  -110,   548,  -110,    -1,  -109,   -65,   -68,     0,
      38,   -37,    87,   270,  -110,  -110,  -108,  -110,  -110,  -110,
     157,   125,  -110
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    37,    38,    45,   122,    22,   161,   162,    23,    39,
      40,    54,    25,    46,    14,    15,   156,    73,    26,    16,
      17,    18,    19
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      11,   117,   115,    11,    24,    43,    21,    11,    42,   147,
       1,    42,    93,    42,     2,     3,     1,   144,    11,    55,
      11,     4,    49,     5,    69,     6,    70,    95,    71,     7,
       8,    72,    67,     9,   -37,   101,    95,   102,    12,    10,
      68,    12,    12,    10,    11,    12,   151,   120,    95,    10,
       1,    27,    28,    50,   171,   173,    12,   104,    12,    29,
      30,   166,    31,   121,   146,   -37,    32,    33,   -37,   152,
      69,   123,   183,   -37,     0,   -37,     0,     0,    34,    11,
       0,     0,    12,    10,   117,     0,   -33,    13,     0,     0,
      13,     0,    35,     0,    13,    12,    11,   112,   113,   114,
      36,     0,     1,    27,    28,    13,   177,    13,     0,     0,
       0,    29,    30,    67,    31,    49,   -33,    12,    32,    33,
      11,     0,     0,     0,     0,     0,    11,     0,    20,     0,
      34,    13,    44,     0,    12,    10,    98,     0,     0,     0,
       0,     0,     0,    11,    35,     0,    50,    11,    11,    51,
      11,    11,    36,    11,    52,     0,    53,     0,    12,    11,
      11,    11,     0,     0,    12,    11,    13,    11,     0,     0,
       0,     0,    11,    11,     0,    65,    11,    65,     0,    11,
      11,    12,     0,    13,     0,    12,    12,     0,    12,    12,
       0,    12,   -38,     0,     0,     0,     0,    12,    12,    12,
       0,    65,     0,    12,   126,    12,     0,    13,     0,     0,
      12,    12,     0,    13,    12,     0,     0,    12,    12,     0,
       0,   143,     0,   -38,     0,     0,   -38,     0,     0,     0,
      13,   -38,     0,   -38,    13,    13,     0,    13,    13,     0,
      13,     0,     0,     0,     0,   150,    13,    13,    13,     0,
       0,     0,    13,     0,    13,     0,     0,     0,     0,    13,
      13,     0,     0,    13,     0,     0,    13,    13,     0,    56,
       0,     0,   159,   160,     0,    41,   165,     0,   167,    47,
      48,    57,     0,    65,     0,     0,   172,     0,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,   179,     0,
      65,   180,     0,    74,    75,    76,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    65,     0,     0,
       0,   100,    65,     0,    65,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,    65,    65,     0,     0,
     118,   119,     0,     0,     0,     0,     0,   124,   125,     0,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,    77,   141,   142,     0,     0,    77,     0,
      96,     0,     0,     0,     0,     0,     0,     0,    78,     0,
       0,    79,     0,    78,     0,     0,     0,    80,    81,    82,
      83,    84,    80,    81,    82,    83,    84,    85,    86,    87,
       0,    77,    85,    86,    87,    88,    89,    90,    91,    92,
      88,    89,    90,    91,    92,     0,    78,     0,     0,     0,
       0,     0,     0,     0,   168,    80,    81,    82,    83,    84,
       0,     0,    97,    77,     0,    85,    86,    87,     0,     0,
       0,     0,     0,    88,    89,    90,    91,    92,    78,     0,
       0,     0,     0,     0,     0,     0,     0,    80,    81,    82,
      83,    84,     0,     0,     0,   145,     0,    85,    86,    87,
      77,     0,   148,     0,     0,    88,    89,    90,    91,    92,
       0,     0,     0,     0,     0,    78,     0,     0,     0,     0,
       0,     0,     0,     0,    80,    81,    82,    83,    84,     0,
       0,     0,    77,     0,    85,    86,    87,   157,     0,     0,
       0,     0,    88,    89,    90,    91,    92,    78,     0,     0,
       0,     0,     0,     0,     0,    77,    80,    81,    82,    83,
      84,     0,     0,     0,     0,     0,    85,    86,    87,     0,
      78,     0,     0,   176,    88,    89,    90,    91,    92,    80,
      81,    82,    83,    84,     0,     0,     0,    77,     0,    85,
      86,    87,     0,     0,     0,     0,     0,    88,    89,    90,
      91,    92,    78,     0,     0,     0,     0,     0,     0,     0,
       0,    80,    81,    82,    83,    84,     0,     0,     0,     0,
       0,    85,    86,    87,     0,     0,     0,     0,    99,    88,
      89,    90,    91,    92,   103,     0,   105,   106,   107,   108,
     109,   110,   111,     1,     0,     0,   116,     2,     3,     0,
       0,     0,     0,     0,     4,     0,     5,     0,     6,     0,
       0,     0,     7,     8,     0,     0,     9,     0,     1,     0,
       0,   140,     2,     3,     0,     0,    10,     0,     0,     4,
       0,     5,     0,     6,   149,     0,     0,     7,     8,     0,
       0,     9,     1,     0,     0,     0,     2,     3,   153,   154,
     155,    10,     0,     4,     0,     5,     0,     6,     0,   164,
       0,     7,     8,     1,     0,     9,     0,     2,     3,   153,
     154,   182,     0,     0,     4,    10,     5,     0,     6,     0,
       1,     0,     7,     8,     2,     3,     9,     0,    66,     0,
       0,     4,     0,     5,     0,     6,    10,     1,     0,     7,
       8,     2,     3,     9,     0,     0,     0,     0,     4,     0,
       5,     0,     6,    10,     0,     0,     7,     8,     1,    94,
       9,     0,     2,     3,     0,     0,   158,     0,     0,     4,
      10,     5,     0,     6,     0,     1,     0,     7,     8,     2,
       3,     9,     0,   163,     0,     0,     4,     0,     5,     0,
       6,    10,     1,     0,     7,     8,     2,     3,     9,     0,
     169,     0,     0,     4,     0,     5,     0,     6,    10,     1,
       0,     7,     8,     2,     3,     9,     0,   170,     0,     0,
       4,     0,     5,     0,     6,    10,     1,     0,     7,     8,
       2,     3,     9,     0,   174,     0,     0,     4,     0,     5,
       0,     6,    10,     1,     0,     7,     8,     2,     3,     9,
       0,   175,     0,     0,     4,     0,     5,     0,     6,    10,
       1,     0,     7,     8,     2,     3,     9,     0,   178,     0,
       0,     4,     0,     5,     0,     6,    10,     1,     0,     7,
       8,     2,     3,     9,     0,   181,     0,     0,     4,     0,
       5,     0,     6,    10,     1,     0,     7,     8,     2,     3,
       9,     0,     0,     0,     0,     4,     0,     5,     0,     6,
      10,     0,     0,     7,     8,     0,     0,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    10
};

static const yytype_int16 yycheck[] =
{
       0,    69,    67,     3,     4,     6,     3,     7,     3,     8,
       3,     3,    35,     3,     7,     8,     3,    37,    18,     0,
      20,    14,     5,    16,    47,    18,    35,    47,    47,    22,
      23,    36,    44,    26,     5,     3,    47,     3,     0,    36,
      17,     3,     4,    36,    44,     7,    37,    37,    47,    36,
       3,     4,     5,    36,    47,   164,    18,    57,    20,    12,
      13,    53,    15,    53,   101,    36,    19,    20,    39,    47,
      47,    72,   180,    44,    -1,    46,    -1,    -1,    31,    79,
      -1,    -1,    44,    36,   152,    -1,    17,     0,    -1,    -1,
       3,    -1,    45,    -1,     7,    57,    96,    27,    28,    29,
      53,    -1,     3,     4,     5,    18,   171,    20,    -1,    -1,
      -1,    12,    13,    44,    15,     5,    47,    79,    19,    20,
     120,    -1,    -1,    -1,    -1,    -1,   126,    -1,     3,    -1,
      31,    44,     7,    -1,    96,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,   143,    45,    -1,    36,   147,   148,    39,
     150,   151,    53,   153,    44,    -1,    46,    -1,   120,   159,
     160,   161,    -1,    -1,   126,   165,    79,   167,    -1,    -1,
      -1,    -1,   172,   173,    -1,    18,   176,    20,    -1,   179,
     180,   143,    -1,    96,    -1,   147,   148,    -1,   150,   151,
      -1,   153,     5,    -1,    -1,    -1,    -1,   159,   160,   161,
      -1,    44,    -1,   165,    79,   167,    -1,   120,    -1,    -1,
     172,   173,    -1,   126,   176,    -1,    -1,   179,   180,    -1,
      -1,    96,    -1,    36,    -1,    -1,    39,    -1,    -1,    -1,
     143,    44,    -1,    46,   147,   148,    -1,   150,   151,    -1,
     153,    -1,    -1,    -1,    -1,   120,   159,   160,   161,    -1,
      -1,    -1,   165,    -1,   167,    -1,    -1,    -1,    -1,   172,
     173,    -1,    -1,   176,    -1,    -1,   179,   180,    -1,    35,
      -1,    -1,   147,   148,    -1,     5,   151,    -1,   153,     9,
      10,    47,    -1,   126,    -1,    -1,   161,    -1,    54,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,   173,    -1,
     143,   176,    -1,    33,    34,    35,    -1,   150,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   159,   160,    -1,    -1,
      -1,    51,   165,    -1,   167,    -1,    -1,    -1,    -1,   172,
      -1,    -1,    -1,    -1,    -1,    -1,   179,   180,    -1,    -1,
      70,    71,    -1,    -1,    -1,    -1,    -1,    77,    78,    -1,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,     6,    94,    95,    -1,    -1,     6,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      -1,    24,    -1,    21,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    30,    31,    32,    33,    34,    40,    41,    42,
      -1,     6,    40,    41,    42,    48,    49,    50,    51,    52,
      48,    49,    50,    51,    52,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   154,    30,    31,    32,    33,    34,
      -1,    -1,    37,     6,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    38,    -1,    40,    41,    42,
       6,    -1,     8,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    -1,     6,    -1,    40,    41,    42,    11,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,
      21,    -1,    -1,    24,    48,    49,    50,    51,    52,    30,
      31,    32,    33,    34,    -1,    -1,    -1,     6,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    50,    48,
      49,    50,    51,    52,    56,    -1,    58,    59,    60,    61,
      62,    63,    64,     3,    -1,    -1,    68,     7,     8,    -1,
      -1,    -1,    -1,    -1,    14,    -1,    16,    -1,    18,    -1,
      -1,    -1,    22,    23,    -1,    -1,    26,    -1,     3,    -1,
      -1,    93,     7,     8,    -1,    -1,    36,    -1,    -1,    14,
      -1,    16,    -1,    18,    44,    -1,    -1,    22,    23,    -1,
      -1,    26,     3,    -1,    -1,    -1,     7,     8,     9,    10,
      11,    36,    -1,    14,    -1,    16,    -1,    18,    -1,    44,
      -1,    22,    23,     3,    -1,    26,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    14,    36,    16,    -1,    18,    -1,
       3,    -1,    22,    23,     7,     8,    26,    -1,    11,    -1,
      -1,    14,    -1,    16,    -1,    18,    36,     3,    -1,    22,
      23,     7,     8,    26,    -1,    -1,    -1,    -1,    14,    -1,
      16,    -1,    18,    36,    -1,    -1,    22,    23,     3,    25,
      26,    -1,     7,     8,    -1,    -1,    11,    -1,    -1,    14,
      36,    16,    -1,    18,    -1,     3,    -1,    22,    23,     7,
       8,    26,    -1,    11,    -1,    -1,    14,    -1,    16,    -1,
      18,    36,     3,    -1,    22,    23,     7,     8,    26,    -1,
      11,    -1,    -1,    14,    -1,    16,    -1,    18,    36,     3,
      -1,    22,    23,     7,     8,    26,    -1,    11,    -1,    -1,
      14,    -1,    16,    -1,    18,    36,     3,    -1,    22,    23,
       7,     8,    26,    -1,    11,    -1,    -1,    14,    -1,    16,
      -1,    18,    36,     3,    -1,    22,    23,     7,     8,    26,
      -1,    11,    -1,    -1,    14,    -1,    16,    -1,    18,    36,
       3,    -1,    22,    23,     7,     8,    26,    -1,    11,    -1,
      -1,    14,    -1,    16,    -1,    18,    36,     3,    -1,    22,
      23,     7,     8,    26,    -1,    11,    -1,    -1,    14,    -1,
      16,    -1,    18,    36,     3,    -1,    22,    23,     7,     8,
      26,    -1,    -1,    -1,    -1,    14,    -1,    16,    -1,    18,
      36,    -1,    -1,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,     8,    14,    16,    18,    22,    23,    26,
      36,    70,    71,    73,    75,    76,    80,    81,    82,    83,
      82,     3,    66,    69,    70,    73,    79,     4,     5,    12,
      13,    15,    19,    20,    31,    45,    53,    62,    63,    70,
      71,    74,     3,    66,    82,    64,    74,    74,    74,     5,
      36,    39,    44,    46,    72,     0,    35,    47,    54,    55,
      56,    57,    58,    59,    60,    81,    11,    44,    17,    47,
      35,    47,    36,    78,    74,    74,    74,     6,    21,    24,
      30,    31,    32,    33,    34,    40,    41,    42,    48,    49,
      50,    51,    52,    35,    25,    47,     8,    37,    37,    64,
      74,     3,     3,    64,    70,    64,    64,    64,    64,    64,
      64,    64,    27,    28,    29,    68,    64,    69,    74,    74,
      37,    53,    65,    66,    74,    74,    82,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      64,    74,    74,    82,    37,    38,    72,     8,     8,    44,
      82,    37,    47,     9,    10,    11,    77,    11,    11,    82,
      82,    67,    68,    11,    44,    82,    53,    82,    74,    11,
      11,    47,    82,    67,    11,    11,    24,    68,    11,    82,
      82,    11,    11,    77
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    63,    63,    63,
      64,    64,    65,    65,    65,    66,    66,    67,    67,    68,
      68,    68,    69,    69,    70,    70,    70,    71,    71,    71,
      72,    72,    72,    73,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    75,    76,    76,    77,    77,
      77,    78,    78,    78,    78,    79,    80,    80,    80,    80,
      80,    80,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    82,    82,    82,    83,
      83,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       1,     3,     1,     3,     1,     1,     3,     1,     3,     1,
       1,     1,     3,     1,     1,     4,     3,     1,     1,     3,
       2,     3,     1,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     3,     5,     5,
       3,     7,     5,     6,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     3,     5,     5,     5,
       5,     7,     7,     2,     4,     1,     0,     1,     2,     2,
       1,     1
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
#line 109 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_ADD, yyvsp[-2], yyvsp[0]); }
#line 1776 "parser.tab.c"
    break;

  case 3:
#line 111 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_SUB, yyvsp[-2], yyvsp[0]); }
#line 1782 "parser.tab.c"
    break;

  case 4:
#line 113 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_MUL, yyvsp[-2], yyvsp[0]); }
#line 1788 "parser.tab.c"
    break;

  case 5:
#line 115 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_DIV, yyvsp[-2], yyvsp[0]); }
#line 1794 "parser.tab.c"
    break;

  case 6:
#line 117 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_POW, yyvsp[-2], yyvsp[0]); }
#line 1800 "parser.tab.c"
    break;

  case 7:
#line 119 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_MOD, yyvsp[-2], yyvsp[0]); }
#line 1806 "parser.tab.c"
    break;

  case 8:
#line 121 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_CONCAT, yyvsp[-2], yyvsp[0]); }
#line 1812 "parser.tab.c"
    break;

  case 9:
#line 123 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_LT, yyvsp[-2], yyvsp[0]); }
#line 1818 "parser.tab.c"
    break;

  case 10:
#line 125 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_GT, yyvsp[-2], yyvsp[0]); }
#line 1824 "parser.tab.c"
    break;

  case 11:
#line 127 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_GE, yyvsp[-2], yyvsp[0]); }
#line 1830 "parser.tab.c"
    break;

  case 12:
#line 129 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_LE, yyvsp[-2], yyvsp[0]); }
#line 1836 "parser.tab.c"
    break;

  case 13:
#line 131 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_NE, yyvsp[-2], yyvsp[0]); }
#line 1842 "parser.tab.c"
    break;

  case 14:
#line 133 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_EQ, yyvsp[-2], yyvsp[0]); }
#line 1848 "parser.tab.c"
    break;

  case 15:
#line 135 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_AND, yyvsp[-2], yyvsp[0]); }
#line 1854 "parser.tab.c"
    break;

  case 16:
#line 137 "parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_OR, yyvsp[-2], yyvsp[0]); }
#line 1860 "parser.tab.c"
    break;

  case 17:
#line 142 "parser.y"
      { yyval = node_unary_operation((yyloc), UNOP_NEG, yyvsp[0]); }
#line 1866 "parser.tab.c"
    break;

  case 18:
#line 144 "parser.y"
      { yyval = node_unary_operation((yyloc), UNOP_NOT, yyvsp[0]); }
#line 1872 "parser.tab.c"
    break;

  case 19:
#line 146 "parser.y"
      { yyval = node_unary_operation((yyloc), UNOP_LEN, yyvsp[0]); }
#line 1878 "parser.tab.c"
    break;

  case 21:
#line 152 "parser.y"
        { yyval = node_expression_list((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1884 "parser.tab.c"
    break;

  case 22:
#line 157 "parser.y"
        { yyval = node_parameter_list((yyloc), yyvsp[0], NULL); }
#line 1890 "parser.tab.c"
    break;

  case 23:
#line 159 "parser.y"
        { yyval = node_parameter_list((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1896 "parser.tab.c"
    break;

  case 24:
#line 161 "parser.y"
        { yyval = node_parameter_list((yyloc), NULL, yyvsp[0]); }
#line 1902 "parser.tab.c"
    break;

  case 26:
#line 167 "parser.y"
        { yyval = node_name_list((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1908 "parser.tab.c"
    break;

  case 28:
#line 173 "parser.y"
        { yyval = node_type_list((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1914 "parser.tab.c"
    break;

  case 29:
#line 178 "parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_NUMBER)); }
#line 1920 "parser.tab.c"
    break;

  case 30:
#line 180 "parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_STRING)); }
#line 1926 "parser.tab.c"
    break;

  case 31:
#line 182 "parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_BOOLEAN)); }
#line 1932 "parser.tab.c"
    break;

  case 32:
#line 187 "parser.y"
        { yyval = node_type_annotation((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1938 "parser.tab.c"
    break;

  case 35:
#line 194 "parser.y"
        { yyval = node_expression_index((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 1944 "parser.tab.c"
    break;

  case 36:
#line 196 "parser.y"
        { yyval = node_name_index((yyloc), yyvsp[-2], yyvsp[0], false); }
#line 1950 "parser.tab.c"
    break;

  case 39:
#line 203 "parser.y"
        { yyval = node_expression_group((yyloc), yyvsp[-1]); }
#line 1956 "parser.tab.c"
    break;

  case 40:
#line 208 "parser.y"
        { yyval = NULL; }
#line 1962 "parser.tab.c"
    break;

  case 41:
#line 210 "parser.y"
        { yyval = yyvsp[-1]; }
#line 1968 "parser.tab.c"
    break;

  case 43:
#line 216 "parser.y"
        { yyval = node_call((yyloc), yyvsp[-1], yyvsp[0], false); }
#line 1974 "parser.tab.c"
    break;

  case 44:
#line 218 "parser.y"
        { yyval = node_call((yyloc), node_name_index((yyloc), yyvsp[-3], yyvsp[-1], true), yyvsp[0], true); }
#line 1980 "parser.tab.c"
    break;

  case 54:
#line 225 "parser.y"
    { yyval = yyvsp[0]; }
#line 1986 "parser.tab.c"
    break;

  case 55:
#line 230 "parser.y"
        { *root = yyvsp[0]; }
#line 1992 "parser.tab.c"
    break;

  case 57:
#line 236 "parser.y"
        { yyval = node_variable_list((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1998 "parser.tab.c"
    break;

  case 58:
#line 241 "parser.y"
        { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 2004 "parser.tab.c"
    break;

  case 59:
#line 243 "parser.y"
        { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], NULL); }
#line 2010 "parser.tab.c"
    break;

  case 60:
#line 245 "parser.y"
        { yyval = yyvsp[-1]; }
#line 2016 "parser.tab.c"
    break;

  case 61:
#line 260 "parser.y"
        { yyval = node_function_body((yyloc), yyvsp[-5], yyvsp[-2], yyvsp[-1]); }
#line 2022 "parser.tab.c"
    break;

  case 62:
#line 262 "parser.y"
        { yyval = node_function_body((yyloc), yyvsp[-3], NULL, yyvsp[-1]); }
#line 2028 "parser.tab.c"
    break;

  case 63:
#line 264 "parser.y"
        { yyval = node_function_body((yyloc), NULL, yyvsp[-2], yyvsp[-1]); }
#line 2034 "parser.tab.c"
    break;

  case 64:
#line 266 "parser.y"
        { yyval = node_function_body((yyloc), NULL, NULL, yyvsp[-1]); }
#line 2040 "parser.tab.c"
    break;

  case 65:
#line 274 "parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN, yyvsp[0]); }
#line 2046 "parser.tab.c"
    break;

  case 66:
#line 279 "parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN, yyvsp[0]); }
#line 2052 "parser.tab.c"
    break;

  case 67:
#line 281 "parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_ADD, yyvsp[0]); }
#line 2058 "parser.tab.c"
    break;

  case 68:
#line 283 "parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_SUB, yyvsp[0]); }
#line 2064 "parser.tab.c"
    break;

  case 69:
#line 285 "parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_MUL, yyvsp[0]); }
#line 2070 "parser.tab.c"
    break;

  case 70:
#line 287 "parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_DIV, yyvsp[0]); }
#line 2076 "parser.tab.c"
    break;

  case 71:
#line 289 "parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_MOD, yyvsp[0]); }
#line 2082 "parser.tab.c"
    break;

  case 72:
#line 291 "parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_POW, yyvsp[0]); }
#line 2088 "parser.tab.c"
    break;

  case 73:
#line 293 "parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_CON, yyvsp[0]); }
#line 2094 "parser.tab.c"
    break;

  case 74:
#line 298 "parser.y"
        { yyval = yyvsp[0]; }
#line 2100 "parser.tab.c"
    break;

  case 75:
#line 300 "parser.y"
        { yyval = node_expression_statement((yyloc), yyvsp[0]); }
#line 2106 "parser.tab.c"
    break;

  case 76:
#line 302 "parser.y"
        { yyval = node_block((yyloc), yyvsp[-1], NULL); }
#line 2112 "parser.tab.c"
    break;

  case 77:
#line 304 "parser.y"
        { yyval = node_while_loop((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 2118 "parser.tab.c"
    break;

  case 78:
#line 306 "parser.y"
        { yyval = node_repeat_loop((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 2124 "parser.tab.c"
    break;

  case 79:
#line 308 "parser.y"
        { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], NULL); }
#line 2130 "parser.tab.c"
    break;

  case 80:
#line 310 "parser.y"
         { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 2136 "parser.tab.c"
    break;

  case 81:
#line 312 "parser.y"
        { yyval = node_numerical_for_loop((yyloc), yyvsp[-5], yyvsp[-3], node_number((yyloc), "1"), yyvsp[-1]); }
#line 2142 "parser.tab.c"
    break;

  case 82:
#line 314 "parser.y"
        { yyval = node_generic_for_loop((yyloc), yyvsp[-5], yyvsp[-3], yyvsp[-1]); }
#line 2148 "parser.tab.c"
    break;

  case 83:
#line 316 "parser.y"
        { yyval = node_local((yyloc), yyvsp[0], node_nil((yyloc))); }
#line 2154 "parser.tab.c"
    break;

  case 84:
#line 318 "parser.y"
        { yyval = node_local((yyloc), yyvsp[-2], yyvsp[0]); }
#line 2160 "parser.tab.c"
    break;

  case 85:
#line 320 "parser.y"
        { yyval = yyvsp[0]; }
#line 2166 "parser.tab.c"
    break;

  case 87:
#line 327 "parser.y"
        { yyval = node_block((yyloc), yyvsp[0], NULL); }
#line 2172 "parser.tab.c"
    break;

  case 88:
#line 329 "parser.y"
        { yyval = node_block((yyloc), yyvsp[-1], yyvsp[0]); }
#line 2178 "parser.tab.c"
    break;

  case 89:
#line 334 "parser.y"
        { yyval = node_return((yyloc), yyvsp[0]); }
#line 2184 "parser.tab.c"
    break;

  case 90:
#line 336 "parser.y"
        { yyval = node_return((yyloc), node_nil((yyloc))); }
#line 2190 "parser.tab.c"
    break;

  case 91:
#line 338 "parser.y"
        { yyval = node_break((yyloc)); }
#line 2196 "parser.tab.c"
    break;


#line 2200 "parser.tab.c"

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
#line 341 "parser.y"


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
