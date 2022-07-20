/*  parser.y - only version
 *      parses lexical tokens into an AST (abstract syntax tree)
 */
 
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
%}

/* Values */
%token IDENTIFIER_T
%token NUMBER_T
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

/* Type annotations */
%token TNUMBER_T
%token TSTRING_T
%token TBOOLEAN_T
%token TARRAY_T
%token TTABLE_T

/* Symbols */
%token PLUS_T/*             +     */         
%token MINUS_T/*            -     */
%token ASTERISK_T/*         *     */
%token SLASH_T/*            /     */
%token PERCENT_T/*          %     */
%token EQUAL_T/*            =     */
%token LEFT_PARAN_T/*       (     */
%token RIGHT_PARAN_T/*      )     */
%token RIGHT_SQUARE_T/*     ]     */
%token LEFT_SQUARE_T/*      [     */
%token CARROT_T/*           ^     */
%token GREATER_THAN_T/*     >     */
%token LESS_THAN_T/*        <     */
%token SQUIGGLE_T/*         ~     */
%token COLON_T/*            :     */
%token POUND_T/*            #     */
%token DOT_T/*              .     */
%token COMMA_T/*            ,     */
%token LEFT_BRACKET_T/*     {     */
%token RIGHT_BRACKET_T/*    }     */

/* Complex symbols */
%token DOUBLE_EQUAL_T/*     ==    */
%token NOT_EQUAL_T/*        ~=    */
%token GREATER_EQUAL_T/*    >=    */
%token LESS_EQUAL_T/*       <=    */
%token CONCAT_T/*           ..    */
%token VARARG_T/*           ...   */
%token PLUS_EQUAL_T/*       +=    */
%token MINUS_EQUAL_T/*      -=    */
%token ASTERISK_EQUAL_T/*   *=    */
%token SLASH_EQUAL_T/*      /=    */
%token MOD_EQUAL_T/*        %=    */
%token CARROT_EQUAL_T/*     ^=    */
%token CONCAT_EQUAL_T/*     ..=    */

%start program

%%

binary_operation
  : expression PLUS_T expression
      { $$ = node_binary_operation(@2, BINOP_ADD, $1, $3); }
  | expression MINUS_T expression
      { $$ = node_binary_operation(@2, BINOP_SUB, $1, $3); }
  | expression ASTERISK_T expression
      { $$ = node_binary_operation(@2, BINOP_MUL, $1, $3); }
  | expression SLASH_T expression
      { $$ = node_binary_operation(@2, BINOP_DIV, $1, $3); }
  | expression CARROT_T expression
      { $$ = node_binary_operation(@2, BINOP_POW, $1, $3); }
  | expression PERCENT_T expression
      { $$ = node_binary_operation(@2, BINOP_MOD, $1, $3); }
  | expression CONCAT_T expression
      { $$ = node_binary_operation(@2, BINOP_CONCAT, $1, $3); }
  | expression LESS_THAN_T expression
      { $$ = node_binary_operation(@2, BINOP_LT, $1, $3); }
  | expression GREATER_THAN_T expression
      { $$ = node_binary_operation(@2, BINOP_GT, $1, $3); }
  | expression GREATER_EQUAL_T expression
      { $$ = node_binary_operation(@2, BINOP_GE, $1, $3); }
  | expression LESS_EQUAL_T expression
      { $$ = node_binary_operation(@2, BINOP_LE, $1, $3); }
  | expression NOT_EQUAL_T expression
      { $$ = node_binary_operation(@2, BINOP_NE, $1, $3); }
  | expression DOUBLE_EQUAL_T expression
      { $$ = node_binary_operation(@2, BINOP_EQ, $1, $3); }
  | expression AND_T expression
      { $$ = node_binary_operation(@2, BINOP_AND, $1, $3); }
  | expression OR_T expression
      { $$ = node_binary_operation(@2, BINOP_OR, $1, $3); }
;

unary_operation
  : MINUS_T expression
      { $$ = node_unary_operation(@$, UNOP_NEG, $2); }
  | NOT_T expression
      { $$ = node_unary_operation(@$, UNOP_NOT, $2); }
  | POUND_T expression
      { $$ = node_unary_operation(@$, UNOP_LEN, $2); }
;

