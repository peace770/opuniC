#include "tagged_union.h"

int fill_union(Tunion* Union, dataTypes type, void* dataptr) {
    int found = -1;
    switch (type)
    {
    case DATA:
        Union->type = DATA;
        Union->u.arr = (int*) dataptr;
        found = DATA;
        break;
    case STRING:
        Union->type = STRING;
        Union->u.str = (char*) dataptr;
        found = STRING;
        break;
    case MAT:
        Union->type = MAT;
        Union->u.mat = (int**) dataptr;
        found = MAT;
        break;
    case ENTRY:
        Union->type = ENTRY;
        Union->u.entryLabel = (char*) dataptr;
        found = ENTRY;
        break;
    case EXTERN:
        Union->type = EXTERN;
        Union->u.externLabel = (char*) dataptr;
        found = EXTERN;
        break;
    case MACRO:
        Union->type = MACRO;
        Union->u.macro = (char**) dataptr;
        found = MACRO;
        break;
    case CODE:
        Union->type = CODE;
        Union->u.code = (char*) dataptr;
        found = CODE;
        break;
    default:
        Union->type = NONE;
        Union->u.null = NULL;
        found = NONE;
        break;
    }
    return found;
}

int determinate_type(char* token, int *dataType) {
    if (strcmp(".data", token) == 0) {
        dataType = DATA;
    }
    else if (strcmp(".string", token) == 0) {
        dataType = STRING;
    }
    else if (strcmp(".mat", token) == 0) {
        dataType = MAT;
    }
    else if (strcmp(".entry", token) == 0) {
        dataType = ENTRY;
    }
    else if (strcmp(".extern", token) == 0) {
        dataType = EXTERN;
    }
    else {
        dataType = NONE;
        return ERR_ILLEGAL_OPERATION;
    }
    return ERR_OK;
}
 