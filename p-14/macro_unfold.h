#ifndef MACRO_UNFOLD_H
#define MACRO_UNFOLD_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/*the max size of an accepted line is 80 chars + '\n' + '\0'*/
#define MAX_READ 82
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#define SPACES "\n\r\t \f\v"
#define MAX_IDENTIFIER_LEN 30

int unfold_macro(char* file_name);

#endif