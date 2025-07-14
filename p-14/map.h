#ifndef HASHMAP_H
#define HAHSMAP_H 1
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#if !defined(TRUE) && !defined(FALSE)
#define TRUE 1
#define FALSE 0
#endif

#define HASHMAP_SIZE 128
#define HASH_PRIME 1990661

typedef struct Map
{
    MapEntry* map[HASHMAP_SIZE];
    char* name;
} Map_t;

typedef struct MapMember
{
    MapEntry* next;
    char* identifier;
    Tunion node_data;
    unsigned int start_address;
    size_t len;
} MapEntry;

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
MapEntry* get(Map_t* map, const char* key);

/*insert an entry to a map, returns 1 for success and 0 for failure*/
int insert(Map_t* map, MapEntry* entry);

/*check if key is in the map, returns 1 for success and 0 for failure*/
int check_map(Map_t* map, const char* key);

/*remove an entry from map, returns the entry, NULL on failure*/
MapEntry* pop(Map_t* map, const char* key);

/*frees the map and all entries within it*/
void map_destroy(Map_t* map);

/*frees an entry or an entire chain of entries until entry->next == NULL*/
void entry_destroy(MapEntry* entry);

#endif