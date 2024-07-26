#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define KEY_LEN 10
#define CAPACITY 5

typedef struct {
    char** keys;
    int* values;
    size_t length;
    size_t capacity;
} Hashmap;

void HashmapInit(Hashmap** hashmap)
{
    assert( (*hashmap) == NULL ); // prevent double HashmapInit() call

    // Allocate space for struct itself
    Hashmap* new_hashmap = malloc(sizeof(Hashmap));

    // Set default fields
    new_hashmap->capacity = CAPACITY;

    // Allocate memory for keys and values
    new_hashmap->keys = malloc(sizeof(char[CAPACITY][KEY_LEN]));
    new_hashmap->values = malloc(sizeof(int) * CAPACITY);

    (*hashmap) = new_hashmap;
}

int ComputeHash(char* key)
{
    size_t key_len = strnlen(key, KEY_LEN);
    int hash = 0;

    for (size_t i = 0; i < key_len; i++) {
        hash += key[i] * (key_len + i);
    }

    return hash;
}

_Bool HashmapPush(Hashmap** hashmap, char* key, int value)
{
    Hashmap* new_hashmap = (*hashmap);
    const size_t key_len = strlen(key);

    // Make sure key length is not an empty string
    // and is not > KEY_LEN
    if (key_len == 0 || key_len > KEY_LEN) {
        return false;
    }

    if (new_hashmap == NULL) {
        HashmapInit(&new_hashmap);
    } else if (new_hashmap->length >= new_hashmap->capacity) { 
        // If we exceeded, reallocate
        size_t new_capacity = new_hashmap->capacity + 5;

        new_hashmap->keys = realloc(new_hashmap->keys, sizeof(char[new_capacity][KEY_LEN]));
        new_hashmap->values = realloc(new_hashmap->values, sizeof(int) * new_capacity);

        new_hashmap->capacity = new_capacity;
    }

    // Check for duplicate key
    int key_hash = ComputeHash(key);
    for (size_t i = 0; i < new_hashmap->length; i++) {
        int current_key_hash = ComputeHash(new_hashmap->keys[i]);
        
        if (current_key_hash == key_hash) {
            return false;
        }
    }


    // Add key:value pair to the hashmap
    size_t i = new_hashmap->length;
    new_hashmap->keys[i] = key;
    new_hashmap->values[i] = value;
    new_hashmap->length++;

    (*hashmap) = new_hashmap;
    return true;
}

_Bool HashmapSet(Hashmap** hashmap, char* key, int value)
{
    Hashmap* new_hashmap = (*hashmap);
    assert(new_hashmap != NULL);
    
    int key_hash = ComputeHash(key);
    for (size_t i = 0; i < new_hashmap->length; i++) {
        int current_key_hash = ComputeHash(new_hashmap->keys[i]);
        
        if (current_key_hash == key_hash) {
            new_hashmap->values[i] = value;
            (*hashmap) = new_hashmap;
            return true;
        }
    }

    // If key wasnt found in hashmap
    return false;
}

_Bool HashmapGet(Hashmap* hashmap, char* key, int* value)
{
    assert(hashmap != NULL);

    int key_hash = ComputeHash(key);
    for (size_t i = 0; i < hashmap->length; i++) {
        int current_key_hash = ComputeHash(hashmap->keys[i]);
        
        if (current_key_hash == key_hash) {
            (*value) = hashmap->values[i];
            return true;
        }
    }

    return false;
}

void HashmapClear(Hashmap** hashmap)
{
    Hashmap* hashmap_copy = (*hashmap);
    Hashmap* new_hashmap = NULL;

    assert(hashmap_copy != NULL);

    if (hashmap_copy->length == 0) return;

    new_hashmap = malloc(sizeof(Hashmap));
    const size_t current_capacity = hashmap_copy->capacity;
    new_hashmap->keys = malloc(sizeof(char[current_capacity][KEY_LEN]));
    new_hashmap->values = malloc(sizeof(int) * current_capacity);
    new_hashmap->capacity = current_capacity;
    new_hashmap->length = 0;

    free(hashmap_copy);

    (*hashmap) = new_hashmap;
}

void HashmapPrint(Hashmap* hashmap)
{
    assert(hashmap != NULL);

    if (hashmap->length == 0) {
        printf("<hashmap empty>\n");
        return;
    }

    for (size_t i = 0; i < hashmap->length; i++) {
        printf("[\"%s\"] = %i\n", hashmap->keys[i], hashmap->values[i]);
    }
}
