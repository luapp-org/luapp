#ifndef _READER_H
#define _READER_H

struct vm_proto;
struct vm_context;

#define CONST_STRING 0
#define CONST_NUMBER 1
#define CONST_ENV 2

void read_context(FILE *input, struct vm_context *context);

#endif