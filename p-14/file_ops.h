#ifndef FILE_OPS_H
#define FILE_OPS_H 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE* open_file(const char* file_name, char* file_ext, char mode);

char* read_line(FILE* file, int max_read, char* buffer);

int write_line(FILE* file, char* buffer);

int close_file(FILE* file);

#endif