%locations
%defines
%define api.pure
%lex-param {yyscan_t lexer}
%parse-param {YYSTYPE *root}
%parse-param {int *error_count}
%parse-param {yyscan_t lexer}
%token-table

%{
    #include <stdio.h>

    #include "includes.h"
    #include "compiler.h"
    
    #define YYERROR_VERBOSE
    static void yyerror(YYLTYPE *loc, YYSTYPE *root,
                      int *error_count, yyscan_t scanner,
                      char const *s);
%}

/* Values */
%token IDENTIFIER_T
%token INTEGER_T
%token STRING_T

/* Keywords */
%token AND_T
%token BREAK_T
%token DO_T
%token ELSE_T
%token ELSEIF_T
%token END_T
%token FALSE_T
%token TRUE_T
%token FOR_T
%token FUNCTION_T
%token IF_T
%token IN_T
%token LOCAL_T
%token NIL_T
%token NOT_T
%token OR_T
%token REPEAT_T
%token RETURN_T
%token THEN_T
%token UNTIL_T
%token WHILE_T

/* Symbols */
%token PLUS_T/*             +     */         
%token MINUS_T/*            -     */
%token ASTERISK_T/*         *     */
%token SLASH_T/*            /     */
%token EQUAL_T/*            =     */
%token LEFT_PARAN_T/*       (     */
%token RIGHT_PARAN_T/*      )     */
%token CARROT_T/*           ^     */
%token GREATER_THAN_T/*     >     */
%token LESS_THAN_T/*        <     */
%token SQUIGGLE_T/*         ~     */
%token COLON_T/*            :     */
%token POUND_T/*            #     */
%token DOT_T/*              .     */

/* Complex symbols */
%token DOUBLE_EQUAL_T/*     ==    */
%token NOT_EQUAL_T/*        ~=    */
%token GREATER_EQUAL_T/*    >=    */
%token LESS_EQUAL_T/*       <=    */
%token CONCAT_T/*           ..    */
%token VARARG_T/*           ...   */

%%
identifier
  : IDENTIFIER_T
;
%%

static void yyerror(YYLTYPE *loc,
                    YYSTYPE *root __attribute__((unused)),
                    int *error_count,
                    yyscan_t scanner __attribute__((unused)),
                    char const *s)
{
  compiler_error(*loc, s);
  (*error_count)++;
}

const char *token_to_string(int token) {
    return yytname[token - 255];
}