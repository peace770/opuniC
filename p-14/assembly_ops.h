#ifndef __ASSEMBLY_OPS_H__
#include <stdlib.h>

#ifndef __UTIL_H__
#include "util.h"
#endif


typedef struct op {
    const int code;
    const char* name;
    const unsigned int src_op;
    const unsigned int dst_op;
    const unsigned int* src_add;
    const unsigned int* dst_add;
} op_t;

const op_t* get_op_details(char* name);

extern char* disallowed_names[35];

extern const op_t assembly_ops[16];

#define __ASSEMBLY_OPS_H__
#endif