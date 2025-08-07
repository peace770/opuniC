#ifndef ERROR_H
#define ERROR_H 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*enum for custom error codes*/
typedef enum {
    ERR_OK = 0,
    ERR_OOM,
    ERR_MEM_NOT_INIT,
    ERR_READ_BUFFER_OVERFLOW,
    ERR_ILLEGAL_TOKEN,
    ERR_VECTOR_OVERFLOW,
    ERR_ILLEGAL_OPERATION
} Errors;


typedef struct ErrorList ErrorAggregator;

/*creates a new aggregator, may return NULL*/
ErrorAggregator* create_aggregator(size_t initial_size);

/*frees the ErrorAggregator and all error within, returns NULL*/
void* destroy_aggregator(ErrorAggregator* error_aggregator);

/*adds a new error to the ErrorAggregator.
gets error code, number of line in code where the error occurred, where the error occurred, where the
error occurred, name of function where the error occurred, content of line that caused error, number of
line in input file where the error occurred, and isErrno flag to signal wether en error came from within the
implantation code or the input. set isErrno to 1 for system errors, and 0 for input related errors.
returns: 0 for success and a positive integer for failure.*/
int add_error_to_aggregate(ErrorAggregator* error_aggregator, int code, 
    int line_in_code, const char* code_file, const char* input_file,
    const char* func, char* line_content,int line_in_input, int isErrno);

/*prints every error that was gathered while running the program*/
void print_errors(ErrorAggregator* error_aggregator);

#endif