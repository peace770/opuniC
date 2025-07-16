#ifndef ASSEMBLY_OPS_H
#define ASSEMBLY_OPS_H 1

const char* disallowed_names[] =
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
};

const char* assembly_ops[16] =
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
};

#endif