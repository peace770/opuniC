#include "assembly_ops.h"

char* disallowed_names[] =
{
    "mov",
    "cmp",
    "add",
    "sub",
    "lea",
    "clr",
    "not",
    "inc",
    "dec",
    "jmp",
    "bne",
    "jsr",
    "red",
    "prn",
    "rts",
    "stop",
    "data",
    "string",
    "mat",
    "entry",
    "extern",
    "PSW",
    "r0",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7",
    ".data",
    ".string",
    ".mat",
    ".entry",
    ".extern"
};
const unsigned int any_addressing[] = {0,1,2,3};
const unsigned int any_mem_addressing[] = {1,2,3};
const unsigned int no_reg_addressing[] = {1,2};

const op_t assembly_ops[] = 
{
    {0,     "mov",  1, 1, any_addressing,       any_mem_addressing},
    {1,     "cmp",  1, 1, any_addressing,       any_addressing},
    {2,     "add",  1, 1, any_addressing,       any_mem_addressing},
    {3,     "sub",  1, 1, any_addressing,       any_mem_addressing},
    {4,     "lea",  1, 1, no_reg_addressing,    any_mem_addressing},
    {5,     "clr",  0, 1, NULL,                 any_mem_addressing},
    {6,     "not",  0, 1, NULL,                 any_mem_addressing},
    {7,     "inc",  0, 1, NULL,                 any_mem_addressing},
    {8,     "dec",  0, 1, NULL,                 any_mem_addressing},
    {9,     "jmp",  0, 1, NULL,                 any_mem_addressing},
    {10,    "bne",  0, 1, NULL,                 any_mem_addressing},
    {11,    "jsr",  0, 1, NULL,                 any_mem_addressing},
    {12,    "red",  0, 1, NULL,                 any_mem_addressing},
    {13,    "prn",  0, 1, NULL,                 any_addressing},
    {14,    "rts",  0, 0, NULL,                 NULL},
    {15,    "stop", 0, 0, NULL,                 NULL},
};

const op_t* get_op_details(char* name) {
    int i;
    for (i = 0; i < ARRAY_SIZE(assembly_ops); i++) {
        if (strcmp(name, assembly_ops[i].name) == 0) {
            return &assembly_ops[i];
        }
    }
    return NULL;
}