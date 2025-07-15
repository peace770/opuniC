#include "vector.h"

#define REALLOC_FACTOR 2

struct Vector
{
    int* items;
    size_t  originalSize;
    size_t  blockSize;
    size_t  currSize;
    size_t  nItems;
};


Vector_t* VectorCreate(size_t size, size_t blockSize)
{
    Vector_t* vector;

    if ((size == 0))
    {
        return NULL;
    }

    vector = (Vector_t*)malloc(sizeof(Vector_t));
    if (!vector)
    {
        return NULL;
    }

    vector->items = (int*)malloc(sizeof(int) * size);
    if (!vector->items)
    {
        free(vector);
        return NULL;
    }

    vector->currSize = size;
    vector->originalSize = size;
    vector->blockSize = blockSize;
    vector->nItems = 0;

    return vector;
}

void VectorDestroy(Vector_t* vector)
{
    if (vector)
    {
        free(vector->items);
        free(vector);
    }
}

int VectorAdd(Vector_t* vector, int item)
{
    int* tmp;

    if (!vector)
    {
        return 1;
    }

    if (vector->nItems == vector->currSize)
    {
        // Handle overflow case.
        if (vector->blockSize == 0)
        {
            return 1;
        }
        tmp = (int*)realloc(vector->items,
            sizeof(int) * (vector->currSize + vector->blockSize));

        if (NULL == tmp)
        {
            return 1;
        }
        vector->items = tmp;
        vector->currSize += vector->blockSize;
    }

    *(vector->items + vector->nItems) = item;
    ++vector->nItems;

    return 0;
}

int VectorDelete(Vector_t* vector, int* item)
{
    int* tmp;

    if (!vector || !item)
    {
        return 1;
    }

    if (vector->nItems == 0)
    {
        return 1;
    }

    if ((vector->currSize > vector->originalSize) &&
        (vector->nItems <= vector->currSize - (vector->blockSize * REALLOC_FACTOR)))
    {
        tmp = (int*)realloc(vector->items,
            sizeof(int) * (vector->currSize - vector->blockSize));
        if (!tmp)
        {
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
int VectorGet(Vector_t* vector, size_t index, int* item)
{
    if (!vector || !item)
    {
        return 1;
    }

    if (index == 0)
    {
        return 1;
    }

    if (index > vector->nItems)
    {
        return (1);
    }

    *item = *(vector->items + index - 1);

    return 0;
}

/* Index from 1 */
int VectorSet(Vector_t* vector, size_t index, int item)
{
    if (!vector)
    {
        return 1;
    }

    if (index == 0)
    {
        return 1;
    }

    if (index > vector->nItems)
    {
        return (1);
    }

    *(vector->items + index - 1) = item;

    return 0;
}

int VectorItemsNum(Vector_t* vector, size_t* numOfItems)
{
    if (!vector || !numOfItems)
    {
        return 1;
    }

    *numOfItems = vector->nItems;

    return 0;
}


/*  Unit-Test functions  */
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
    printf("vector details> nItems : %zu, size: %zu, blockSize : %zu \n", vector->nItems, vector->currSize, vector->blockSize);
    printf("vector items>   ");
    for (i = 0; i < vector->nItems; ++i)
    {
        printf("%d ", vector->items[i]);
    }
    printf("\n-------------------------------------------------------\n");
}