#include "assembly_ops.h"

int encode_data(char mem_word[], int item, int len);

char* disallowed_names[] =
{
    "mov",
    "cmp",
    "add",
    "sub",
    "lea",
    "clr",
    "not",
    "inc",
    "dec",
    "jmp",
    "bne",
    "jsr",
    "red",
    "prn",
    "rts",
    "stop",
    "data",
    "string",
    "mat",
    "entry",
    "extern",
    "PSW",
    "r0",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7",
    ".data",
    ".string",
    ".mat",
    ".entry",
    ".extern"
};
const unsigned int any_addressing[] = {0,1,2,3};
const unsigned int any_mem_addressing[] = {1,2,3};
const unsigned int no_reg_addressing[] = {1,2};

const op_t assembly_ops[] = 
{
    {0,     "mov",  1, 1, any_addressing,       any_mem_addressing},
    {1,     "cmp",  1, 1, any_addressing,       any_addressing},
    {2,     "add",  1, 1, any_addressing,       any_mem_addressing},
    {3,     "sub",  1, 1, any_addressing,       any_mem_addressing},
    {4,     "lea",  1, 1, no_reg_addressing,    any_mem_addressing},
    {5,     "clr",  0, 1, NULL,                 any_mem_addressing},
    {6,     "not",  0, 1, NULL,                 any_mem_addressing},
    {7,     "inc",  0, 1, NULL,                 any_mem_addressing},
    {8,     "dec",  0, 1, NULL,                 any_mem_addressing},
    {9,     "jmp",  0, 1, NULL,                 any_mem_addressing},
    {10,    "bne",  0, 1, NULL,                 any_mem_addressing},
    {11,    "jsr",  0, 1, NULL,                 any_mem_addressing},
    {12,    "red",  0, 1, NULL,                 any_mem_addressing},
    {13,    "prn",  0, 1, NULL,                 any_addressing},
    {14,    "rts",  0, 0, NULL,                 NULL},
    {15,    "stop", 0, 0, NULL,                 NULL},
};

const op_t* get_op_details(char* name) {
    int i;
    for (i = 0; i < ARRAY_SIZE(assembly_ops); i++) {
        if (strcmp(name, assembly_ops[i].name) == 0) {
            return &assembly_ops[i];
        }
    }
    return NULL;
}