expression_list 
    : expression
    | expression COMMA_T expression_list
        {
            $$ = node_expression_list(@$, $3, $1); 
        }
;

parameter_list 
    : name_list
        { $$ = node_parameter_list(@$, $1, NULL); }
    | name_list COMMA_T VARARG_T
        { $$ = node_parameter_list(@$, $1, $3); }
    | VARARG_T
        { $$ = node_parameter_list(@$, NULL, $1); }
;

name_list 
    : name_type
    | name_type COMMA_T name_list 
        { $$ = node_name_list(@$, $3, $1); }
;

type_list 
    : type
    | type COMMA_T type_list
        { $$ = node_type_list(@$, $3, $1); }
;

type 
    : TNUMBER_T
        { $$ = node_type(@$, type_basic(TYPE_BASIC_NUMBER)); }
    | TSTRING_T
        { $$ = node_type(@$, type_basic(TYPE_BASIC_STRING)); }
    | TBOOLEAN_T
        { $$ = node_type(@$, type_basic(TYPE_BASIC_BOOLEAN)); }
    | TARRAY_T LESS_THAN_T type GREATER_THAN_T 
        { $$ = node_type_array(@$, $3); }
    | TTABLE_T LESS_THAN_T type COMMA_T type GREATER_THAN_T 
        { $$ = node_type_table(@$, $3, $5); }
;

name_type 
    : IDENTIFIER_T COLON_T type
        { $$ = node_type_annotation(@$, $1, $3); }
    | IDENTIFIER_T
;

array_constructor 
    : LEFT_BRACKET_T expression_list RIGHT_BRACKET_T
        { $$ = node_array_constructor(@$, $2); }
    | LEFT_BRACKET_T RIGHT_BRACKET_T
        { $$ = node_array_constructor(@$, NULL); }
;

pair
    : LEFT_SQUARE_T expression RIGHT_SQUARE_T EQUAL_T expression
        { $$ = node_key_value_pair(@$, $2, $5); }
;

pair_list
    : pair
    | pair COMMA_T pair_list
        { $$ = node_expression_list(@$, $1, $3); }
;

table_constructor 
    : LEFT_BRACKET_T pair_list RIGHT_BRACKET_T
        { $$ = node_table_constructor(@$, $2); }
    | LEFT_BRACKET_T RIGHT_BRACKET_T
        { $$ = node_table_constructor(@$, NULL); }
;

variable 
    : IDENTIFIER_T
    | prefix_expression LEFT_SQUARE_T expression RIGHT_SQUARE_T
        { $$ = node_expression_index(@$, $1, $3); }
    | prefix_expression DOT_T IDENTIFIER_T
        { $$ = node_name_index(@$, $1, $3, false); }
;

prefix_expression
    : variable
        { $$ = node_name_reference(@$, $1); }
    | call
    | LEFT_PARAN_T expression RIGHT_PARAN_T
        { $$ = node_expression_group(@$, $2); }
;

arguments
    : LEFT_PARAN_T RIGHT_PARAN_T
        { $$ = NULL; }
    | LEFT_PARAN_T expression_list RIGHT_PARAN_T
        { $$ = $2; }
    | STRING_T
;

call 
    : prefix_expression arguments
        { $$ = node_call(@$, $1, $2, false); }
    | prefix_expression COLON_T IDENTIFIER_T arguments
        { $$ = node_call(@$, node_name_index(@$, $1, $3, true), $4, true); }
;

expression
  : NIL_T  | FALSE_T | TRUE_T | NUMBER_T | STRING_T | VARARG_T
  | binary_operation | unary_operation | prefix_expression | array_constructor
  | table_constructor 
  | FUNCTION_T function_body
    { $$ = $2; }
;

program 
    : block
        { *root = $1; }
;

variable_list 
    : variable
        { $$ = node_name_reference(@$, $1); }
    | variable COMMA_T variable_list
        { $$ = node_variable_list(@$, $3, $1); }
;

else_body
    : ELSEIF_T expression THEN_T block else_body
        { $$ = node_if_statement(@$, $2, $4, $5); }
    | ELSEIF_T expression THEN_T block END_T
        { $$ = node_if_statement(@$, $2, $4, NULL); }
    | ELSE_T block END_T
        { $$ = $2; }
;

