#include "compiler.h"

void compiler_error(YYLTYPE location, const char *format, ...)
{
    va_list ap;
    printf("Error (%d, %d): ", location.first_line, location.first_column);
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
    printf("\n");
}

char *concat(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    /* allocate enough memory for the new string and it's null terminator */
    char *result = malloc(len1 + len2 + 1);
    /* make sure we were able to allocate enough space */
    if (result == NULL)
        return NULL;
    /* copy the strings into result */
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

void clear(char arr[])
{
    int length = strlen(arr);
    /* remove all of the characters in the string */
    memmove(arr, arr + length, length + 1);
}