#ifndef __UTIL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#ifndef MIN
#define MIN(x,y) (((x)>(y))? (y) : (x))
#endif

#ifndef MAX
#define MAX(x,y) (((x)>(y))? (x) : (y))
#endif


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/*the max size of an accepted line is 80 chars + '\n' + '\0'*/
#ifndef MAX_READ
#define MAX_READ 82
#endif

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#define SPACES "\n\r\t \f\v"
#define MAX_IDENTIFIER_LEN 30

char* strdup(const char* str);

int validate_int(char* input, int* ouput);

int validate_str(char* input, char* output);

int validate_label(char* input, char* ouput);

#define __UTIL_H__
#endif