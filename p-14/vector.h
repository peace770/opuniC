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
int   VectorAdd(Vector_t* vector, int  item); 

/* Delete item from the end. */
int   VectorDelete(Vector_t* vector, int* item);

/* The Index range in the following functions is : 1..numOfItems */
int   VectorGet(Vector_t* vector, size_t index, int* item);

int   VectorSet(Vector_t* vector, size_t index, int  item);

int   VectorItemsNum(Vector_t* vector, size_t* numOfItems);


/*  Unit-Test functions  */
void VectorPrint(Vector_t* vector);

#endif /*__VECTOR_H__*/