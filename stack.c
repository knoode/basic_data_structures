#include "stack.h"

int main()
{
    Stack* stack = NULL;

//    StackInit(&stack);
    Push(&stack, 123);
    Push(&stack, 456);
    Push(&stack, 789);

    Pop(&stack); // 789
    Pop(&stack); // 456
    StackPrint(stack);  // 123
    StackClear(&stack);
    StackPrint(stack);  // <stack empty> 

    return 0;
}
