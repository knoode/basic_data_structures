#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char chr;
    struct Node* next;
} Node;

void NodeAdd(Node** head, char chr)
{
    Node* new_node = malloc(sizeof(Node));

    new_node->chr = chr;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
}

void NodePrint(Node** head)
{
    Node* current = *head;
    while (current != NULL) {
        printf("'%c' [%p] -> ", current->chr, current);
        current = current->next;
    }

    printf("NULL\n");
}
