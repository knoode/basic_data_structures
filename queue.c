#include <stdio.h>
#include <time.h>

#include "queue.h"

void stress_test(Queue** queue)
{
    srand(time(NULL));

    for (int i = 0; i < 100; i++) {
        int rand_item = (rand() % 100) + 1;
        Enqueue(queue, rand_item); 
    }
}

int main()
{
    Queue* queue = NULL;

    stress_test(&queue);
    QueuePrint(queue);

    printf("length = %ld, capacity = %ld\n", queue->length, queue->capacity);

    free(queue);
    return 0;
}
