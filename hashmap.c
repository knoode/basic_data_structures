#include "hashmap.h"

int main()
{
    Hashmap* hashmap = NULL;

    HashmapInit(&hashmap);

    HashmapPush(&hashmap, "l33t", 1337);
    HashmapPush(&hashmap, "lel", 69);
    HashmapPush(&hashmap, "sdsdlksjdvklsdvjlksvdjsdvlksdjdv", 228); // duplicate!
    HashmapPush(&hashmap, "", 228); // duplicate!
    
    printf("%ld\n", hashmap->capacity);

    HashmapPrint(hashmap);
    HashmapClear(&hashmap);
    HashmapPrint(hashmap);

    free(hashmap);

    return 0;
}

