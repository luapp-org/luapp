/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 14 "compiler/src/parser.y"

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

#line 92 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER_T = 3,               /* IDENTIFIER_T  */
  YYSYMBOL_NUMBER_T = 4,                   /* NUMBER_T  */
  YYSYMBOL_STRING_T = 5,                   /* STRING_T  */
  YYSYMBOL_AND_T = 6,                      /* AND_T  */
  YYSYMBOL_BREAK_T = 7,                    /* BREAK_T  */
  YYSYMBOL_DO_T = 8,                       /* DO_T  */
  YYSYMBOL_ELSE_T = 9,                     /* ELSE_T  */
  YYSYMBOL_ELSEIF_T = 10,                  /* ELSEIF_T  */
  YYSYMBOL_END_T = 11,                     /* END_T  */
  YYSYMBOL_FALSE_T = 12,                   /* FALSE_T  */
  YYSYMBOL_TRUE_T = 13,                    /* TRUE_T  */
  YYSYMBOL_FOR_T = 14,                     /* FOR_T  */
  YYSYMBOL_FUNCTION_T = 15,                /* FUNCTION_T  */
  YYSYMBOL_IF_T = 16,                      /* IF_T  */
  YYSYMBOL_IN_T = 17,                      /* IN_T  */
  YYSYMBOL_LOCAL_T = 18,                   /* LOCAL_T  */
  YYSYMBOL_NIL_T = 19,                     /* NIL_T  */
  YYSYMBOL_NOT_T = 20,                     /* NOT_T  */
  YYSYMBOL_OR_T = 21,                      /* OR_T  */
  YYSYMBOL_REPEAT_T = 22,                  /* REPEAT_T  */
  YYSYMBOL_RETURN_T = 23,                  /* RETURN_T  */
  YYSYMBOL_THEN_T = 24,                    /* THEN_T  */
  YYSYMBOL_UNTIL_T = 25,                   /* UNTIL_T  */
  YYSYMBOL_WHILE_T = 26,                   /* WHILE_T  */
  YYSYMBOL_TNUMBER_T = 27,                 /* TNUMBER_T  */
  YYSYMBOL_TSTRING_T = 28,                 /* TSTRING_T  */
  YYSYMBOL_TBOOLEAN_T = 29,                /* TBOOLEAN_T  */
  YYSYMBOL_TANY_T = 30,                    /* TANY_T  */
  YYSYMBOL_TARRAY_T = 31,                  /* TARRAY_T  */
  YYSYMBOL_TTABLE_T = 32,                  /* TTABLE_T  */
  YYSYMBOL_PLUS_T = 33,                    /* PLUS_T  */
  YYSYMBOL_MINUS_T = 34,                   /* MINUS_T  */
  YYSYMBOL_ASTERISK_T = 35,                /* ASTERISK_T  */
  YYSYMBOL_SLASH_T = 36,                   /* SLASH_T  */
  YYSYMBOL_PERCENT_T = 37,                 /* PERCENT_T  */
  YYSYMBOL_EQUAL_T = 38,                   /* EQUAL_T  */
  YYSYMBOL_LEFT_PARAN_T = 39,              /* LEFT_PARAN_T  */
  YYSYMBOL_RIGHT_PARAN_T = 40,             /* RIGHT_PARAN_T  */
  YYSYMBOL_RIGHT_SQUARE_T = 41,            /* RIGHT_SQUARE_T  */
  YYSYMBOL_LEFT_SQUARE_T = 42,             /* LEFT_SQUARE_T  */
  YYSYMBOL_CARROT_T = 43,                  /* CARROT_T  */
  YYSYMBOL_GREATER_THAN_T = 44,            /* GREATER_THAN_T  */
  YYSYMBOL_LESS_THAN_T = 45,               /* LESS_THAN_T  */
  YYSYMBOL_SQUIGGLE_T = 46,                /* SQUIGGLE_T  */
  YYSYMBOL_COLON_T = 47,                   /* COLON_T  */
  YYSYMBOL_POUND_T = 48,                   /* POUND_T  */
  YYSYMBOL_DOT_T = 49,                     /* DOT_T  */
  YYSYMBOL_COMMA_T = 50,                   /* COMMA_T  */
  YYSYMBOL_LEFT_BRACKET_T = 51,            /* LEFT_BRACKET_T  */
  YYSYMBOL_RIGHT_BRACKET_T = 52,           /* RIGHT_BRACKET_T  */
  YYSYMBOL_DOUBLE_EQUAL_T = 53,            /* DOUBLE_EQUAL_T  */
  YYSYMBOL_NOT_EQUAL_T = 54,               /* NOT_EQUAL_T  */
  YYSYMBOL_GREATER_EQUAL_T = 55,           /* GREATER_EQUAL_T  */
  YYSYMBOL_LESS_EQUAL_T = 56,              /* LESS_EQUAL_T  */
  YYSYMBOL_CONCAT_T = 57,                  /* CONCAT_T  */
  YYSYMBOL_VARARG_T = 58,                  /* VARARG_T  */
  YYSYMBOL_PLUS_EQUAL_T = 59,              /* PLUS_EQUAL_T  */
  YYSYMBOL_MINUS_EQUAL_T = 60,             /* MINUS_EQUAL_T  */
  YYSYMBOL_ASTERISK_EQUAL_T = 61,          /* ASTERISK_EQUAL_T  */
  YYSYMBOL_SLASH_EQUAL_T = 62,             /* SLASH_EQUAL_T  */
  YYSYMBOL_MOD_EQUAL_T = 63,               /* MOD_EQUAL_T  */
  YYSYMBOL_CARROT_EQUAL_T = 64,            /* CARROT_EQUAL_T  */
  YYSYMBOL_CONCAT_EQUAL_T = 65,            /* CONCAT_EQUAL_T  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_binary_operation = 67,          /* binary_operation  */
  YYSYMBOL_unary_operation = 68,           /* unary_operation  */
  YYSYMBOL_expression_list = 69,           /* expression_list  */
  YYSYMBOL_parameter_list = 70,            /* parameter_list  */
  YYSYMBOL_name_list = 71,                 /* name_list  */
  YYSYMBOL_type_list = 72,                 /* type_list  */
  YYSYMBOL_type = 73,                      /* type  */
  YYSYMBOL_name_type = 74,                 /* name_type  */
  YYSYMBOL_array_constructor = 75,         /* array_constructor  */
  YYSYMBOL_pair = 76,                      /* pair  */
  YYSYMBOL_pair_list = 77,                 /* pair_list  */
  YYSYMBOL_table_constructor = 78,         /* table_constructor  */
  YYSYMBOL_variable = 79,                  /* variable  */
  YYSYMBOL_prefix_expression = 80,         /* prefix_expression  */
  YYSYMBOL_arguments = 81,                 /* arguments  */
  YYSYMBOL_call = 82,                      /* call  */
  YYSYMBOL_expression = 83,                /* expression  */
  YYSYMBOL_program = 84,                   /* program  */
  YYSYMBOL_variable_list = 85,             /* variable_list  */
  YYSYMBOL_else_body = 86,                 /* else_body  */
  YYSYMBOL_function_body = 87,             /* function_body  */
  YYSYMBOL_single_assignment = 88,         /* single_assignment  */
  YYSYMBOL_assignment = 89,                /* assignment  */
  YYSYMBOL_statement = 90,                 /* statement  */
  YYSYMBOL_block = 91,                     /* block  */
  YYSYMBOL_last_statement = 92             /* last_statement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER_T",
  "NUMBER_T", "STRING_T", "AND_T", "BREAK_T", "DO_T", "ELSE_T", "ELSEIF_T",
  "END_T", "FALSE_T", "TRUE_T", "FOR_T", "FUNCTION_T", "IF_T", "IN_T",
  "LOCAL_T", "NIL_T", "NOT_T", "OR_T", "REPEAT_T", "RETURN_T", "THEN_T",
  "UNTIL_T", "WHILE_T", "TNUMBER_T", "TSTRING_T", "TBOOLEAN_T", "TANY_T",
  "TARRAY_T", "TTABLE_T", "PLUS_T", "MINUS_T", "ASTERISK_T", "SLASH_T",
  "PERCENT_T", "EQUAL_T", "LEFT_PARAN_T", "RIGHT_PARAN_T",
  "RIGHT_SQUARE_T", "LEFT_SQUARE_T", "CARROT_T", "GREATER_THAN_T",
  "LESS_THAN_T", "SQUIGGLE_T", "COLON_T", "POUND_T", "DOT_T", "COMMA_T",
  "LEFT_BRACKET_T", "RIGHT_BRACKET_T", "DOUBLE_EQUAL_T", "NOT_EQUAL_T",
  "GREATER_EQUAL_T", "LESS_EQUAL_T", "CONCAT_T", "VARARG_T",
  "PLUS_EQUAL_T", "MINUS_EQUAL_T", "ASTERISK_EQUAL_T", "SLASH_EQUAL_T",
  "MOD_EQUAL_T", "CARROT_EQUAL_T", "CONCAT_EQUAL_T", "$accept",
  "binary_operation", "unary_operation", "expression_list",
  "parameter_list", "name_list", "type_list", "type", "name_type",
  "array_constructor", "pair", "pair_list", "table_constructor",
  "variable", "prefix_expression", "arguments", "call", "expression",
  "program", "variable_list", "else_body", "function_body",
  "single_assignment", "assignment", "statement", "block",
  "last_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

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
static const yytype_uint8 yydefgoto[] =
{
       0,    38,    39,    50,   140,    22,   172,   173,    48,    40,
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, root, error_count, lexer); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, YYSTYPE *root, int *error_count, yyscan_t lexer)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (root);
  YY_USE (error_count);
  YY_USE (lexer);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, YYSTYPE *root, int *error_count, yyscan_t lexer)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, root, error_count, lexer);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, YYSTYPE *root, int *error_count, yyscan_t lexer)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), root, error_count, lexer);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, YYSTYPE *root, int *error_count, yyscan_t lexer)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (root);
  YY_USE (error_count);
  YY_USE (lexer);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (YYSTYPE *root, int *error_count, yyscan_t lexer)
{
/* Lookahead token kind.  */
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
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, lexer);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  case 2: /* binary_operation: expression PLUS_T expression  */
#line 114 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_ADD, yyvsp[-2], yyvsp[0]); }
#line 1642 "parser.tab.c"
    break;

  case 3: /* binary_operation: expression MINUS_T expression  */
