#include "map.h"
#include "tagged_union.h"

static unsigned int hash(const char* key, size_t length) {
    int i = 0;
    unsigned int hash = HASH_PRIME;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash % HASHMAP_SIZE;
}

Map_t* map_init(const char* name) {
    int i;
    Map_t *map = (Map_t*) malloc(sizeof(Map_t));
    if (map == NULL) {
        return NULL;
    }
    map -> name = name;
    for (i = 0; i < HASHMAP_SIZE; i++) {
        map->map[i] = NULL;
    }
    return map;
}

MapEntry* get(Map_t* map, const char* key) {
    unsigned int index = hash(key, strlen(key));
    MapEntry* entry = map->map[index];
    if (NULL == entry) {
        return NULL;
    }
    while (entry != NULL) {
        if (strcmp(entry->identifier, key) != 0) {
            entry = entry->next;
        } 
        else {
            return entry;
        }
    }
    return NULL;
}

int insert(Map_t* map, MapEntry* entry) {
    int success = 0;
    unsigned int index = hash(entry->identifier, strlen(entry->identifier));
    if (NULL == map->map[index]) {
        map->map[index] = entry;
        success = 1;
    } 
    else {
        MapEntry* head = map->map[index];
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = entry;
        success = 1;
    } 
    return success;
}

int check_map(Map_t* map, const char* key) {
    int success = 0;
    unsigned int index = hash(key, strlen(key));
    MapEntry* entry = map->map[index];
    if (NULL == entry) {
        return success;
    }
    while (entry != NULL) {
        if (strcmp(entry->identifier, key) != 0) {
            entry = entry->next;
        } 
        else {
            success = 1;
            break;
        }
    }
    return success;
}

MapEntry* pop(Map_t* map, const char* key) {
    unsigned int index = hash(key, strlen(key));
    MapEntry* prev = NULL;
    MapEntry* entry = map->map[index];
    if (NULL == entry) {
        return NULL;
    }
    while (entry != NULL) {
        if (strcmp(entry->identifier, key) != 0) {
            prev = entry;
            entry = entry->next;
        } 
        else {
            if (prev == NULL) {
                map->map[index] = entry->next;
            }
            else
            prev->next = entry->next;
            entry->next = NULL;
            return entry;
        }
    }
    return NULL;
}

void entry_destroy(MapEntry* entry) {
    if (entry == NULL) {
        return;
    }
    entry_destroy(entry->next);
    free(entry);
    return;
}

void map_destroy(Map_t* map) {
    int i;
    for (i = 0; i < HASHMAP_SIZE; i++) {
        entry_destroy(map->map[i]);
    }
    free(map);
    return NULL;
}

MapEntry* entry_init(const char* label, size_t len, unsigned int start_address, void* dataptr, dataTypes Dtype) {
    MapEntry* entry = (MapEntry*) malloc(sizeof(MapEntry));
    if (entry == NULL) {
        return NULL;
    }
    entry->identifier = label;
    entry->len = len;
    entry->start_address = start_address;
    entry->next = NULL;
    fill_union(&entry->node_data, Dtype, dataptr);
    return entry;
}

MapEntry* empty_entry_init() {
    MapEntry* entry = (MapEntry*) malloc(sizeof(MapEntry));
    if (entry == NULL) {
        return NULL;
    }
    entry->identifier = "";
    entry->len = 0;
    entry->start_address = 0;
    entry->next = NULL;
    entry->node_data.type = NONE;
    entry->node_data.u.null = NULL;
    return entry;
}