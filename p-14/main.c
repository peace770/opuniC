#include "map.h"
#include "tagged_union.h"

void pre_assembly(const char* file_name);

void print_no_args_massage(char* prog_name);

int main(int argc, char const *argv[]) {
    char* curr_arg;
    if (argc > 1) {
        while (--argc > 0) {
            curr_arg = *++argv;
            pre_assembly(curr_arg);
        }
    }
    else {
        print_no_args_massage(argv[0]);
    }
    return 0;
}



void print_no_args_massage(char* prog_name) {
    printf("%s: missing a file to proccess.\n", prog_name);
    printf("usage: %s <file-name-1>, <file-name-2> ...<file-name-n>\n" , prog_name);
    printf("it is mandatory to pass at least one file name to %s\n", prog_name);
}