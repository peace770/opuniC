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
        // Handle overflow case.
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

int VectorDelete(Vector_t* vector, char* item) {
    char** tmp;
    if (!vector || !item) {
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

    *item = *(vector->items + vector->nItems - 1);
    --vector->nItems;

    return 0;
}

/* Index from 1 */
int VectorGet(Vector_t* vector, size_t index, char* item) {
    if (!vector || !item) {
        return 1;
    }

    if (index == 0) {
        return 1;
    }

    if (index > vector->nItems) {
        return (1);
    }

    *item = *(vector->items + index - 1);

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
        return (1);
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
