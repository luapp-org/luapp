/*  compiler.c - only version
 *      all utilities used throughout the compiler
 */

#include "compiler.h"

/*  compiler_error - prints a compiler error to stdout based on params
 *      args: location of error, format, args
 *      rets: none
 */
void compiler_error(YYLTYPE location, const char *format, ...)
{
    va_list ap;
    printf("Error (%d, %d): ", location.first_line, location.first_column);
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
    printf("\n");
}

/*  unhandled_compiler_error - prints a compiler error to stdout based on params (no location)
 *      args: format, args
 *      rets: none
 */
void unhandled_compiler_error(const char *format, ...)
{
    va_list ap;
    printf("Error: ");
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
    printf("\n");
}

/*  clear - clears the given string
 *      args: string
 *      rets: none
 */
void clear(char arr[])
{
    int length = strlen(arr);
    /* remove all of the characters in the string */
    memmove(arr, arr + length, length + 1);
}

/*  usage - prints the usage for the program
 *      args: none
 *      rets: none
 */
void usage()
{
    printf("luapp -s [lexer|parser|type|symbol|ir|codgen] -o [outputfile] [inputfile]\n\n");
    printf(" -s : indicates the name of the stage to stop after.\n");
    printf("      Defaults to the last stage.\n");
    printf(" -o : name of the output file. Defaults to \"output.s\"\n\n");
    printf("You should pass the name of the file to compile.\n");
}