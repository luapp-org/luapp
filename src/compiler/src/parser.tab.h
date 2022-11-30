/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER_T = 258,            /* IDENTIFIER_T  */
    NUMBER_T = 259,                /* NUMBER_T  */
    STRING_T = 260,                /* STRING_T  */
    AND_T = 261,                   /* AND_T  */
    BREAK_T = 262,                 /* BREAK_T  */
    DO_T = 263,                    /* DO_T  */
    ELSE_T = 264,                  /* ELSE_T  */
    ELSEIF_T = 265,                /* ELSEIF_T  */
    END_T = 266,                   /* END_T  */
    FALSE_T = 267,                 /* FALSE_T  */
    TRUE_T = 268,                  /* TRUE_T  */
    FOR_T = 269,                   /* FOR_T  */
    FUNCTION_T = 270,              /* FUNCTION_T  */
    IF_T = 271,                    /* IF_T  */
    IN_T = 272,                    /* IN_T  */
    LOCAL_T = 273,                 /* LOCAL_T  */
    NIL_T = 274,                   /* NIL_T  */
    NOT_T = 275,                   /* NOT_T  */
    OR_T = 276,                    /* OR_T  */
    REPEAT_T = 277,                /* REPEAT_T  */
    RETURN_T = 278,                /* RETURN_T  */
    THEN_T = 279,                  /* THEN_T  */
    UNTIL_T = 280,                 /* UNTIL_T  */
    WHILE_T = 281,                 /* WHILE_T  */
    TNUMBER_T = 282,               /* TNUMBER_T  */
    TSTRING_T = 283,               /* TSTRING_T  */
    TBOOLEAN_T = 284,              /* TBOOLEAN_T  */
    TANY_T = 285,                  /* TANY_T  */
    TARRAY_T = 286,                /* TARRAY_T  */
    TTABLE_T = 287,                /* TTABLE_T  */
    PLUS_T = 288,                  /* PLUS_T  */
    MINUS_T = 289,                 /* MINUS_T  */
    ASTERISK_T = 290,              /* ASTERISK_T  */
    SLASH_T = 291,                 /* SLASH_T  */
    PERCENT_T = 292,               /* PERCENT_T  */
    EQUAL_T = 293,                 /* EQUAL_T  */
    LEFT_PARAN_T = 294,            /* LEFT_PARAN_T  */
    RIGHT_PARAN_T = 295,           /* RIGHT_PARAN_T  */
    RIGHT_SQUARE_T = 296,          /* RIGHT_SQUARE_T  */
    LEFT_SQUARE_T = 297,           /* LEFT_SQUARE_T  */
    CARROT_T = 298,                /* CARROT_T  */
    GREATER_THAN_T = 299,          /* GREATER_THAN_T  */
    LESS_THAN_T = 300,             /* LESS_THAN_T  */
    SQUIGGLE_T = 301,              /* SQUIGGLE_T  */
    COLON_T = 302,                 /* COLON_T  */
    POUND_T = 303,                 /* POUND_T  */
    DOT_T = 304,                   /* DOT_T  */
    COMMA_T = 305,                 /* COMMA_T  */
    LEFT_BRACKET_T = 306,          /* LEFT_BRACKET_T  */
    RIGHT_BRACKET_T = 307,         /* RIGHT_BRACKET_T  */
    DOUBLE_EQUAL_T = 308,          /* DOUBLE_EQUAL_T  */
    NOT_EQUAL_T = 309,             /* NOT_EQUAL_T  */
    GREATER_EQUAL_T = 310,         /* GREATER_EQUAL_T  */
    LESS_EQUAL_T = 311,            /* LESS_EQUAL_T  */
    CONCAT_T = 312,                /* CONCAT_T  */
    VARARG_T = 313,                /* VARARG_T  */
    PLUS_EQUAL_T = 314,            /* PLUS_EQUAL_T  */
    MINUS_EQUAL_T = 315,           /* MINUS_EQUAL_T  */
    ASTERISK_EQUAL_T = 316,        /* ASTERISK_EQUAL_T  */
    SLASH_EQUAL_T = 317,           /* SLASH_EQUAL_T  */
    MOD_EQUAL_T = 318,             /* MOD_EQUAL_T  */
    CARROT_EQUAL_T = 319,          /* CARROT_EQUAL_T  */
    CONCAT_EQUAL_T = 320           /* CONCAT_EQUAL_T  */
  };
  typedef enum yytokentype yytoken_kind_t;
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