#line 116 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_SUB, yyvsp[-2], yyvsp[0]); }
#line 1648 "parser.tab.c"
    break;

  case 4: /* binary_operation: expression ASTERISK_T expression  */
#line 118 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_MUL, yyvsp[-2], yyvsp[0]); }
#line 1654 "parser.tab.c"
    break;

  case 5: /* binary_operation: expression SLASH_T expression  */
#line 120 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_DIV, yyvsp[-2], yyvsp[0]); }
#line 1660 "parser.tab.c"
    break;

  case 6: /* binary_operation: expression CARROT_T expression  */
#line 122 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_POW, yyvsp[-2], yyvsp[0]); }
#line 1666 "parser.tab.c"
    break;

  case 7: /* binary_operation: expression PERCENT_T expression  */
#line 124 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_MOD, yyvsp[-2], yyvsp[0]); }
#line 1672 "parser.tab.c"
    break;

  case 8: /* binary_operation: expression CONCAT_T expression  */
#line 126 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_CONCAT, yyvsp[-2], yyvsp[0]); }
#line 1678 "parser.tab.c"
    break;

  case 9: /* binary_operation: expression LESS_THAN_T expression  */
#line 128 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_LT, yyvsp[-2], yyvsp[0]); }
#line 1684 "parser.tab.c"
    break;

  case 10: /* binary_operation: expression GREATER_THAN_T expression  */
