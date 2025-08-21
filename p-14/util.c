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

int validate_int(char* input, int* ouput) {
    int i;
    if (input[0] != '+' && input[0] != '-' && (input[0] < '0' || input[0] > '9')) {
        *ouput = 0;
        return 1;
    }
    for (i = 1; i < strlen(input); i++) {
        if (input[i] < '0' || input[i] > '9') {
            ouput = 0;
            return 1;
        }
    }
    *ouput = (int) strtol(input, NULL, 10);
    if (*ouput < -512 || *ouput > 511) {
        *ouput = 0;
        return 2;
        /* overflow/underflow */
    }
    return 0;
}

int validate_str(char* input, char* ouput) {
    int i , len;
    len = strlen(input);
    if (input[0] != '"' || input[len-1] != '"') {
        ouput = NULL;
        return 1;
    }
    for (i = 1; i < len-1; i++){
        if (!isprint((unsigned char) input[i])) {
            ouput = NULL;
            return 1;
        }
    }
    *(input+(len-1)) ='\0';
    ouput = strdup(input+1);
    return 0;
}

int validate_label(char* input, char* ouput) {
    int i , len;
    len = strlen(input);
    if (!isalpha((unsigned char) input[0]) || (input[len-1] != ':' && !isspace(input[len-2]))) {
        ouput = NULL;
        return 1;
    }
    for (i = 1; i < len-1; i++){
        if (!isalnum((unsigned char) input[i])) {
            ouput = NULL;
            return 1;
        }
    }
    *(input+(len-1)) ='\0';
    ouput = strdup(input+1);
    return 0;
}

void set_isError(int *res, int* flag) {
    if (!(*flag)) {
        *flag = *res;
    }
    *res = 0;
}

char* strip_spaces(char* str) {
    int i, j;
    for (i = 0; i < strlen(str) && isspace(str[i]); i++);
    str = str + i;
    for (j = strlen(str)-1; j >= 0 && isspace(str[j]); i--);
    str[j+1] = '\0';
}

unsigned int getbits(unsigned data, int pos, int width) {
    return (data >> (pos+1-width)  & ~(~0 << width));
}