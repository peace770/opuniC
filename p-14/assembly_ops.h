#ifndef __ASSEMBLY_OPS_H__
#include <stdlib.h>

#ifndef __UTIL_H__
#include "util.h"
#endif

#ifndef __HASHMAP_H__
#include "map.h"
#endif

#ifndef __MEM_IMAGE_H__
#include "mem_image.h"
#endif

typedef struct op {
    const int code;
    const char* name;
    const unsigned int src_op;
    const unsigned int dst_op;
    const unsigned int* src_add;
    const unsigned int* dst_add;
} op_t;

extern char* disallowed_names[35];

extern const op_t assembly_ops[16];

const op_t* get_op_details(char* name);

int is_op_check(char* token);

int is_allowed_name(char* name);

int is_data(char* name);

int analyze_op(char* type, MapEntry* entry, int* mem_address, MemImage* mem_image);

#define __ASSEMBLY_OPS_H__
#endif