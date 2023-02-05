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
    
    flexstr_t s;
    int first_line, first_col;
    bool comment;
%}

%x LCOMMENT
%x COMMENT
%x LSTRING

newline         \n
ws              [ \t\v\f]

digit           [[:digit:]]
letter          [[:alpha:]]

identifier      {letter}({letter}|{digit})*
number          [+-]?([0-9]+\.?[0-9]*|\.[0-9]+)
string          \"([^"\\\n]|\\(.|\n))*\"|'([^"\\\n]|\\(.|\n))*'
lstring         \[\[(.*?|\n|\r)\]\]

%%


"--[["              { BEGIN(LCOMMENT); }
<LCOMMENT>"]]--"    { BEGIN(INITIAL); }
<LCOMMENT>\n        { yyextra = 1; }
<LCOMMENT>.         { }

"[["                { 
                        BEGIN(LSTRING); 
                        first_line = yylineno; 
                        first_col = yyextra;
                    }
<LSTRING>"]]"       { 
                        BEGIN(INITIAL);

                        /* Hacky method of updating line positions over multiple lines. */
                        yylloc->first_line = first_line;
                        yylloc->last_line = yylineno;
                        yylloc->first_column = first_col;
                        yylloc->last_column = yyextra;

                        *yylval = node_string(*yylloc, fs_getstr(&s)); 
                        return STRING_T;
                    }
<LSTRING>.          { fs_addch(&s, yytext[0]); }
<LSTRING>\n         { fs_addch(&s, '\n'); yyextra = 1; }
<LSTRING><<EOF>>    { compiler_error(*yylloc_param, "unexpected EOF", yytext); yyterminate(); }

"--"                { if (!comment)
                        BEGIN(COMMENT);
                      else 
                        return DECREMENT_T; 
                    }
"//"                { if (comment) 
                        BEGIN(COMMENT); 
                      else {
                          compiler_error(*yylloc_param, "use '--!comment' if c-style comments are perferred"); 
                          yyterminate();
                      }
                    }
<COMMENT>\n         { yyextra = 1; BEGIN(INITIAL); }
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

"number"            return TNUMBER_T;
"string"            return TSTRING_T;
"boolean"           return TBOOLEAN_T;
"any"               return TANY_T;
"Array"             return TARRAY_T;
"Table"             return TTABLE_T;

\[                  return LEFT_SQUARE_T;
\]                  return RIGHT_SQUARE_T;
\+                  return PLUS_T;
-                   return MINUS_T;
\*                  return ASTERISK_T;
\/                  {
                    slash_label:
                        return SLASH_T; 
                    }
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
\{                  return LEFT_BRACKET_T;
\}                  return RIGHT_BRACKET_T;
\;                  /* do nothing */

"=="                return DOUBLE_EQUAL_T;
"~="                return NOT_EQUAL_T;
">="                return GREATER_EQUAL_T;
"<="                return LESS_EQUAL_T;
".."                return CONCAT_T;
"..."               { *yylval = node_vararg(*yylloc); return VARARG_T; }
"+="                return PLUS_EQUAL_T;
"-="                return MINUS_EQUAL_T;
"*="                return ASTERISK_EQUAL_T;
"/="                return SLASH_EQUAL_T;
"%="                return MOD_EQUAL_T;
"^="                return CARROT_EQUAL_T;
"..="               return CONCAT_EQUAL_T;
"++"                return INCREMENT_T;

{identifier}        { *yylval = node_identifier(*yylloc, yytext); return IDENTIFIER_T; }
{number}            { *yylval = node_number(*yylloc, yytext); return NUMBER_T; }
{string}            {
                        /* Hacky: remove quotes only for single line strings */
                        char *res = yytext + 1;
                        res[strlen(res) - 1] = '\0';

                        *yylval = node_string(*yylloc, res); return STRING_T; 
                    }


{newline}           { yyextra = 1; }
{ws}
.                   { compiler_error(*yylloc_param, "unrecognized character %s", yytext); yyterminate(); }
%%

/*  lex_init - initializes the flex lexer
 *      args: lexer, file
 *      rets: none
 */
void lex_init(yyscan_t *lexer, compiler_context_t *context, FILE *input) {
    yylex_init(lexer);
    yyset_in(input, *lexer);
    yyset_extra(1, *lexer);

    fs_init(&s, 0);
    comment = context->is_c_comment;
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
            case NUMBER_T:
                fprintf(output, "%-20lf", val->data.number.value);
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
