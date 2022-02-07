#include "kernel.h"

void initStack(k_stack_t *stack, stack_data_t *buffer, uint32_t size)
{
    stack->base = stack->next = buffer;
    stack->top = stack->base + size;
    stack->stack_size = size;
}

void pushStack(k_stack_t *stack, stack_data_t data)
{
    if (stack->next >= stack->top) {
        stack->next = stack->top;
        printf("base = %ld, top = %ld, next = %ld\n", *(stack->base), *stack->top, *stack->next);
        printf("Error: stack is full\n");
        return;
    }

    *(stack->next) = data;
    stack->next ++;
}

void popStack(k_stack_t *stack, stack_data_t *data)
{
    if (stack->next <= stack->base) {
        stack->next = stack->base;
        printf("Error: invalid stack\n");
        return;
    }

    stack->next--; 
    *data = *(stack->next);
}

void readStack(k_stack_t *stack)
{
    stack_data_t *pbase = stack->base;

    while (pbase != stack->top) {
        printf("stack content %ld\n", *pbase);
        pbase++;
    }
}
