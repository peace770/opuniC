#include "macro_unfold.h"
#include "map.h"
#include "file_ops.h"
#include "tagged_union.h"
#include "vector.h"
#include "assembly_ops.h"

/*the max size of an accepted line is 80 chars + '\n' + '\0'*/
#define MAX_READ 82
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))

int save_file(char* file_name);
int is_allowed_name(char* macro_name);

int unfold_macro(char* file_name) {
    char* line, *line_copy;
    size_t actual_line_len;
    int error = 0;
    int is_macro = 0;
    char buffer[MAX_READ] = {0};
    FILE* original = open_file(file_name, ".as", 'r');
    if (NULL == original) {
        return !error;
    }
    Map_t* macro_table = map_init("macros");
    if (NULL == macro_table) {
        close_file(original);
        return !error;
    }
    Vector_t* file_line_array = VectorCreate(15, 5);
    if (NULL == file_line_array) {
        close_file(original);
        map_destroy(macro_table);
        return !error;
    }
    while ((line = read_line(original, MAX_READ, buffer)) != NULL) {
        if (line == '\n' || line == ';') {
            continue;
        } 
        actual_line_len = strlen(line) + 1;
        line_copy = (char*) malloc(sizeof(char) * actual_line_len);
        if (NULL == line_copy) {
            close_file(original);
            map_destroy(macro_table);
            VectorDestroy(file_line_array);
            return !error;
        }
        strcpy(line_copy, line);
        

    }
    if (feof(original)) {
        close_file(original);
        save_file(file_name);
    } 
    else {
        error = 1;
    }
    



    map_destroy(macro_table);
    VectorDestroy(file_line_array);
    return error;
}

int is_allowed_name(char* macro_name) {
    int i;
    for (i = 0; i < ARRAY_SIZE(disallowed_names); i++){
        if (strcmp(macro_name, disallowed_names[i]) == 0){
            return FALSE;
        }
    }
    return TRUE;
}