#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <stdio.h>

// Forward declaration:
typedef struct Vector Vector_t;

/* size      - The initial allocation size.
   blockSize - The extention block size.    */
Vector_t* VectorCreate(size_t size, size_t blockSize);

void     VectorDestroy(Vector_t* vector);

/* Add item to end. */
int   VectorAdd(Vector_t* vector, char*  item); 

/* Delete item from the end. */
int   VectorDelete(Vector_t* vector, char* item);

/* The Index range in the following functions is : 1..numOfItems */
int   VectorGet(Vector_t* vector, size_t index, char* item);

int   VectorSet(Vector_t* vector, size_t index, char* item);

int   VectorItemsNum(Vector_t* vector, size_t* numOfItems);

#endif /*__VECTOR_H__*/