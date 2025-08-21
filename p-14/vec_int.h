#ifndef __VEC_INT_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* Forward declaration:*/
typedef struct VecInt
{
    int* items;
    size_t  originalSize;
    size_t  currSize;
    size_t  nItems;
} VecInt_t;

/* size      - The initial allocation size.
   blockSize - The extention block size.    */
VecInt_t* VecInt_create();

void     VecInt_destroy(VecInt_t* vector);

/* Add item to end. */
int   VecInt_add(VecInt_t* vector, int  item); 

int   VecInt_get(VecInt_t* vector, size_t index, int* item);

int   VecInt_numItems(VecInt_t* vector, size_t* numOfItems);

int  VecInt_clear(VecInt_t* VecInt);

#define __VEC_INT_H__
#endif /*__VEC_INT_H__*/