#include "file_ops.h"

FILE* open_file(const char* file_name, char* file_ext, char mode) {
    FILE* fp;
    int len;
    char* full_file_name;
    len = strlen(file_name) + strlen(file_ext) + 1;
    full_file_name = (char*) malloc(sizeof(char) * len);
    if (NULL == full_file_name) {
        return NULL;
    }
    full_file_name = strcat(strcat(full_file_name, file_name), file_ext);
    fp = fopen(full_file_name, &mode);
    free(full_file_name);
    return fp;
}

char* read_line(FILE* file, int max_read, char* buffer) {
    
}

int write_line(FILE* file, char* buffer) {

}

int close_file(FILE* file) {
    return fclose(file);
}