int is_op_check(char* token) {
    int i;
    for (i = 0; i < ARRAY_SIZE(assembly_ops); i++) {
        if (strcmp(token, assembly_ops[i].name) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

int is_allowed_name(char* name) {
    int i;
    for (i = 0; i < ARRAY_SIZE(disallowed_names); i++){
        if (strcmp(name, disallowed_names[i]) == 0){
            return FALSE;
        }
    }
    return TRUE;
}

int is_data(char* name) {
    if (strcmp(".data", name) == 0 || strcmp(".string", name) == 0 || strcmp(".mat", name) == 0) {
        return TRUE;
    }
    return FALSE;
}

int analyze_data(char* type, MapEntry* entry, int* mem_address, MemImage* mem_image) {
    VecInt_t* elems;
    char* token, *raw_data, *str;
    int L = 0, i, j, mem_word_width, *data, item, error = ERR_OK, mat_elem_num = 0, **mat;
    mem_word_width = ARRAY_SIZE(mem_image->mem_image[0]) - 1;
    switch (entry->node_data.type) 
    {
    case DATA:
        elems = VecInt_create();
        if (elems == NULL) {
            return ERR_OOM;
        }
        while (token = strtok(NULL, ",") != NULL && !error) {
            item = 0;
            token = strip_spaces(token);
            error = validate_int(token, &item);
            if (!error) {
                error = VecInt_add(elems, item);
                encode_data(mem_image->mem_image[*mem_address+L], item, mem_word_width);
            }
            L++;
        }
        if (!error) {
            error = VecInt_numItems(elems, entry->len);
            data = (int*) malloc(sizeof(int) * entry->len);
            if (data == NULL) {
                VecInt_destroy(elems);
                return ERR_OOM;
            }
            error = copy_data(elems, data, entry->len);
            entry->node_data.u.arr = data;
            *mem_address += L;
        }
        VecInt_destroy(elems);
        break;
    case STRING:
        token = strtok(NULL, SPACES);
        if (token == NULL) {
            return ERR_ILLEGAL_TOKEN;
        }
        token = strip_spaces(token);
        error = validate_str(token, str);
        if (!error) {
            entry->len = strlen(str) + 1;
            for (i = 0; i <  entry->len; i++) {
                encode_data(mem_image->mem_image[*mem_address+L++], item, mem_word_width);
            }
            entry->node_data.u.str = str;
            *mem_address += L;
        }
        break;
    case MAT:
        elems = VecInt_create();
        if (elems == NULL) {
            return ERR_OOM;
        }
        token = strtok(NULL, SPACES);
        if (token[0] != '[') {
            VecInt_destroy(elems);
            return ERR_ILLEGAL_TOKEN;
        }
        for (i = 0; i < strlen(token); i++) {
            if (isdigit(token[i])) {
                item = token[i] - '0';
                error = VecInt_add(elems, item);
                mat_elem_num += item;
            }
            if (isalpha(token[i]) || ispunct(token[i])) {
                VecInt_destroy(elems);
                return ERR_ILLEGAL_TOKEN;
            }
        }
        error = VecInt_get(elems, 0, item);
        if (error) {
            VecInt_destroy(elems);
            return ERR_ILLEGAL_TOKEN;

        }
        mat = (int**) malloc (sizeof(int*) * (item + 1));
        if (NULL == mat) {
            VecInt_destroy(elems);
            return ERR_OOM;
        }
        mat[item] = NULL;
        error = VecInt_get(elems, 1, item);
        if (error) {
            VecInt_destroy(elems);
            return ERR_ILLEGAL_TOKEN;

        }
        i = 0;
        while (*(mat + i) != NULL) {
            data = (int*) malloc(sizeof(int) * item + 1);
            if (NULL == data) {
                VecInt_destroy(elems);
                while (*(mat + i) != NULL) {
                    free(*(mat + i));
                }
                free(mat);
                return ERR_OOM;
            }
            data[item] = NULL;
            *(mat + i) = data;
            i++;
        }
        error = VecInt_clear(elems);
        raw_data = strtok(NULL, "");
        if (NULL == raw_data) {
            while (*(mat + i) != NULL) {
                while (*((mat + i) + j) != NULL) {
                    *((mat + i) + j) = 0;
                    encode_data(mem_image->mem_image[*mem_address+L], item, mem_word_width);
                    L++;
                    j++; 
                }
                i++;
            }
            entry->len = mat_elem_num;
            entry->node_data.u.mat = mat;
            *mem_address += L;
        }
        else {
            token = strtok(raw_data, ",");
            while (*(mat + i) != NULL) {
                while (*((mat + i) + j) != NULL) {
                    do {
                        item = 0;
                        token = strip_spaces(token);
                        error = validate_int(token, &item);
                        if (!error) {
                            *((mat + i) + j) = item;
                            error = VecInt_add(elems, item);
                            encode_data(mem_image->mem_image[*mem_address+L], item, mem_word_width);
                        }
                        L++;
                    } while (token = strtok(NULL, ",") != NULL && !error);
                    j++;
                }
                i++;
            }
            error = VecInt_numItems(elems, item);
            if (mat_elem_num != item){
                VecInt_destroy(elems);
                return ERR_ILLEGAL_TOKEN;
            }
            entry->len = mat_elem_num;
            entry->node_data.u.mat = mat;
            *mem_address += L;

        }
        VecInt_destroy(elems);
        break;
    default:
        break;
    }

    return error;
}

int copy_data(VecInt_t* vec, int* data, size_t len) {
    int i, error;
    for (i = 0; i < len; i++) {
        error = VecInt_get(vec, i, data+i);
    }
    return error;
}

int encode_data(char mem_word[], int item, int len) {
    int s_pos = 10, i;
    unsigned int x = 0;
    for (i = 0; i < len; i++) {
        x = getbits((unsigned int) item, s_pos, 2);
        if (x & 0){
            mem_word[i] = 'a';
        }
        else if (x & 1){
            mem_word[i] = 'b';
        }
        else if (x & 2){
            mem_word[i] = 'c';
        }
        else if (x & 3){
            mem_word[i] = 'd';
        }
        s_pos -= 2;
    }
    mem_word[len] = '\0';
    return 0;
}