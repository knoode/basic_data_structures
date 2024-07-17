#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_KEY_LEN 10
#define MIN_CAPACITY 5

// TODO: Maybe make another struct for hashmap pairs (keys, values)
typedef struct {
    char** keys;
    int* values;
    size_t length;
    size_t capacity;
} Hashmap;

// TODO: Maybe implement a type for common hashmap errors
// TODO: Implement HashmapPrint() function

void HashmapInit(Hashmap** hashmap)
{
    // Allocate space for struct itself
    Hashmap* new_hashmap = malloc(sizeof(Hashmap));
    
    // Set default fields
    new_hashmap->length = 0;
    new_hashmap->capacity = MIN_CAPACITY;

    // Allocate memory for keys and values
    new_hashmap->keys = malloc(sizeof(char[MIN_CAPACITY][MAX_KEY_LEN]));
    new_hashmap->values = malloc(sizeof(int) * MIN_CAPACITY);

    (*hashmap) = new_hashmap;
}

int ComputeHash(char* key)
{
    size_t key_len = strnlen(key, MAX_KEY_LEN);
    int hash = 0;

    for (size_t i = 0; i < key_len; i++) {
        hash += key[i] * (key_len + i);
    }

    return hash;
}

_Bool HashmapPush(Hashmap** hashmap, char* key, int value)
{
    Hashmap* new_hashmap = (*hashmap);

    if (new_hashmap == NULL) {
        HashmapInit(&new_hashmap);
    } else if (new_hashmap->length >= new_hashmap->capacity) { 
        // If we exceeded, reallocate
        size_t new_capacity = new_hashmap->capacity + 5;

        new_hashmap->keys = realloc(new_hashmap->keys, sizeof(char[new_capacity][MAX_KEY_LEN]));
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

    // Make sure key length is not > MAX_KEY_LEN
    if (strlen(key) > MAX_KEY_LEN) {
        return false;
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
    Hashmap* new_hashmap = (*hashmap);
    assert(new_hashmap != NULL);

    for (size_t i = 0; i < new_hashmap->length; i++) {
         new_hashmap->keys[i] = "\0";
         new_hashmap->values[i] = 0;
    }

    new_hashmap->length = 0;

    (*hashmap) = new_hashmap;
}

int main()
{
    Hashmap* hashmap = NULL;
    int a, b;

    HashmapPush(&hashmap, "sex", 69);
    HashmapPush(&hashmap, "satan", 666);

    HashmapSet(&hashmap, "sdd", 666666);
    HashmapSet(&hashmap, "satan", 666666);
    
    HashmapGet(hashmap, "sex", &a);
    HashmapGet(hashmap, "satan", &b);

    printf("length = %ld, capacity = %ld\n", hashmap->length, hashmap->capacity);
    printf("sex = %d, satan = %d\n", a, b);

    return 0;
}

