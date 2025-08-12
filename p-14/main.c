#ifndef __ERROR_H__
#include "errors.h"
#endif
#ifndef __HASHMAP_H__
#include "map.h"
#endif
#ifndef __VECTOR_H__
#include "vector.h"
#endif
#ifndef __MEM_IMAGE_H__
#include "mem_image.h"
#endif

#include "macro_unfold.h"
#include "first_pass.h"

int handle_file(char* file_name);
void print_no_args_massage(const char* prog_name);

int main(int argc, char const *argv[]) {
    char* curr_arg;
    if (argc > 1) {
        while (--argc > 0) {
            curr_arg = (char*) *++argv;
            handle_file(curr_arg);
        }
    }
    else {
        print_no_args_massage(argv[0]);
    }
    return 0;
}

int handle_file(char* file_name) {
    int error = ERR_OK, isError = FALSE;
    Vector_t* file_line_array;
    MapEntry* entry = NULL;
    Map_t* symbol_table;
    unsigned int* DCF, *ICF;
    MemImage* dataImage = &data_image;
    MemImage* instructionImage = &instruction_image;
    file_line_array = VectorCreate(15, 5);
    if (NULL == file_line_array) {
        return ERR_OOM;
    }
    symbol_table = map_init("symbols");
    if (NULL == symbol_table) {
        VectorDestroy(file_line_array);
        return ERR_OOM;
    }
    isError = unfold_macro(file_name, file_line_array, symbol_table);
    if (isError) {
        VectorDestroy(file_line_array);
        symbol_table = map_destroy(symbol_table);
        return 1;
    }
    isError = first_pass(symbol_table, file_line_array, dataImage, instructionImage, DCF, ICF); 
    isError = (isError) ? TRUE : second_pass(symbol_table, file_line_array);
    isError = (isError) ? TRUE : save_output_files(symbol_table);
    return 0;
}


void print_no_args_massage(const char* prog_name) {
    printf("%s: missing a file to proccess.\n", prog_name);
    printf("usage: %s <file-name-1>, <file-name-2> ...<file-name-n>\n" , prog_name);
    printf("it is mandatory to pass at least one file name to %s\n", prog_name);
}

void pre_assembly(const char* file_name) { 
    printf("how?\n");
}