#line 130 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_GT, yyvsp[-2], yyvsp[0]); }
#line 1690 "parser.tab.c"
    break;

  case 11: /* binary_operation: expression GREATER_EQUAL_T expression  */
#line 132 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_GE, yyvsp[-2], yyvsp[0]); }
#line 1696 "parser.tab.c"
    break;

  case 12: /* binary_operation: expression LESS_EQUAL_T expression  */
#line 134 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_LE, yyvsp[-2], yyvsp[0]); }
#line 1702 "parser.tab.c"
    break;

  case 13: /* binary_operation: expression NOT_EQUAL_T expression  */
#line 136 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_NE, yyvsp[-2], yyvsp[0]); }
#line 1708 "parser.tab.c"
    break;

  case 14: /* binary_operation: expression DOUBLE_EQUAL_T expression  */
#line 138 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_EQ, yyvsp[-2], yyvsp[0]); }
#line 1714 "parser.tab.c"
    break;

  case 15: /* binary_operation: expression AND_T expression  */
#line 140 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_AND, yyvsp[-2], yyvsp[0]); }
#line 1720 "parser.tab.c"
    break;

  case 16: /* binary_operation: expression OR_T expression  */
#line 142 "compiler/src/parser.y"
      { yyval = node_binary_operation((yylsp[-1]), BINOP_OR, yyvsp[-2], yyvsp[0]); }
