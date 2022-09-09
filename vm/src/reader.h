#ifndef _READER_H
#define _READER_H

struct vm_proto;
struct vm_context;

void read_context(FILE *input, struct vm_context *context);

#endif