/* function_name 
    : IDENTIFIER_T
    | IDENTIFIER_T DO_T IDENTIFIER_T
        { $$ = node_name_index(@$, $1, $3, false); }
    | IDENTIFIER_T COLON_T IDENTIFIER_T
        { $$ = node_name_index(@$, $1, $3, true); }
    | IDENTIFIER_T DO_T IDENTIFIER_T COLON_T IDENTIFIER_T
        { $$ = node_name_index(@$, $1, node_name_index(@$, $3, $4, true), false); } */
;

function_body 
    : LEFT_PARAN_T parameter_list RIGHT_PARAN_T COLON_T type_list block END_T
        { $$ = node_function_body(@$, $2, $5, $6); }
    | LEFT_PARAN_T parameter_list RIGHT_PARAN_T block END_T
        { 
            $$ = node_function_body(@$, $2, NULL, $4); 
        }
    | LEFT_PARAN_T RIGHT_PARAN_T COLON_T type_list block END_T
        { $$ = node_function_body(@$, NULL, $4, $5); }
    | LEFT_PARAN_T RIGHT_PARAN_T block END_T
        { $$ = node_function_body(@$, NULL, NULL, $3); }
;

/* DIFF: Added `single_assignment` to for loop syntax --> any variable can be incremented 
 *      (Not in vanilla Lua 5.1)
 */
single_assignment 
    : variable EQUAL_T expression
        { $$ = node_assignment(@$, $1, ASSIGN, $3); }
;

assignment
    : variable_list EQUAL_T expression_list
        { $$ = node_assignment(@$, $1, ASSIGN, $3); }
    | variable_list PLUS_EQUAL_T expression_list
        { $$ = node_assignment(@$, $1, ASSIGN_ADD, $3); }
    | variable_list MINUS_EQUAL_T expression_list
        { $$ = node_assignment(@$, $1, ASSIGN_SUB, $3); }
    | variable_list ASTERISK_EQUAL_T expression_list
        { $$ = node_assignment(@$, $1, ASSIGN_MUL, $3); }
    | variable_list SLASH_EQUAL_T expression_list
        { $$ = node_assignment(@$, $1, ASSIGN_DIV, $3); }
    | variable_list MOD_EQUAL_T expression_list
        { $$ = node_assignment(@$, $1, ASSIGN_MOD, $3); }
    | variable_list CARROT_EQUAL_T expression_list
        { $$ = node_assignment(@$, $1, ASSIGN_POW, $3); }
    | variable_list CONCAT_EQUAL_T expression_list
        { $$ = node_assignment(@$, $1, ASSIGN_CON, $3); }
;

statement
    : assignment
        { $$ = $1; }
    | call 
        { $$ = node_expression_statement(@$, $1); }
    | DO_T block END_T
        { $$ = node_block(@$, $2, NULL); }
    | WHILE_T expression DO_T block END_T
        { $$ = node_while_loop(@$, $2, $4); }
    | REPEAT_T block UNTIL_T expression END_T
        { $$ = node_repeat_loop(@$, $2, $4); }
    | IF_T expression THEN_T block END_T
        { $$ = node_if_statement(@$, $2, $4, NULL); }
    | IF_T expression THEN_T block else_body
         { $$ = node_if_statement(@$, $2, $4, $5); }
    | FOR_T single_assignment COMMA_T expression DO_T block END_T
        { $$ = node_numerical_for_loop(@$, $2, $4, node_number(@$, "1"), $6); }
    | FOR_T name_list IN_T expression_list DO_T block END_T
        { $$ = node_generic_for_loop(@$, $2, $4, $6); }
    | LOCAL_T name_list 
        { $$ = node_local(@$, $2, node_nil(@$)); }
    | LOCAL_T name_list EQUAL_T expression_list
        { $$ = node_local(@$, $2, $4); }
    | FUNCTION_T 
    | last_statement
        { $$ = $1; }

;

block 
    : %empty
        { $$ = NULL; }
    | statement
        { $$ = node_block(@$, $1, NULL); }
    | block statement
        { $$ = node_block(@$, $1, $2); }
;

last_statement 
    : RETURN_T expression_list
        { $$ = node_return(@$, $2); }
    | RETURN_T
        { $$ = node_return(@$, node_nil(@$)); }
    | BREAK_T
        { $$ = node_break(@$); }
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