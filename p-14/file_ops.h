#ifndef __FILE_OPS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*tries to open file as constructed form file_name + file_ext (e.g "hello" + ".txt") in the mode passed in mode.
allocates memory for the concatenated file_name + file_ext, and frees it before returning.  
returns NULL if failed the allocation or finding the file, FILE pointer if success.*/
FILE* open_file(const char* file_name, char* file_ext, char* mode);

/*reads a line from file using fgets(), buffer must be at least 1 byte longer then max_read to avoid memory corruption.
returns a pointer to the start of the line, or NULL on failure to read from file and EOF.
its advisable to check feof() in such cases.*/
char* read_line(FILE* file, int max_read, char* buffer, int* err);

/*wraps fputs(), returns a non-negative number on success, EOF on error.*/
int write_line(FILE* file, char* buffer);

/*wraps fclose() returns 0 on success, EOF on fail. */
int close_file(FILE* file);

#define __FILE_OPS_H__ 
#endif