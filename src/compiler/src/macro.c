#include "macro.h"
#include "ctype.h"

#include "util/flexstr.h"

#define is_newline(c) (c == '\n')
#define is_whitespace(c) (c == ' ' || c == '\t' || c == '\v' || c == '\f')

static char *read_macro(FILE *input);
static int fpeek(FILE *stream);
static bool set_macro(compiler_context_t *context, char *name);
static char *trim(char *str);
static void init_default(compiler_context_t *context);

/* macro_init() - initialized compiler context based on the macros used.
 *      args: compiler context, input file
 *      returns: none
 *
 * Node: Sets the file pointer after the last definition of a macro and doesn't close the stream.
 */
void macro_init(compiler_context_t *context, FILE *input)
{
    char c, next;
    fpos_t p;

    init_default(context);

    do {
        c = (char)fgetc(input);
        next = (char)fpeek(input);

        if (is_newline(c) || is_whitespace(c))
            continue;
        else if (c == '-' && next == '-') {
            fgetc(input);

            if ((c = (char)fgetc(input)) != '!') {
                rewind(input);
                break;
            }

            char *m = read_macro(input);

            if (!set_macro(context, m)) {
                lcompiler_error("unknown macro reference \"--!%s\"", m);
                context->error_count++;
            }

            free(m);
        } else {
            ungetc(c, input);
            break;
        }
    } while (c != EOF);
}

/* macro_print() - prints all macro values for debug purposes.
 *      args: compiler context
 *      returns: none
 */
void macro_print(compiler_context_t *context)
{
    printf("--!lenient: %s\n", context->is_strict ? "false" : "true");
    printf("--!carrays: %s\n", context->is_c_array ? "true" : "false");
    printf("--!comment: %s\n", context->is_c_comment ? "true" : "false");
}

static char *read_macro(FILE *input)
{
    flexstr_t s;
    char c;

    fs_init(&s, 0);

    while (!is_newline((c = (char)fgetc(input))))
        fs_addch(&s, c);

    return fs_getstr(&s);
}

static bool set_macro(compiler_context_t *context, char *name)
{
    name = trim(name);

    if (strcmp(name, "lenient") == 0)
        context->is_strict = false;
    else if (strcmp(name, "carrays") == 0)
        context->is_c_array = true;
    else if (strcmp(name, "comment") == 0)
        context->is_c_comment = true;
    else
        return false;

    return true;
}

int fpeek(FILE *stream)
{
    int c;

    c = fgetc(stream);
    ungetc(c, stream);

    return c;
}

char *trim(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

static void init_default(compiler_context_t *context)
{
    context->is_strict = true;
    context->is_c_array = false;
    context->is_c_comment = false;
}