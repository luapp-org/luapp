#ifndef FLEXSTR_H
#define FLEXSTR_H

#include <stdio.h>

#define CHUNKSIZE 20

struct flexstring {
    int fs_space;  /* Total space allocated */
    int fs_used;   /* Total space used */
    char *fs_str;  /* String */
    int fs_growby; /* Amount of byted fs_str will increase by */
};

typedef struct flexstring flexstr_t;

/* Construction and destruction methods */
void fs_init(flexstr_t *p, int amt);
void fs_free(flexstr_t *p);

/* Other methods */
char *fs_getstr(flexstr_t *p);
void fs_addch(flexstr_t *p, char c);
void fs_addstr(flexstr_t *p, char *s);

/* Safe malloc and realloc */
void *smalloc(size_t n);
void *srealloc(void *p, size_t n);

#endif