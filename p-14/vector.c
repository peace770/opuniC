#include "vector.h"

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
    int i = vector->nItems;
    if (vector) {
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
        return 1;
    }
    if (vector->nItems == vector->currSize) {
        /* Handle overflow case.*/
        if (vector->blockSize == 0) {
            return 1;
        }
        tmp = (char**)realloc(vector->items, sizeof(char*) * (vector->currSize + vector->blockSize));

        if (NULL == tmp) {
            return 1;
        }
        vector->items = tmp;
        vector->currSize += vector->blockSize;
    }
    *(vector->items + vector->nItems) = item;
    ++vector->nItems;

    return 0;
}

int VectorDelete(Vector_t* vector, char* item, size_t max_read) {
    char** tmp;
    if (!vector) {
        return 1;
    }
    
    if (vector->nItems == 0) {
        return 1;
    }

    if ((vector->currSize > vector->originalSize) &&
        (vector->nItems <= vector->currSize - (vector->blockSize * REALLOC_FACTOR)))
    {
        tmp = (char**)realloc(vector->items, sizeof(char*) * (vector->currSize - vector->blockSize));
        if (!tmp){
            return (1);
        }
        vector->items = tmp;
        vector->currSize -= vector->blockSize;
    }

    strncpy(item, *(vector->items + vector->nItems - 1), max_read);
    --vector->nItems;

    return 0;
}

int VectorGet(Vector_t* vector, size_t index, char* item, size_t max_read) {
    if (!vector) {
        return 1;
    }
    if (index < 0) {
        return 1;
    }
    if (index > vector->nItems) {
        return 1;
    }
    strncpy(item, *(vector->items + index), max_read);

    return 0;
}


int VectorSet(Vector_t* vector, size_t index, char* item) {
    if (!vector) {
        return 1;
    }

    if (index < 0) {
        return 1;
    }

    if (index > vector->nItems) {
        return 1;
    }

    *(vector->items + index) = item;

    return 0;
}

int VectorItemsNum(Vector_t* vector, size_t* numOfItems) {
    if (!vector || !numOfItems) {
        return 1;
    }

    *numOfItems = vector->nItems;

    return 0;
}

int  VectorClear(Vector_t* vector) {
    int i;
    if (!vector) {
        return 1;
    }
    for (i = 0; i < vector->nItems; i++) {
        free(vector->items[i]);
    }
    vector->nItems = 0;  
    VectorPrint(vector);
    return 0;
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