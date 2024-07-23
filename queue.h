#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define CAPACITY 5

// FIXME: Length and Capacity fields can be modified by anyone
// so maybe we should implement a function for controling these fields
typedef struct {
    int* items;
    size_t length;
    size_t capacity;
} Queue;

void QueueInit(Queue** queue)
{
    assert( (*queue) == NULL ); // assert if queue is already initialized

    Queue* new_queue = malloc(sizeof(Queue));

    new_queue->items = malloc(sizeof(int) * CAPACITY);
    new_queue->length = 0;
    new_queue->capacity = CAPACITY;

    (*queue) = new_queue;
}

void Enqueue(Queue** queue, int item)
{
    Queue* queue_copy = (*queue);

    if (queue_copy == NULL) {
        QueueInit(&queue_copy);
    } else if (queue_copy->length >= queue_copy->capacity) {
        // If we exceeded, reallocate
        size_t new_capacity = queue_copy->capacity + 5;

        queue_copy->items = realloc(queue_copy->items, new_capacity * sizeof(int)); 
        queue_copy->capacity = new_capacity;
    }

    size_t next_item = queue_copy->length;
    queue_copy->items[next_item] = item;
    queue_copy->length++;

    (*queue) = queue_copy;
}

void Dequeue(Queue** queue)
{
    Queue* queue_copy = (*queue);

    assert(queue_copy != NULL);

    // Check if queue is empty
    if (queue_copy->length == 0) return;

    // FIXME: Maybe find a better way to alloc a new Queue in this case
    Queue* new_queue = malloc(sizeof(Queue));

    new_queue->items = malloc(queue_copy->capacity * sizeof(int));
    new_queue->length = 0;
    new_queue->capacity = queue_copy->capacity;

    // Copy elements from old queue to new, except for 0 index element
    for (size_t i = 1; i < queue_copy->length; i++) {
        Enqueue(&new_queue, queue_copy->items[i]);
    }

    new_queue->length = queue_copy->length - 1;

    (*queue) = new_queue;
}

void QueueClear(Queue** queue) 
{
    Queue* queue_copy = (*queue);
    Queue* new_queue = NULL;

    assert(queue_copy != NULL);

    if (queue_copy->length == 0) return;

    // Keep the same capacity, but allocate a new queue with length = 0
    new_queue = malloc(sizeof(Queue));
    new_queue->items = malloc(sizeof(int) * queue_copy->capacity);
    new_queue->capacity = queue_copy->capacity;
    new_queue->length = 0;

    free(queue_copy);

    (*queue) = new_queue;
}

void QueuePrint(Queue* queue)
{
    assert(queue != NULL);

    if (queue->length == 0) {
        printf("<queue empty>\n");
        return;
    }

    for (size_t i = 0; i < queue->length; i++) {
        printf("[%ld] = %i\n", i, queue->items[i]);
    }
}
