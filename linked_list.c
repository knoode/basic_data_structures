#include "linked_list.h"

int main()
{
    Node* node = NULL;

    // You can add some nodes here:
    NodeAdd(&node, 'a');
    NodeAdd(&node, 'b');
    NodeAdd(&node, 'c');

    NodePrint(&node);

    return 0;
}
