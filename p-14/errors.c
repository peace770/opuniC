#include "errors.h"
#include "util.h"

const char* error_description[] = {
    "OK",
    "out of memory",
};

typedef struct err
{
    int code;
    int isErrno;
    int line_in_code;
    int line_in_input;
    const char* msg;
    const char* func;
    const char* in_file;
    const char* code_file;
    const char* line_content;
} Error;

struct ErrorList 
{
    Error** err_list;
    size_t capcity;
    size_t used;
};

ErrorAggregator* create_aggregator(size_t initial_size){
    ErrorAggregator* ea;
    if (0 == initial_size) {
        return NULL;
    }
    ea = (ErrorAggregator*) malloc(sizeof(ErrorAggregator));
    if (!ea) {
        return NULL;
    }
    ea->err_list = (Error**) malloc(sizeof(Error*) * initial_size);
    if (!ea->err_list) {
        free(ea);
        return NULL;
    }
    ea->capcity = initial_size;
    ea->used = 0;

    return ea;
}

void* destroy_error(Error* err) {
    if (!err) {
        return NULL;
    }
    free((void*) err->code_file);
    free((void*) err->in_file);
    free((void*) err->func);
    free((void*) err->line_content);
    free((void*) err->msg);
    free((void*) err);
    return NULL;
}

void* destroy_aggregator(ErrorAggregator* error_aggregator) {
    int i;
    if (error_aggregator){
        i = error_aggregator->used;
        while (i-- > 0) {
            error_aggregator->err_list[i] = destroy_error(error_aggregator->err_list[i]);
        }
        free(error_aggregator->err_list);
        free(error_aggregator);
    }
    return NULL;
}

Error* init_error(int code, int line_in_code, const char* code_file, const char* input_file, const char* func, char* line_content, int line_in_input, int isErrno) {
    Error* err;
    char* file_cpy, * func_cpy, * msg, * content_cpy, * input_file_cpy; 
    err = (Error*) malloc(sizeof(Error));
    if (!err) {
        return NULL;
    }
    if (isErrno) {
        msg = strdup(strerror(code));
    }
    else {
        msg = strdup(error_description[code]);
    }
    if (!msg) {
        free(err);
        return NULL;
    }
    file_cpy = strdup(code_file);
    if (!file_cpy) {
        free(err);
        free(msg);
        return NULL;
    }
    func_cpy = strdup(func);
    if (!func_cpy) {
        free(err);
        free(msg);
        free(file_cpy);
        return NULL;
    }
    content_cpy = strdup(line_content);
    if (!content_cpy) {
        free(err);
        free(msg);
        free(file_cpy);
        free(func_cpy);
        return NULL;
    }
    input_file_cpy = strdup(input_file);
    if (!input_file_cpy) {
        free(err);
        free(msg);
        free(file_cpy);
        free(func_cpy);
        free(content_cpy);
        return NULL;
    }
    err->msg = msg;
    err->code = code;
    err->func = func_cpy;
    err->isErrno = isErrno;
    err->code_file = file_cpy;
    err->in_file = input_file_cpy;
    err->line_content = content_cpy;
    err->line_in_code = line_in_code;
    err->line_in_input = line_in_input;
    return err;
}

int add_error_to_aggregate(ErrorAggregator* error_aggregator, int code, int line_in_code, const char* code_file, const char* input_file, const char* func, char* line_content, int line_in_input, int isErrno) {
    Error* err, ** tmp_list;
    err = init_error(code, line_in_code, code_file, input_file, func, line_content, line_in_input, isErrno);
    if (!err) {
        return ERR_OOM;
    }
    if (error_aggregator->capcity == error_aggregator->used) {
        tmp_list = (Error**) realloc(error_aggregator->err_list, sizeof(Error*) * (error_aggregator->capcity * 2));
        if (NULL == tmp_list) {
            return ERR_OOM;
        }
        error_aggregator->err_list = tmp_list;
        error_aggregator->capcity *= 2;
    }
    *(error_aggregator->err_list + error_aggregator->used) = err;
    ++error_aggregator->used;
    return ERR_OK;
}

void print_errors(ErrorAggregator* error_aggregator) {
    int i;
    Error* err;
    for (i = 0; i < error_aggregator->used; i++) {
        err = error_aggregator->err_list[i];
        if (err->isErrno) {
            fprintf(stdout, "%s:%d:%s(): Error: %s Error Code: %d\n", err->code_file, err->line_in_code, err->func, err->msg, err->code);   
        }
        else {
            fprintf(stdout, "%s:%d: Error: %s Error Code: %d\n", err->in_file, err->line_in_input, err->msg, err->code);
        }
        fprintf(stdout, "%s\n", err->line_content);   
    }
}