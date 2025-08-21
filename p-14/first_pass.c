#include "first_pass.h"

int first_pass(Map_t* symbol_table, Vector_t* file_line_array, MemImage* dataImage, MemImage* instructionImage, unsigned int* DCF,unsigned int* ICF) {
    unsigned int IC = 0, DC = 0, L;
    char line[MAX_READ], *token, *symbol;
    int error = ERR_OK, lineno = 0, isError = FALSE, dataType = NONE;
    int isSymbol = FALSE;
    size_t line_count, i = 0;
    MapEntry* symbol_entry = NULL;

    error = VectorItemsNum(file_line_array, &line_count);
    set_isError(&error, &isError);
    while (i < line_count && !isError && !(error = VectorGet(file_line_array, i, line, MAX_READ))) {
        token = strtok(line, SPACES);
        if (is_op_check(token)) {
            /*analyze op*/
        }
        else {
            if (token && (is_allowed_name(token) && strlen(token) <= MAX_IDENTIFIER_LEN) && !check_map(symbol_table, token)) {
                error = validate_label(token, symbol);
                if (!error) {
                    isSymbol = TRUE;
                }
                set_isError(&error, &isError);
                token = strtok(NULL, SPACES);
                if (is_data(token)) {
                    error = determinate_type(token, &dataType);
                    set_isError(&error, &isError);
                    if (!isError) { 
                        symbol_entry = entry_init(symbol, 0, DC, NULL, dataType);
                        if (NULL == symbol_entry) {
                            error = ERR_OOM;
                            set_isError(&error, &isError);
                        }
                        if (!isError) {
                            error = analyze_data(token, symbol_entry, &DC, dataImage);
                        }
                    }
                }
                else if (is_pointer(token)) {
                    /* code */
                }
                else if (is_op_check(token)) {
                    /* code */
                }
            }
            else {
                error = ERR_ILLEGAL_TOKEN;
                set_isError(&error, &isError);
            }
        }
        i++;
    }
    set_isError(&error, &isError);

    return isError;
}