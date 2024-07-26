#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define CAPACITY 5

typedef struct {
    int* items;
    size_t length;
    size_t capacity;
} Stack;

void StackInit(Stack** stack)
{
    assert( (*stack) == NULL ); // assert if stack is already initialized

    Stack* new_stack = malloc(sizeof(Stack));

    new_stack->items = malloc(sizeof(int) * CAPACITY);
    new_stack->length = 0;
    new_stack->capacity = CAPACITY;

    (*stack) = new_stack;
}

void Push(Stack** stack, int item)
{
    Stack* stack_copy = (*stack);

    if (stack_copy == NULL) {
        StackInit(&stack_copy);
    } else if (stack_copy->length >= stack_copy->capacity) {
        // If we exceeded, reallocate
        size_t new_capacity = stack_copy->capacity + 5;

        stack_copy->items = realloc(stack_copy->items, new_capacity * sizeof(int)); 
        stack_copy->capacity = new_capacity;
    }

    size_t next_item = stack_copy->length;
    stack_copy->items[next_item] = item;
    stack_copy->length++;

    (*stack) = stack_copy;
}

void Pop(Stack** stack)
{
    Stack* stack_copy = (*stack);
    assert(stack_copy != NULL);
    
    // If all elements were already POPed
    if (stack_copy->length == 0) return;

    Stack* new_stack = malloc(sizeof(Stack));
    const size_t current_capacity = stack_copy->capacity;
    new_stack->items = malloc(sizeof(int) * current_capacity);
    new_stack->capacity = current_capacity;
    new_stack->length = 0;

    // Copy all elements from stack_copy to new_stack, except for last one
    for (size_t i = 0; i <= stack_copy->length; i++) {
        Push(&new_stack, stack_copy->items[i]);
    }
    
    new_stack->length = stack_copy->length - 1;

    free(stack_copy);
    (*stack) = new_stack;
}

void StackPrint(Stack* stack)
{
    assert(stack != NULL);

    if (stack->length == 0) {
        printf("<stack empty>\n");
        return;
    }

    for (size_t i = 0; i < stack->length; i++) {
        printf("[%ld] = %i\n", i, stack->items[i]);
    }
}

void StackClear(Stack** stack) 
{
    Stack* stack_copy = (*stack);
    Stack* new_stack = NULL;

    assert(stack_copy != NULL);

    if (stack_copy->length == 0) return;

    // Keep the same capacity, but allocate a new stack with length = 0
    new_stack = malloc(sizeof(Stack));
    const size_t current_capacity = stack_copy->capacity;
    new_stack->items = malloc(sizeof(int) * current_capacity);
    new_stack->capacity = current_capacity;
    new_stack->length = 0;

    free(stack_copy);

    (*stack) = new_stack;
}
