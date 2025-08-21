#include "vector.h"
#include "errors.h"

#define REALLOC_FACTOR 2

struct Vector
{
    char** items;
    size_t  originalSize;
    size_t  blockSize;
    size_t  currSize;
    size_t  nItems;
};


Vector_t* VectorCreate(size_t size, size_t blockSize) {
    Vector_t* vector;
    if ((size == 0)) {
        return NULL;
    }

    vector = (Vector_t*)malloc(sizeof(Vector_t));
    if (!vector) {
        return NULL;
    }

    vector->items = (char**)malloc(sizeof(char*) * size);
    if (!vector->items) {
        free(vector);
        return NULL;
    }

    vector->currSize = size;
    vector->originalSize = size;
    vector->blockSize = blockSize;
    vector->nItems = 0;

    return vector;
}

void VectorDestroy(Vector_t* vector) {
    int i;
    if (vector) {
        i = vector->nItems;
        while (i-- > 0) {
           free(vector->items[i]);
        }
        free(vector->items);
        free(vector);
    }
}

int VectorAdd(Vector_t* vector, char* item) {
    char** tmp;
    if (!vector) {
        return ERR_MEM_NOT_INIT;
    }
    if (vector->nItems == vector->currSize) {
        /* Handle overflow case.*/
        if (vector->blockSize == 0) {
            return ERR_VECTOR_OVERFLOW;
        }
        tmp = (char**)realloc(vector->items, sizeof(char*) * (vector->currSize + vector->blockSize));

        if (NULL == tmp) {
            return ERR_OOM;
        }
        vector->items = tmp;
        vector->currSize += vector->blockSize;
    }
    *(vector->items + vector->nItems) = item;
    ++vector->nItems;

    return ERR_OK;
}

int VectorDelete(Vector_t* vector, char* item, size_t max_read) {
    char** tmp;
    if (!vector) {
        return ERR_MEM_NOT_INIT;
    }
    
    if (vector->nItems == 0) {
        return ERR_ILLEGAL_OPERATION;
    }

    if ((vector->currSize > vector->originalSize) &&
        (vector->nItems <= vector->currSize - (vector->blockSize * REALLOC_FACTOR)))
    {
        tmp = (char**)realloc(vector->items, sizeof(char*) * (vector->currSize - vector->blockSize));
        if (!tmp){
            return ERR_OOM;
        }
        vector->items = tmp;
        vector->currSize -= vector->blockSize;
    }

    strncpy(item, *(vector->items + vector->nItems - 1), max_read);
    --vector->nItems;

    return ERR_OK;
}

int VectorGet(Vector_t* vector, size_t index, char* item, size_t max_read) {
    if (!vector) {
        return ERR_MEM_NOT_INIT;
    }
    if (index < 0) {
        return ERR_ILLEGAL_OPERATION;
    }
    if (index > vector->nItems) {
        return ERR_ILLEGAL_OPERATION;
    }
    strncpy(item, *(vector->items + index), max_read);

    return ERR_OK;
}


int VectorSet(Vector_t* vector, size_t index, char* item) {
    if (!vector) {
        return ERR_MEM_NOT_INIT;
    }

    if (index < 0) {
        return ERR_ILLEGAL_OPERATION;
    }

    if (index > vector->nItems) {
        return ERR_ILLEGAL_OPERATION;
    }

    *(vector->items + index) = item;

    return ERR_OK;
}

int VectorItemsNum(Vector_t* vector, size_t* numOfItems) {
    if (!vector || !numOfItems) {
        return ERR_MEM_NOT_INIT;
    }

    *numOfItems = vector->nItems;

    return ERR_OK;
}

int  VectorClear(Vector_t* vector) {
    int i;
    if (!vector) {
        return ERR_MEM_NOT_INIT;
    }
    for (i = 0; i < vector->nItems; i++) {
        free(vector->items[i]);
    }
    vector->nItems = 0;  
    return ERR_OK;
}

void VectorPrint(Vector_t* vector)
{
    int i;

    if (!vector)
    {
        printf("\n-------------------------------------------------------\n");
        printf("vector details> Vector is not initialized.\n");
        printf("-------------------------------------------------------\n");
        return;
    }

    printf("\n-------------------------------------------------------\n");
    printf("vector details> nItems : %lu, size: %lu, blockSize : %lu \n", vector->nItems, vector->currSize, vector->blockSize);
    printf("vector items>\n");
    for (i = 0; i < vector->nItems; ++i)
    {
        printf("%dth item: %s", i+1,vector->items[i]);
    }
    printf("\n-------------------------------------------------------\n");
}