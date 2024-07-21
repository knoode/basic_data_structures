#include <stdio.h>
#include "hashmap.h"

int main()
{
    Hashmap* hashmap = NULL;

    HashmapPush(&hashmap, "sex", 69);
    HashmapPush(&hashmap, "satan", 666);
    HashmapPush(&hashmap, "heaven", 333);

    HashmapSet(&hashmap, "sdd", 666666); // <- error!
    HashmapSet(&hashmap, "satan", 666666);
    
    HashmapPrint(hashmap);

    HashmapClear(&hashmap);

    HashmapPrint(hashmap);

    return 0;
}

