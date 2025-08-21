#include "vec_int.h"

struct VecInt
{
    int* items;
    size_t  originalSize;
    size_t  currSize;
    size_t  nItems;
};


VecInt_t* VecInt_create()
{
    size_t size = 5;
    VecInt_t* VecInt;

    if ((size == 0))
    {
        return NULL;
    }

    VecInt = (VecInt_t*)malloc(sizeof(VecInt_t));
    if (!VecInt)
    {
        return NULL;
    }

    VecInt->items = (int*)malloc(sizeof(int) * size);
    if (!VecInt->items)
    {
        free(VecInt);
        return NULL;
    }

    VecInt->currSize = size;
    VecInt->originalSize = size;
    VecInt->nItems = 0;

    return VecInt;
}

void VecInt_destroy(VecInt_t* VecInt)
{
    if (VecInt)
    {
        free(VecInt->items);
        free(VecInt);
    }
}

int VecInt_add(VecInt_t* VecInt, int item)
{
    int* tmp;

    if (!VecInt)
    {
        return 1;
    }

    if (VecInt->nItems == VecInt->currSize)
    {
        // Handle overflow case.
        tmp = (int*)realloc(VecInt->items,
            sizeof(int) * (VecInt->currSize * 2));

        if (NULL == tmp)
        {
            return 1;
        }
        VecInt->items = tmp;
        VecInt->currSize *= VecInt->currSize;
    }

    *(VecInt->items + VecInt->nItems) = item;
    ++VecInt->nItems;

    return 0;
}



int VecInt_get(VecInt_t* VecInt, size_t index, int* item)
{
    if (!VecInt || !item)
    {
        return 1;
    }

    if (index < 0)
    {
        return 1;
    }

    if (index > VecInt->nItems)
    {
        return (1);
    }

    *item = *(VecInt->items + index);

    return 0;
}

int VecInt_numItems(VecInt_t* VecInt, size_t* numOfItems)
{
    if (!VecInt || !numOfItems)
    {
        return 1;
    }

    *numOfItems = VecInt->nItems;

    return 0;
}

int  VecInt_clear(VecInt_t* VecInt) {
    int i;
    if (!VecInt) {
        return 1;
    }
    VecInt->nItems = 0;  
    return 0;
}
