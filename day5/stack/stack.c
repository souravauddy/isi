#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "generic-stacks.h"

STACK * allocate_stack() {
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

inline bool is_empty(const STACK *stack) {
    return stack->num_elements == 0;
}

inline void free_stack(STACK *stack) {
    free(stack->elements);
    free(stack);
}

int push(STACK *stack, const void *element_pointer) {
    if (stack->num_elements == stack->max_elements)
        return 0; // there is no space left in the stack to push a new element.

    memcpy((char *) stack->elements + stack->num_elements * stack->element_size, element_pointer, stack->element_size);
    stack->num_elements++;
    return 1; // push successful.
}

int pop(STACK *stack, void *element_pointer) {
    if (stack->num_elements == 0)
        return 0; // there is not element left to pop.

    stack->num_elements--;
    memcpy(element_pointer, (char *) stack->elements + stack->num_elements * stack->element_size, stack->element_size);
    return 1; // pop successful.
}

const int MAX_SIZE = (int) 5;

int main(const int argc, const char **argv) {
    STACK *stack = allocate_stack();
    init_stack(stack, sizeof(int), MAX_SIZE);

    int *elements = (int *) malloc(MAX_SIZE * sizeof(int));

    for (int i = 0; i < MAX_SIZE; i++)
        elements[i] = i + 1;

    for (int i = 0; i < MAX_SIZE; i++)
        push(stack, elements + i);

    int *element = (int *) malloc(sizeof(int));

    for (int i = 0; i < MAX_SIZE; i++) {
        pop(stack, element);
        printf("%d ", *((int *) element));
    }

    puts("");
    free_stack(stack);
}
