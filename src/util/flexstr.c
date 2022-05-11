/*  flexstr.c - 1.0
 *      dynamic string library
 */

#include "flexstr.h"

#include <stdlib.h>
#include <string.h>

/* fs_init() -- initializes a new flex string instance
 *      args: instance, amount to grow by
 *
 * Note: If `amt` is 0 then the string will grow by CHUNKSIZE
 */
void fs_init(flexstr_t *p, int amt)
{
    p->fs_str = NULL;
    p->fs_space = p->fs_used = 0;
    p->fs_growby = (amt > 0 ? amt : CHUNKSIZE);
}

/* fs_free() -- free a flex string instance
 *      args: instance
 */
void fs_free(flexstr_t *p) { free(p->fs_str); }

/* fs_getstr() -- returns the string in the flex string instance
 *      args: instance
 *      returns: the string
 *
 * Note: The function terminates the string for you.
 */
char *fs_getstr(flexstr_t *p)
{
    /* First make sure there's room for the '\0' */
    if (p->fs_used == p->fs_space) { /* string is full, add room for one more char */
        p->fs_str = srealloc(p->fs_str, ++p->fs_space);
    }

    /* Add terminating '\0'.  Don't increment fs_used -- the '\0' is not part of
     * the string, and shouldn't be counted if someone wants to continue adding
     * characters to the string later.
     */
    p->fs_str[p->fs_used] = '\0';

    /* Now return the (terminated) string. */
    return p->fs_str;
}

/* fs_addch() -- adds a character to the flex string
 *      args: flex string, character
 *
 * Note: Invokes smalloc() if fs_str hasn't been alloced yet. Invokes srealloc to resize fs_str.
 */
void fs_addch(flexstr_t *p, char c)
{
    /* Call smalloc() if we haven't allocated any memory yet */
    if (p->fs_space == 0) {
        p->fs_str = smalloc(p->fs_growby);
        p->fs_used = 0;
        p->fs_space = p->fs_growby;
    } else if (p->fs_used + 1 >= p->fs_space) { /* +1 for \0 */
        p->fs_space += p->fs_growby;
        p->fs_str = srealloc(p->fs_str, p->fs_space);
    }
    p->fs_str[p->fs_used++] = c;
}

void fs_addstr(flexstr_t *p, char *s)
{
    int c;

    /* Add each character individually */
    while ((c = *s++) != '\0')
        fs_addch(p, c);
}

/* smalloc() -- safely allocates memory for an object
 *      args: number of bytes
 *      returns: newly allocated memory
 *
 * Note: This function handles malloc() errors.
 */
void *smalloc(size_t n)
{
    void *res;

    if ((res = malloc(n)) == NULL) {
        fprintf(stderr, "malloc(): out of memory\n");
        exit(1);
    }
    return res;
}

/* srealloc() -- safely allocates additional memory for an object
 *      args: object, number of bytes
 *      returns: newly allocated memory
 *
 * Note: This function handles realloc() errors.
 */
void *srealloc(void *p, size_t n)
{
    void *res;

    if ((res = realloc(p, n)) == NULL) {
        fprintf(stderr, "realloc(): unexpected failure\n");
        exit(1);
    }
    return res;
}