#line 1726 "parser.tab.c"
    break;

  case 17: /* unary_operation: MINUS_T expression  */
#line 147 "compiler/src/parser.y"
      { yyval = node_unary_operation((yyloc), UNOP_NEG, yyvsp[0]); }
#line 1732 "parser.tab.c"
    break;

  case 18: /* unary_operation: NOT_T expression  */
#line 149 "compiler/src/parser.y"
      { yyval = node_unary_operation((yyloc), UNOP_NOT, yyvsp[0]); }
#line 1738 "parser.tab.c"
    break;

  case 19: /* unary_operation: POUND_T expression  */
#line 151 "compiler/src/parser.y"
      { yyval = node_unary_operation((yyloc), UNOP_LEN, yyvsp[0]); }
#line 1744 "parser.tab.c"
    break;

  case 21: /* expression_list: expression COMMA_T expression_list  */
#line 157 "compiler/src/parser.y"
        { yyval = node_expression_list((yyloc), yyvsp[0], yyvsp[-2]); }
#line 1750 "parser.tab.c"
    break;

  case 22: /* parameter_list: name_list  */
#line 162 "compiler/src/parser.y"
        { yyval = node_parameter_list((yyloc), yyvsp[0], NULL); }
#line 1756 "parser.tab.c"
    break;

  case 23: /* parameter_list: name_list COMMA_T VARARG_T  */
