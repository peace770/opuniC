#include "macro_unfold.h"

int save_file(char* file_name, Vector_t* line_array);
int is_allowed_name(char* macro_name);
int copy_lines(Vector_t * vec, MapEntry* entry, int src);
void set_isError(int res, int* flag);

int unfold_macro(char* file_name, Vector_t* file_line_array, Map_t* macro_table) {
    char* line, *line_copy, *token;
    size_t actual_line_len;
    int error = ERR_OK, lineno = 0, isError = FALSE;
    int is_macro = FALSE;
    char buffer[MAX_READ] = {0};
    MapEntry* macro_entry = NULL;
    FILE* original;
    Vector_t *macro_lines;
    original = open_file(file_name, ".as", "r");
    if (NULL == original) {
        return ERR_OOM;
    }
    macro_lines = VectorCreate(5, 2);
    if (NULL == macro_lines) {
        error = close_file(original);
        return ERR_OOM;
    }
    while (((line = read_line(original, MAX_READ, buffer, &error)) != NULL) && !error) {
        lineno++;
        if (*line == '\n' || *line == ';') {
            continue;
        }
        actual_line_len = strlen(line) + 1;
        line_copy = (char*) malloc(sizeof(char) * actual_line_len);
        if (NULL == line_copy) {
            error = close_file(original);
            return ERR_OOM;
        }
        strcpy(line_copy, line);
        printf("line %5d:\t%s", lineno, line_copy);
        token = strtok(line, SPACES);
        if (check_map(macro_table, token)) {
            macro_entry = map_get(macro_table, token);
            error = copy_lines(file_line_array, macro_entry, 1);
            set_isError(error, &isError);
            free(line_copy);
            line_copy = NULL;
            continue;
        }
        else if ((!error && token) && strcmp(token, "mcro") == 0) {
            token = strtok(NULL, SPACES);
            printf("token: %s\n", token);
            if (token && (is_allowed_name(token) && strlen(token) <= MAX_IDENTIFIER_LEN) && !check_map(macro_table, token)){
                macro_entry = entry_init(token, 0, 0, NULL, MACRO);
                if (NULL == macro_entry) {
                    error = ERR_OOM;
                    set_isError(error, &isError);
                }
                is_macro = TRUE;
            }
            else {
                error = ERR_ILLEGAL_TOKEN;
                set_isError(error, &isError);
            }
            token = strtok(NULL, SPACES);
            if (NULL != token) {
                macro_entry = entry_destroy(macro_entry);
                error = ERR_ILLEGAL_TOKEN;
                set_isError(error, &isError);
            }
            free(line_copy);
            line_copy = NULL;
        }
        else if (token && strcmp(token, "mcroend") == 0) {
            is_macro = FALSE;
            error = copy_lines(macro_lines, macro_entry, 0);
            set_isError(error, &isError);
            error = !map_insert(macro_table, macro_entry);
            set_isError(error, &isError);
            if (macro_entry) print_entry(macro_entry, -1);
            printf("inserting entry %s was a %s\n", macro_entry->identifier, (error) ?"success" : "failure");
            error = VectorClear(macro_lines);
            set_isError(error, &isError);
            token = strtok(NULL, SPACES);
            if (NULL != token) {
                error = ERR_ILLEGAL_TOKEN;
            }
            free(line_copy);
            line_copy = NULL;
        }
        else if (is_macro && !error){
            error = VectorAdd(macro_lines, line_copy);
            set_isError(error, &isError);
        }
        else if (error) {
            macro_entry = entry_destroy(macro_entry);
        }
        else {
            error = VectorAdd(file_line_array, line_copy);
            set_isError(error, &isError);
        }
    }

    printf("------------------------\nfile line array\n");
    VectorPrint(file_line_array);
    
    if (feof(original) && !error && !isError) {
        error = close_file(original);
        set_isError(error, &isError);
        error = save_file(file_name, file_line_array);
        set_isError(error, &isError);
    } 
    else {
        error = ferror(original);
        set_isError(error, &isError);
    }
    print_map(macro_table);

    VectorDestroy(macro_lines); 

    return isError;
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
    unsigned int i, error = ERR_OK;
    size_t line_count;
    char ** tmp_lns, *tmp_ln, tmp[MAX_READ];
    if (src) {
        line_count = entry->len;
        for (i = 0; i < line_count; i++) {
            tmp_ln = (char*) malloc(sizeof(char) * strlen(entry->node_data.u.macro[i])+1); 
            if (tmp_ln == NULL) {
                break;
            }
            strcpy(tmp_ln, entry->node_data.u.macro[i]);
            error = VectorAdd(vec, tmp_ln);
        }
    }
    else {
        error = VectorItemsNum(vec, &line_count);
        tmp_lns = (char**) malloc(sizeof(char*) * line_count);
        if (tmp_lns != NULL) {
            for (i = 0; i < line_count; i++) {
                error = VectorGet(vec, i, tmp, MAX_READ);
                if (!error) {
                    tmp_ln = (char*) malloc(sizeof(char) * strlen(tmp)+1); 
                    if (tmp_ln == NULL) {
                        error = ERR_OOM;
                    }
                    strcpy(tmp_ln, tmp);
                }
                *(tmp_lns+i) = tmp_ln;
                tmp_ln = NULL;
            }
            for (i = 0 ; i<line_count; i++){
                printf("tmp_lns[%d]: %s", i, tmp_lns[i]);
            }
            entry->node_data.u.macro = tmp_lns;
            entry->len = line_count;
        }
        else{
            error = ERR_OOM;
        }
    }
    tmp_lns = NULL;
    return error;
}

int save_file(char* file_name, Vector_t* line_array) {
    size_t line_count;
    int i, error = ERR_OK;
    char line[MAX_READ]; 
    FILE* newf;
    error = VectorItemsNum(line_array, &line_count);
    newf = open_file(file_name, ".am", "w");
    for (i = 0; i < line_count; i++) {
        error = VectorGet(line_array, i, line, MAX_READ);
        error = fputs(line, newf);
    } 
    error = close_file(newf);
    return error;
}

void set_isError(int res, int* flag){
    if (!(*flag)) {
        *flag = res;
    }
}
