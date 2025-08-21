#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "generic-stacks.h"

STACK * create_stack() {
    return (STACK *) malloc(sizeof(STACK));
}

int init_stack(STACK *stack, int element_size, int capacity) {
    stack->num_elements = 0;
    stack->max_elements = capacity;
    stack->element_size = element_size;
    stack->elements = malloc(element_size * capacity);

    if (stack->elements == NULL)
        return 0; // memory allocation failed.

    return 1; // memory allocation successful.
}

bool is_empty(const STACK *stack) {
    return stack->num_elements == 0;
}

void free_stack(STACK *stack) {
    free(stack->elements);
    free(stack);
}

int push(STACK *stack, const void *element_pointer) {
    if (stack->num_elements == stack->max_elements)
        return 0; // there is no space left in the stack to push a new element.

    memcpy(stack->elements + stack->num_elements * stack->element_size, element_pointer, stack->element_size);
    stack->num_elements++;
    return 1; // push successful.
}

int pop(STACK *stack, void *element_pointer) {
    if (stack->num_elements == 0)
        return 0; // there is not element left to pop.

    stack->num_elements--;
    memcpy(element_pointer, stack->elements + stack->num_elements * stack->element_size, stack->element_size);
    return 1; // pop successful.
}

int main(const int argc, const char **argv) {
    
}
