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
    #include "util/flexstr.h"

    /* Tell GCC to ignore the warning for now (must be a bug) */
    #pragma GCC diagnostic ignored "-Wstringop-overflow="

    /* Track locations. */
    #define YY_EXTRA_TYPE int
    #define YY_USER_ACTION { yylloc->first_line = yylloc->last_line = yylineno; \
                           yylloc->first_column = yyextra; \
                           yylloc->last_column = yyextra + yyleng - 1; \
                           yyextra += yyleng; }
    
    char string[0];
    flexstr_t s;
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
"[["                { BEGIN(LSTRING); fs_init(&s, 0); }
<LSTRING>"\\t"      { fs_addch(&s, '\t'); }
<LSTRING>"\\n"      { fs_addch(&s, '\n'); }
<LSTRING>"\\a"      { fs_addch(&s, '\a'); }
<LSTRING>"\\b"      { fs_addch(&s, '\b'); }
<LSTRING>"\\f"      { fs_addch(&s, '\f'); }
<LSTRING>"\\r"      { fs_addch(&s, '\r'); }
<LSTRING>"\\v"      { fs_addch(&s, '\v'); }
<LSTRING>"\\"       { fs_addch(&s, '\\'); }
<LSTRING>"]]"       { 
                        *yylval = node_string(*yylloc, fs_getstr(&s)); 
                        fs_free(&s);
                        BEGIN(INITIAL); 
                        return STRING_T; 
                    }
<LSTRING><<EOF>>    { compiler_error(*yylloc_param, "unfinished string"); yyterminate(); }
<LSTRING>.          { fs_addch(&s, yytext[0]); }
<LSTRING>\n         { fs_addch(&s, '\n'); }

"\""                {   if (!start) {
                            start = '"'; 
                            fs_init(&s, 0);
                            BEGIN(STRING); 
                        }   
                    }
<STRING>"\""        { 
                        if (start == '"') {
                            start = 0;
                            *yylval = node_string(*yylloc, fs_getstr(&s));
                            fs_free(&s);
                            BEGIN(INITIAL); 
                            return STRING_T;
                        } else 
                            fs_addch(&s, yytext[0]);
                    }
"'"                 {   if (!start) {
                            start = '\''; 
                            fs_init(&s, 0);
                            BEGIN(STRING); 
                        }   
                    }
<STRING>"'"        { 
                        if (start == '\'') {
                            start = 0;
                            *yylval = node_string(*yylloc, fs_getstr(&s));
                            fs_free(&s); 
                            BEGIN(INITIAL); 
                            return STRING_T;
                        } else 
                            fs_addch(&s, yytext[0]);
                    }
<STRING>"\\t"      { fs_addch(&s, '\t'); }
<STRING>"\\n"      { fs_addch(&s, '\n'); }
<STRING>"\\a"      { fs_addch(&s, '\a'); }
<STRING>"\\b"      { fs_addch(&s, '\b'); }
<STRING>"\\f"      { fs_addch(&s, '\f'); }
<STRING>"\\r"      { fs_addch(&s, '\r'); }
<STRING>"\\v"      { fs_addch(&s, '\v'); }
<STRING>"\\"       { fs_addch(&s, '\\'); }
<STRING>"\\\""      { 
                        if (start == '"') 
                            fs_addch(&s, '\"');
                         else 
                            fs_addstr(&s, "\\\"");
                    }
<STRING>"\\\'"      { 
                        if (start == '\'') 
                            fs_addch(&s, '\'');
                         else 
                            fs_addstr(&s, "\\\'");
                    }
<STRING><<EOF>>     { compiler_error(*yylloc_param, "unfinished string"); yyterminate(); }
<STRING>.           { fs_addch(&s, yytext[0]); }

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

{identifier}        { *yylval = node_identifier(*yylloc, yytext); return IDENTIFIER_T; }
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
        
        switch (token) {
            case INTEGER_T:
                break;
            case STRING_T:
                fprintf(output, "%-20s", val->data.string.value);
                break;
            case IDENTIFIER_T:
                fprintf(output, "%-20s", val->data.identifier.name);
                break;
            default:
                fprintf(output, "%-20s", "");
                break;
        }

        fprintf(output, "%04d:%04d-%04d:%04d", 
            loc.first_line, loc.first_column, loc.last_line, loc.last_column);

        fputc('\n', output);
    }
}
