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
    map->name = (char*) name;
    for (i = 0; i < HASHMAP_SIZE; i++) {
        map->map[i] = NULL;
    }
    return map;
}

MapEntry* map_get(Map_t* map, const char* key) {
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

int map_insert(Map_t* map, MapEntry* entry) {
    int success = FALSE;
    unsigned int index = hash(entry->identifier, strlen(entry->identifier));
    if (NULL == map->map[index]) {
        map->map[index] = entry;
        success = TRUE;
    } 
    else {
        MapEntry* head = map->map[index];
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = entry;
        success = TRUE;
    } 
    return success;
}

int check_map(Map_t* map, const char* key) {
    int success = FALSE;
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
            success = TRUE;
            break;
        }
    }
    return success;
}

MapEntry* map_pop(Map_t* map, const char* key) {
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

void* entry_destroy(MapEntry* entry) {
    int i;
    if (entry == NULL) {
        return NULL;
    }
    entry_destroy(entry->next);
    free(entry->identifier);
    switch (entry->node_data.type)
    {
    case DATA:
        free(entry->node_data.u.arr);
        break;
    case STRING:
        free(entry->node_data.u.str);
        break;
    case MAT:
        for (i=0; i<entry->len;i++){
            free(entry->node_data.u.mat[i]);
        }
        free(entry->node_data.u.mat);
        break;
    case ENTRY:
        free(entry->node_data.u.entryLabel);
        break;
    case EXTERN:
        free(entry->node_data.u.externLabel);
        break;
    case MACRO:
        for (i=0; i<entry->len;i++){
           free(entry->node_data.u.macro[i]); 
        }
        free(entry->node_data.u.macro);
        break;
    case CODE:
        free(entry->node_data.u.code);
        break;
    default:
        break;
    }
    free(entry);
    return NULL;
}

void* map_destroy(Map_t* map) {
    int i;
    if (!map) {
        return NULL;
    }
    for (i = 0; i < HASHMAP_SIZE; i++) {
        map->map[i] = entry_destroy(map->map[i]);
    }
    free(map);
    return NULL;
}

MapEntry* entry_init(const char* label, size_t len, unsigned int start_address, void* dataptr, dataTypes Dtype) {
    MapEntry* entry = (MapEntry*) malloc(sizeof(MapEntry));
    if (entry == NULL) {
        return NULL;
    }
    entry->identifier = (char*) malloc(sizeof(char) * strlen(label)+1);
    strcpy(entry->identifier, label);
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

void print_entry(MapEntry* entry, int index) {
    int i, *j;
    if (!entry) {
        printf("MapMember at map index %d details> NULL.\n", index);
        printf("-----\n");
        return;
    }
    printf("MapMember at map index %d details> identifier : %s, len: %lu, start_addres: %u tag: %d, has-next? %s.\n",index, entry->identifier, entry->len, entry->start_address, entry->node_data.type, (entry->next)? "true" :"false");
    printf("MapMember data>\n");
    switch (entry->node_data.type)
    {
    case DATA:
        for (i=0; i<entry->len;i++){
            printf("%4d,", entry->node_data.u.arr[i]);
        }
        printf("\n");
        break;
    case STRING:
        printf("%s", entry->node_data.u.str);
        break;
    case MAT:
        for (i=0; i<entry->len;i++){
            printf("%-2d: [", i);
            j = entry->node_data.u.mat[i];
            while (j != NULL){
                printf("%3d,", *j++);
            }
            printf("]\n");
        }
        break;
    case ENTRY:
        printf("%s", entry->node_data.u.entryLabel);
        break;
    case EXTERN:
        printf("%s", entry->node_data.u.externLabel);
        break;
    case MACRO:
        for (i=0; i<entry->len;i++){
           printf("%s", entry->node_data.u.macro[i]); 
        }
        break;
    case CODE:
        printf("%s", entry->node_data.u.code);
        break;
    default:
        printf("%s\n", "NULL");
        break;
    }
    printf("-----\n");
    if (entry->next) {
        print_entry(entry->next, index);
    }
}

void print_map(Map_t* map) {
    int i;
    if (!map) {
        printf("\n-------------------------------------------------------\n");
        printf("Map details> Map is not initialized.\n");
        printf("-------------------------------------------------------\n");
        return;
    }
    printf("\n-------------------------------------------------------\n");
    printf("Map details> name : %s.\n", map->name);
    printf("Map data>\n");
    printf("-----\n");
    for (i = 0; i < HASHMAP_SIZE; i++) {
        print_entry(map->map[i], i);
    }
    printf("-------------------------------------------------------\n");
}