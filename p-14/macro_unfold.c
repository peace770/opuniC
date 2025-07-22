#include "macro_unfold.h"
#include "map.h"
#include "file_ops.h"
#include "vector.h"
#include "assembly_ops.h"

/*the max size of an accepted line is 80 chars + '\n' + '\0'*/
#define MAX_READ 82
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
# define SPACES "\n\r\t \f\v"

int save_file(char* file_name, Vector_t* line_array);
int is_allowed_name(char* macro_name);
int copy_lines(Vector_t * vec, MapEntry* entry, int src);

int unfold_macro(char* file_name) {
    char* line, *line_copy, *token;
    size_t actual_line_len;
    int error = 0, lineno = 0;
    int is_macro = FALSE;
    char buffer[MAX_READ] = {0};
    MapEntry* macro_entry = NULL;
    FILE* original;
    Map_t* macro_table;
    Vector_t* file_line_array, *macro_lines;
    original = open_file(file_name, ".as", "r");
    if (NULL == original) {
        return !error;
    }
    macro_table = map_init("macros");
    if (NULL == macro_table) {
        close_file(original);
        return !error;
    }
    file_line_array = VectorCreate(15, 5);
    if (NULL == file_line_array) {
        close_file(original);
        map_destroy(macro_table);
        return !error;
    }
    macro_lines = VectorCreate(5, 2);
    if (NULL == macro_lines) {
        close_file(original);
        map_destroy(macro_table);
        VectorDestroy(file_line_array);
        return !error;
    }
    while (((line = read_line(original, MAX_READ, buffer)) != NULL) && !error) {
        lineno++;
        if (*line == '\n' || *line == ';') {
            continue;
        } 
        printf("line %3d: %s", lineno, line);
        actual_line_len = strlen(line) + 1;
        line_copy = (char*) malloc(sizeof(char) * actual_line_len);
        if (NULL == line_copy) {
            close_file(original);
            map_destroy(macro_table);
            VectorDestroy(file_line_array);
            return !error;
        }
        strcpy(line_copy, line);
        token = strtok(line, SPACES);
        if (check_map(macro_table, token)) {
            macro_entry = get(macro_table, token);
            copy_lines(file_line_array, macro_entry, 1);
            free(line_copy);
            line_copy = NULL;
            continue;
        }
        else if (token && strcmp(token, "mcro") == 0) {
            token = strtok(NULL, SPACES);
            if (token && is_allowed_name(token) && !check_map(macro_table, token)){
                macro_entry = entry_init(token, 0, 0, NULL, MACRO);
                if (NULL == macro_entry) {
                    error = 1;
                }
                is_macro = TRUE;
            }
            else {
                error = 1;
            }
            token = strtok(NULL, SPACES);
            if (NULL != token) {
                entry_destroy(macro_entry);
                macro_entry = NULL;
                error = 1;
            }
            free(line_copy);
            line_copy = NULL;
        }
        else if (token && strcmp(token, "mcroend") == 0) {
            is_macro = FALSE;
            copy_lines(macro_lines, macro_entry, 0);
            error = insert(macro_table, macro_entry);
            printf("inserting entry %s was a %s\n", macro_entry->identifier, (error) ?"success" : "failure");
            VectorClear(macro_lines);
            token = strtok(NULL, SPACES);
                if (NULL != token) {
                    error = 1;

                }
            free(line_copy);
            line_copy = NULL;
        }
        else if (is_macro && !error){
            error = VectorAdd(macro_lines, line_copy);
        }
        else {
           error = VectorAdd(file_line_array, line_copy);
        }
    }
    if (feof(original) && !error) {
        close_file(original);
        save_file(file_name, file_line_array);
    } 
    else {
        error = 1;
    }
    

    map_destroy(macro_table);
    VectorDestroy(file_line_array);
    VectorDestroy(macro_lines); 

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

int copy_lines(Vector_t * vec, MapEntry* entry, int src) {
    unsigned int i, error = 0;
    size_t line_count;
    char ** tmp;
    if (src) {
        line_count = entry->len;
        for (i = 0; i < line_count; i++) {
            error = VectorAdd(vec, entry->node_data.u.macro[i]);
        }
    }
    else {
        error = VectorItemsNum(vec, &line_count);
        tmp = (char**) malloc(sizeof(char*) * line_count);
        for (i = 0; i < line_count; i++) {
            error = VectorGet(vec, i, tmp[i]);
        }
        entry->node_data.u.macro = tmp;
        entry->len = line_count;
    }
    return error;
}

int save_file(char* file_name, Vector_t* line_array) {
    size_t line_count;
    int i, error = 0;
    char* line = NULL;
    FILE* newf;
    error = VectorItemsNum(line_array, &line_count);
    newf = open_file(file_name, ".am", "w");
    for (i = 0; i < line_count; i++) {
        error = VectorGet(line_array, i, line);
        if (line != NULL) {
            error = fputs(line, newf);
        }
    } 
    close_file(newf);
    return error;
}