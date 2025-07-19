#ifndef TAGGED_UNION_H
#define TAGGED_UNION_H 1


#ifndef _STDLIB_H
#include <stdlib.h>
#endif

typedef enum {NONE = -1, DATA, STRING, MAT, ENTRY, EXTERN, MACRO, CODE} dataTypes;

typedef struct tagged_union
{
    dataTypes type;
    union {
        void* null;
        int* arr;
        char* str;
        int** mat;
        char* label;
        char* label;
        char** macro;
        char* code;
    };
}Tunion;

/*input data to the union. gets a pointer to a tagged union,
 and a type from dataTypes enum and void pointer
to the data. returns a non negative integer on success, -1 on failure*/
int fill_union(Tunion* Union, dataTypes type, void* dataptr);

#endif