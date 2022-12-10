#ifndef _BYTECODE_H
#define _BYTECODE_H

#include <stdint.h>

typedef enum bytecode_version
{
    VERSION_0,
    VERSION_1 
} version_t;

/* Max and min versions that will successfully run in the VM */
#define MAX_VERSION VERSION_1
#define MIN_VERSION VERSION_1

/* Acceptable bytecode version */
#define VERSION_ACCEPTABLE(version) (version >= MIN_VERSION && version <= MAX_VERSION)

typedef enum constant_type
{
    CONSTANT_NIL,
    CONSTANT_BOOLEAN,
    CONSTANT_NUMBER,
    CONSTANT_STRING,
    CONSTANT_ENVIRONMENT
} constant_t;

#endif