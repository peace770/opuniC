#ifndef __MEM_IMAGE_H__
#include <stdlib.h>

#ifndef __UTIL_H__
#include "util.h"
#endif

typedef struct memImage
{
    size_t nItems;
    char mem_image[256][6];
} MemImage;

extern MemImage data_image;

extern MemImage instruction_image;


#define __MEM_IMAGE_H__
#endif