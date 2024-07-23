#include "hashmap.h"

int main()
{
    Hashmap* hashmap = NULL;

    HashmapPush(&hashmap, "l33t", 1337);
    HashmapPush(&hashmap, "lel", 69);
    HashmapPush(&hashmap, "lel", 228); // duplicate!

    HashmapPrint(hashmap);

    HashmapClear(&hashmap);
    HashmapPrint(hashmap); // empty!

    free(hashmap);

    return 0;
}

