%option yylineno
%option reentrant
%option bison-bridge
%option bison-locations
%option noyywrap noinput nounput nodefault


%{
    #include <stdio.h>
    #include <errno.h>
    #include <string.h>

    #include "compiler.h"
    #include "parser.tab.h"
    #include "node.h"

    /* Tell GCC to ignore the warning for now (must be a bug) */
    #pragma GCC diagnostic ignored "-Wstringop-overflow="

    /* Track locations. */
    #define YY_EXTRA_TYPE int
    #define YY_USER_ACTION { yylloc->first_line = yylloc->last_line = yylineno; \
                           yylloc->first_column = yyextra; \
                           yylloc->last_column = yyextra + yyleng - 1; \
                           yyextra += yyleng; }
    
    char string[0];
    char start = 0;
%}

%x LCOMMENT
%x COMMENT
%x STRING
%x LSTRING

newline         \n
ws              [ \t\v\f]

digit           [[:digit:]]
letter          [[:alpha:]]

identifier      {letter}({letter}|{digit})*
integer         {digit}+

%%
"[["                { BEGIN(LSTRING); clear(string); }
<LSTRING>"\\t"      { strncat(string, "\t", 1); }
<LSTRING>"\\n"      { strncat(string, "\n", 1); }
<LSTRING>"\\a"      { strncat(string, "\a", 1); }
<LSTRING>"\\b"      { strncat(string, "\b", 1); }
<LSTRING>"\\f"      { strncat(string, "\f", 1); }
<LSTRING>"\\r"      { strncat(string, "\r", 1); }
<LSTRING>"\\v"      { strncat(string, "\v", 1); }
<LSTRING>"\\"       { strncat(string, "\\", 1); }
<LSTRING>"]]"       { 
                        *yylval = node_identifier(*yylloc, string, yyleng); 
                        BEGIN(INITIAL); 
                        return STRING_T; 
                    }
<LSTRING><<EOF>>    { compiler_error(*yylloc_param, "unfinished string"); yyterminate(); }
<LSTRING>.          { strncat(string, &yytext[0], 1); }
<LSTRING>\n         { strncat(string, "\n", 1); }

"\""                {   if (!start) {
                            start = '"'; 
                            BEGIN(STRING); 
                        }   
                    }
<STRING>"\""        { 
                        if (start == '"') {
                            start = 0;
                            *yylval = node_string(*yylloc, string, yyleng);
                            clear(string); 
                            BEGIN(INITIAL); 
                            return STRING_T;
                        } else 
                            strncat(string, &yytext[0], 1);
                    }
"'"                 {   if (!start) {
                            start = '\''; 
                            BEGIN(STRING); 
                        }   
                    }
<STRING>"'"        { 
                        if (start == '\'') {
                            start = 0;
                            *yylval = node_string(*yylloc, string, yyleng);
                            clear(string); 
                            BEGIN(INITIAL); 
                            return STRING_T;
                        } else 
                            strncat(string, &yytext[0], 1);
                    }
<STRING>"\\t"       { strncat(string, "\t", 1); }
<STRING>"\\n"       { strncat(string, "\n", 1); }
<STRING>"\\a"       { strncat(string, "\a", 1); }
<STRING>"\\b"       { strncat(string, "\b", 1); }
<STRING>"\\f"       { strncat(string, "\f", 1); }
<STRING>"\\r"       { strncat(string, "\r", 1); }
<STRING>"\\v"       { strncat(string, "\v", 1); }
<STRING>"\\"        { strncat(string, "\\", 1); }
<STRING>"\\\""      { 
                        if (start == '"') 
                            strncat(string, "\"", 1);
                         else 
                            strncat(string, "\\\"", 2);
                    }
<STRING>"\\\'"      { 
                        if (start == '\'') 
                            strncat(string, "'", 1);
                         else 
                            strncat(string, "\\\'", 2);
                    }
<STRING><<EOF>>     { compiler_error(*yylloc_param, "unfinished string"); yyterminate(); }
<STRING>.           { strncat(string, &yytext[0], 1); }

"--[["              { BEGIN(LCOMMENT); }
<LCOMMENT>"]]--"    { BEGIN(INITIAL); }
<LCOMMENT>\n        { }
<LCOMMENT>.         { }

"--"                { BEGIN(COMMENT); }
<COMMENT>\n         { BEGIN(INITIAL); }
<COMMENT>.          { }

"and"               return AND_T;
"break"             return BREAK_T;
"do"                return DO_T;
"else"              return ELSE_T;
"elseif"            return ELSEIF_T;
"end"               return END_T;
"false"             { *yylval = node_boolean(*yylloc, false); return FALSE_T; }
"true"              { *yylval = node_boolean(*yylloc, true); return TRUE_T; }
"for"               return FOR_T;
"function"          return FUNCTION_T;
"if"                return IF_T;
"in"                return IN_T;
"local"             return LOCAL_T;
"nil"               return NIL_T;
"not"               return NOT_T;
"or"                return OR_T;
"repeat"            return REPEAT_T;
"return"            return RETURN_T;
"then"              return THEN_T;
"until"             return UNTIL_T;
"while"             return WHILE_T;

\[                  return LEFT_SQUARE_T;
\]                  return RIGHT_SQUARE_T;
\+                  return PLUS_T;
-                   return MINUS_T;
\*                  return ASTERISK_T;
\/                  return SLASH_T;
\=                  return EQUAL_T;
\)                  return RIGHT_PARAN_T;
\(                  return LEFT_PARAN_T;
\^                  return CARROT_T;
\>                  return GREATER_THAN_T;
\<                  return LESS_THAN_T;
\~                  return SQUIGGLE_T;
\:                  return COLON_T;
\#                  return POUND_T;
\%                  return PERCENT_T;
\,                  return COMMA_T;
"."                 return DOT_T;
\;                  /* do nothing */

"=="                return DOUBLE_EQUAL_T;
"~="                return NOT_EQUAL_T;
">="                return GREATER_EQUAL_T;
"<="                return LESS_EQUAL_T;
".."                return CONCAT_T;
"..."               return VARARG_T;

{identifier}        { *yylval = node_identifier(*yylloc, yytext, yyleng); return IDENTIFIER_T; }
{integer}           { *yylval = node_integer(*yylloc, yytext); return INTEGER_T; }


{newline}           yyextra = 1;
{ws}
.                   { compiler_error(*yylloc_param, "unrecognized charcter %s", yytext); yyterminate(); }
%%

/*  lex_init - initializes the flex lexer
 *      args: lexer, file
 *      rets: none
 */
void lex_init(yyscan_t *lexer, FILE *input) {
    yylex_init(lexer);
    yyset_in(input, *lexer);
    yyset_extra(1, *lexer);
}

/*  lex_destroy - frees the lexer instance 
 *      args: lexer
 *      rets: none
 */
void lex_destroy(yyscan_t *lexer) {
    yylex_destroy(*lexer);
    lexer = NULL;
}

/*  lex_print - prints all of the tokens generated by the lexer
 *      args: lexer, number of errors, output file
 *      rets: none
 */
void lex_print(yyscan_t *lexer, int *error_count, FILE *output) {
    YYSTYPE val;
    YYLTYPE loc;
    int token;

    while ((token = yylex(&val, &loc, lexer)) != 0) {
        if (token < 0) {
            (*error_count)++;
            return;
        } else {
            fprintf(output, "%-20s", token_to_string(token));
        }

        fprintf(output, "%04d:%04d-%04d:%04d", 
                loc.first_line, loc.first_column, loc.last_line, loc.last_column);
        
        fputc('\n', output);
    }
}
