#include "util.h"

char* strdup(const char* str) {
    size_t len;
    char* copy;
    len = strlen(str) + 1;
    copy = (char*) malloc(sizeof(char) * len);
    if (NULL == copy) {
        return NULL;
    }
    return (char*) memcpy(copy, str, len);
}