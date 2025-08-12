#ifndef __FIRST_PASS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#ifndef __VECTOR_H__
#include "vector.h"
#endif

#ifndef __HASHMAP_H__
#include "map.h"
#endif

#ifndef __UTIL_H__
#include "util.h"
#endif

#ifndef __ERROR_H__
#include "errors.h"
#endif

#ifndef __ASSEMBLY_OPS_H__
#include "assembly_ops.h"
#endif

int first_pass(Map_t* symbol_table, Vector_t* file_line_array);

#define __FIRST_PASS_H__
#endif