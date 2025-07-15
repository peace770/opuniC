#include "macro_unfold.h"
#include "map.h"
#include "file_ops.h"




int unfold_macro(char* file_name) {
    int error = 0;
    int is_macro = 0;
    FILE* original = open_file(file_name, ".as", 'r');
    if (NULL == original) {
        return !error;
    }
    Map_t* macro_table = map_init("macros");
    
}
