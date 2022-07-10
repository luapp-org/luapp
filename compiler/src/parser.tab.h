/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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