#line 164 "compiler/src/parser.y"
        { yyval = node_parameter_list((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1762 "parser.tab.c"
    break;

  case 24: /* parameter_list: VARARG_T  */
#line 166 "compiler/src/parser.y"
        { yyval = node_parameter_list((yyloc), NULL, yyvsp[0]); }
#line 1768 "parser.tab.c"
    break;

  case 26: /* name_list: name_type COMMA_T name_list  */
#line 172 "compiler/src/parser.y"
        { yyval = node_name_list((yyloc), yyvsp[0], yyvsp[-2]); }
#line 1774 "parser.tab.c"
    break;

  case 28: /* type_list: type COMMA_T type_list  */
#line 178 "compiler/src/parser.y"
        { yyval = node_type_list((yyloc), yyvsp[0], yyvsp[-2]); }
#line 1780 "parser.tab.c"
    break;

  case 29: /* type: TNUMBER_T  */
#line 183 "compiler/src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_NUMBER)); }
#line 1786 "parser.tab.c"
    break;

  case 30: /* type: TSTRING_T  */
#line 185 "compiler/src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_STRING)); }
#line 1792 "parser.tab.c"
    break;

  case 31: /* type: TBOOLEAN_T  */
#line 187 "compiler/src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_BOOLEAN)); }
#line 1798 "parser.tab.c"
    break;

  case 32: /* type: TANY_T  */
#line 189 "compiler/src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_ANY)); }
#line 1804 "parser.tab.c"
    break;

  case 33: /* type: VARARG_T  */
#line 191 "compiler/src/parser.y"
        { yyval = node_type((yyloc), type_basic(TYPE_BASIC_VARARG)); }
#line 1810 "parser.tab.c"
    break;

  case 34: /* type: TARRAY_T LESS_THAN_T type GREATER_THAN_T  */
#line 193 "compiler/src/parser.y"
        { yyval = node_type_array((yyloc), yyvsp[-1]); }
#line 1816 "parser.tab.c"
    break;

  case 35: /* type: TTABLE_T LESS_THAN_T type COMMA_T type GREATER_THAN_T  */
#line 195 "compiler/src/parser.y"
        { yyval = node_type_table((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 1822 "parser.tab.c"
    break;

  case 36: /* type: LEFT_PARAN_T type_list RIGHT_PARAN_T COLON_T type_list  */
#line 197 "compiler/src/parser.y"
        { yyval = node_type_function((yyloc), yyvsp[-3], yyvsp[0]); }
#line 1828 "parser.tab.c"
    break;

  case 37: /* name_type: IDENTIFIER_T COLON_T type  */
#line 202 "compiler/src/parser.y"
        { yyval = node_type_annotation((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1834 "parser.tab.c"
    break;

  case 39: /* array_constructor: LEFT_BRACKET_T expression_list RIGHT_BRACKET_T  */
#line 208 "compiler/src/parser.y"
        { yyval = node_array_constructor((yyloc), yyvsp[-1]); }
#line 1840 "parser.tab.c"
    break;

  case 40: /* array_constructor: LEFT_BRACKET_T RIGHT_BRACKET_T  */
#line 210 "compiler/src/parser.y"
        { yyval = node_array_constructor((yyloc), NULL); }
#line 1846 "parser.tab.c"
    break;

  case 41: /* pair: LEFT_SQUARE_T expression RIGHT_SQUARE_T EQUAL_T expression  */
#line 215 "compiler/src/parser.y"
        { yyval = node_key_value_pair((yyloc), yyvsp[-3], yyvsp[0]); }
#line 1852 "parser.tab.c"
    break;

  case 42: /* pair_list: %empty  */
#line 220 "compiler/src/parser.y"
        { yyval = NULL; }
#line 1858 "parser.tab.c"
    break;

  case 44: /* pair_list: pair COMMA_T pair_list  */
#line 223 "compiler/src/parser.y"
        { yyval = node_expression_list((yyloc), yyvsp[-2], yyvsp[0]); }
#line 1864 "parser.tab.c"
    break;

  case 45: /* table_constructor: LEFT_BRACKET_T pair_list RIGHT_BRACKET_T  */
#line 228 "compiler/src/parser.y"
        { yyval = node_table_constructor((yyloc), yyvsp[-1]); }
#line 1870 "parser.tab.c"
    break;

  case 47: /* variable: prefix_expression LEFT_SQUARE_T expression RIGHT_SQUARE_T  */
#line 234 "compiler/src/parser.y"
        { yyval = node_expression_index((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 1876 "parser.tab.c"
    break;

  case 48: /* variable: prefix_expression DOT_T IDENTIFIER_T  */
#line 236 "compiler/src/parser.y"
        { yyval = node_name_index((yyloc), yyvsp[-2], yyvsp[0], false); }
#line 1882 "parser.tab.c"
    break;

  case 49: /* prefix_expression: variable  */
#line 241 "compiler/src/parser.y"
        { yyval = node_name_reference((yyloc), yyvsp[0]); }
#line 1888 "parser.tab.c"
    break;

  case 51: /* prefix_expression: LEFT_PARAN_T expression RIGHT_PARAN_T  */
#line 244 "compiler/src/parser.y"
        { yyval = node_expression_group((yyloc), yyvsp[-1]); }
#line 1894 "parser.tab.c"
    break;

  case 52: /* arguments: LEFT_PARAN_T RIGHT_PARAN_T  */
#line 249 "compiler/src/parser.y"
        { yyval = NULL; }
#line 1900 "parser.tab.c"
    break;

  case 53: /* arguments: LEFT_PARAN_T expression_list RIGHT_PARAN_T  */
#line 251 "compiler/src/parser.y"
        { yyval = yyvsp[-1]; }
#line 1906 "parser.tab.c"
    break;

  case 55: /* call: prefix_expression arguments  */
#line 257 "compiler/src/parser.y"
        { yyval = node_call((yyloc), yyvsp[-1], yyvsp[0], false); }
#line 1912 "parser.tab.c"
    break;

  case 56: /* call: prefix_expression COLON_T IDENTIFIER_T arguments  */
#line 259 "compiler/src/parser.y"
        { yyval = node_call((yyloc), node_name_index((yyloc), yyvsp[-3], yyvsp[-1], true), yyvsp[0], true); }
#line 1918 "parser.tab.c"
    break;

  case 68: /* expression: FUNCTION_T function_body  */
#line 267 "compiler/src/parser.y"
    { yyval = yyvsp[0]; }
#line 1924 "parser.tab.c"
    break;

  case 69: /* program: block  */
#line 272 "compiler/src/parser.y"
        { 
            // *root = node_function_body(@$, node_parameter_list(@$, NULL, node_vararg(@$)), node_type(@$, type_basic(TYPE_BASIC_ANY)), $1);
            //*root = $1;
            struct node *params = node_parameter_list((yyloc), NULL, node_vararg((yyloc)));
            struct node *type = node_type((yyloc), type_basic(TYPE_BASIC_ANY)); 
            *root = node_function_body((yyloc), params, type, yyvsp[0]);
        }
#line 1936 "parser.tab.c"
    break;

  case 70: /* variable_list: variable  */
#line 283 "compiler/src/parser.y"
        { yyval = node_name_reference((yyloc), yyvsp[0]); }
#line 1942 "parser.tab.c"
    break;

  case 71: /* variable_list: variable COMMA_T variable_list  */
#line 285 "compiler/src/parser.y"
        { yyval = node_variable_list((yyloc), yyvsp[0], yyvsp[-2]); }
#line 1948 "parser.tab.c"
    break;

  case 72: /* else_body: ELSEIF_T expression THEN_T block else_body  */
#line 290 "compiler/src/parser.y"
        { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 1954 "parser.tab.c"
    break;

  case 73: /* else_body: ELSEIF_T expression THEN_T block END_T  */
#line 292 "compiler/src/parser.y"
        { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], NULL); }
#line 1960 "parser.tab.c"
    break;

  case 74: /* else_body: ELSE_T block END_T  */
#line 294 "compiler/src/parser.y"
        { yyval = yyvsp[-1]; }
#line 1966 "parser.tab.c"
    break;

  case 75: /* function_body: LEFT_PARAN_T parameter_list RIGHT_PARAN_T COLON_T type_list block END_T  */
#line 309 "compiler/src/parser.y"
        { yyval = node_function_body((yyloc), yyvsp[-5], yyvsp[-2], yyvsp[-1]); }
#line 1972 "parser.tab.c"
    break;

  case 76: /* function_body: LEFT_PARAN_T parameter_list RIGHT_PARAN_T block END_T  */
#line 311 "compiler/src/parser.y"
        { yyval = node_function_body((yyloc), yyvsp[-3], NULL, yyvsp[-1]); }
#line 1978 "parser.tab.c"
    break;

  case 77: /* function_body: LEFT_PARAN_T RIGHT_PARAN_T COLON_T type_list block END_T  */
#line 313 "compiler/src/parser.y"
        { yyval = node_function_body((yyloc), NULL, yyvsp[-2], yyvsp[-1]); }
#line 1984 "parser.tab.c"
    break;

  case 78: /* function_body: LEFT_PARAN_T RIGHT_PARAN_T block END_T  */
#line 315 "compiler/src/parser.y"
        { yyval = node_function_body((yyloc), NULL, NULL, yyvsp[-1]); }
#line 1990 "parser.tab.c"
    break;

  case 79: /* single_assignment: variable EQUAL_T expression  */
#line 323 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), node_name_reference((yyloc), yyvsp[-2]), ASSIGN, yyvsp[0]); }
#line 1996 "parser.tab.c"
    break;

  case 80: /* single_assignment: name_type EQUAL_T expression  */
#line 325 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN, yyvsp[0]); }
#line 2002 "parser.tab.c"
    break;

  case 81: /* assignment: variable_list EQUAL_T expression_list  */
#line 330 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN, yyvsp[0]); }
#line 2008 "parser.tab.c"
    break;

  case 82: /* assignment: variable_list PLUS_EQUAL_T expression_list  */
#line 332 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_ADD, yyvsp[0]); }
#line 2014 "parser.tab.c"
    break;

  case 83: /* assignment: variable_list MINUS_EQUAL_T expression_list  */
#line 334 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_SUB, yyvsp[0]); }
#line 2020 "parser.tab.c"
    break;

  case 84: /* assignment: variable_list ASTERISK_EQUAL_T expression_list  */
#line 336 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_MUL, yyvsp[0]); }
#line 2026 "parser.tab.c"
    break;

  case 85: /* assignment: variable_list SLASH_EQUAL_T expression_list  */
#line 338 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_DIV, yyvsp[0]); }
#line 2032 "parser.tab.c"
    break;

  case 86: /* assignment: variable_list MOD_EQUAL_T expression_list  */
#line 340 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_MOD, yyvsp[0]); }
#line 2038 "parser.tab.c"
    break;

  case 87: /* assignment: variable_list CARROT_EQUAL_T expression_list  */
#line 342 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_POW, yyvsp[0]); }
#line 2044 "parser.tab.c"
    break;

  case 88: /* assignment: variable_list CONCAT_EQUAL_T expression_list  */
#line 344 "compiler/src/parser.y"
        { yyval = node_assignment((yyloc), yyvsp[-2], ASSIGN_CON, yyvsp[0]); }
#line 2050 "parser.tab.c"
    break;

  case 89: /* statement: assignment  */
#line 349 "compiler/src/parser.y"
        { yyval = yyvsp[0]; }
#line 2056 "parser.tab.c"
    break;

  case 90: /* statement: call  */
#line 351 "compiler/src/parser.y"
        { yyval = node_expression_statement((yyloc), yyvsp[0]); }
#line 2062 "parser.tab.c"
    break;

  case 91: /* statement: DO_T block END_T  */
#line 353 "compiler/src/parser.y"
        { yyval = node_block((yyloc), yyvsp[-1], NULL); }
#line 2068 "parser.tab.c"
    break;

  case 92: /* statement: WHILE_T expression DO_T block END_T  */
#line 355 "compiler/src/parser.y"
        { yyval = node_while_loop((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 2074 "parser.tab.c"
    break;

  case 93: /* statement: REPEAT_T block UNTIL_T expression END_T  */
#line 357 "compiler/src/parser.y"
        { yyval = node_repeat_loop((yyloc), yyvsp[-3], yyvsp[-1]); }
#line 2080 "parser.tab.c"
    break;

  case 94: /* statement: IF_T expression THEN_T block END_T  */
#line 359 "compiler/src/parser.y"
        { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], NULL); }
#line 2086 "parser.tab.c"
    break;

  case 95: /* statement: IF_T expression THEN_T block else_body  */
#line 361 "compiler/src/parser.y"
         { yyval = node_if_statement((yyloc), yyvsp[-3], yyvsp[-1], yyvsp[0]); }
#line 2092 "parser.tab.c"
    break;

  case 96: /* statement: FOR_T single_assignment COMMA_T expression DO_T block END_T  */
#line 363 "compiler/src/parser.y"
        { yyval = node_numerical_for_loop((yyloc), yyvsp[-5], yyvsp[-3], node_number((yyloc), "1"), yyvsp[-1]); }
#line 2098 "parser.tab.c"
    break;

  case 97: /* statement: FOR_T single_assignment COMMA_T expression COMMA_T expression DO_T block END_T  */
#line 365 "compiler/src/parser.y"
        { yyval = node_numerical_for_loop((yyloc), yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[-1]); }
#line 2104 "parser.tab.c"
    break;

  case 98: /* statement: FOR_T name_list IN_T expression_list DO_T block END_T  */
#line 367 "compiler/src/parser.y"
        { yyval = node_generic_for_loop((yyloc), node_local((yyloc), yyvsp[-5], yyvsp[-3]), yyvsp[-1]); }
#line 2110 "parser.tab.c"
    break;

  case 99: /* statement: LOCAL_T name_list  */
#line 369 "compiler/src/parser.y"
        { yyval = node_local((yyloc), yyvsp[0], NULL); }
#line 2116 "parser.tab.c"
    break;

  case 100: /* statement: LOCAL_T name_list EQUAL_T expression_list  */
#line 371 "compiler/src/parser.y"
        { yyval = node_local((yyloc), yyvsp[-2], yyvsp[0]); }
#line 2122 "parser.tab.c"
    break;

  case 101: /* statement: LOCAL_T FUNCTION_T IDENTIFIER_T function_body  */
#line 373 "compiler/src/parser.y"
        { yyval = node_local((yyloc), node_type_annotation((yyloc), yyvsp[-1], node_type((yyloc), NULL)), yyvsp[0]); }
#line 2128 "parser.tab.c"
    break;

  case 102: /* statement: last_statement  */
#line 375 "compiler/src/parser.y"
        { yyval = yyvsp[0]; }
#line 2134 "parser.tab.c"
    break;

  case 103: /* block: %empty  */
#line 381 "compiler/src/parser.y"
        { yyval = NULL; }
#line 2140 "parser.tab.c"
    break;

  case 104: /* block: statement  */
#line 383 "compiler/src/parser.y"
        { yyval = node_block((yyloc), yyvsp[0], NULL); }
#line 2146 "parser.tab.c"
    break;

  case 105: /* block: block statement  */
#line 385 "compiler/src/parser.y"
        { yyval = node_block((yyloc), yyvsp[-1], yyvsp[0]); }
#line 2152 "parser.tab.c"
    break;

  case 106: /* last_statement: RETURN_T expression_list  */
#line 390 "compiler/src/parser.y"
        { yyval = node_return((yyloc), yyvsp[0]); }
#line 2158 "parser.tab.c"
    break;

  case 107: /* last_statement: RETURN_T  */
#line 392 "compiler/src/parser.y"
        { yyval = node_return((yyloc), node_nil((yyloc))); }
#line 2164 "parser.tab.c"
    break;

  case 108: /* last_statement: BREAK_T  */
#line 394 "compiler/src/parser.y"
        { yyval = node_break((yyloc)); }
#line 2170 "parser.tab.c"
    break;


#line 2174 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (&yylloc, root, error_count, lexer, YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, root, error_count, lexer);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, root, error_count, lexer, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, root, error_count, lexer);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 397 "compiler/src/parser.y"


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
