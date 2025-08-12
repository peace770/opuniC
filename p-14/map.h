#ifndef __HASHMAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "tagged_union.h"

#ifndef __UTIL_H__
#include "util.h"
#endif

#define HASHMAP_SIZE 128
#define HASH_PRIME 1990661

#ifndef MAP_ENTRY
typedef struct MapMember MapEntry;

struct MapMember
{
    MapEntry* next;
    char* identifier;
    Tunion node_data;
    unsigned int start_address;
    size_t len;
};
#define MAP_ENTRY 1
#endif

#ifndef MAP_T
typedef struct Map
{
    MapEntry* map[HASHMAP_SIZE];
    char* name;
} Map_t;
#define MAP_T 1
#endif

/*initialize a map, returns a pointer to the map, NULL on failure*/
Map_t* map_init(const char* name);

/*create an entry for the map. gets a label for the element, length, 
the intended start address of the element, 
a void* pointer to the data of the element,
and the type as declred in dataTypes enum.
returns a pointer to the entry, NULL on fail.*/
MapEntry* entry_init(const char* label, size_t len, 
    unsigned int start_address, void* dataptr, dataTypes Dtype);

/*create an empty entry for the map. returns a pointer to the entry, NULL on fail.*/
MapEntry* empty_entry_init(); 

/*retrieve an entry from map, NULL for failure*/
MapEntry* map_get(Map_t* map, const char* key);

/*insert an entry to a map, returns 1 for success and 0 for failure*/
int map_insert(Map_t* map, MapEntry* entry);

/*check if key is in the map, returns 1 for success and 0 for failure*/
int check_map(Map_t* map, const char* key);

/*remove an entry from map, returns the entry, NULL on failure*/
MapEntry* map_pop(Map_t* map, const char* key);

/*frees the map and all entries within it*/
void* map_destroy(Map_t* map);

/*frees an entry or an entire chain of entries until entry->next == NULL*/
void* entry_destroy(MapEntry* entry);

void print_entry(MapEntry* entry, int i);

void print_map(Map_t* map);

#define __HAHSMAP_H__
#endif