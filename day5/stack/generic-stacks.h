#ifndef _GSTACK_
#define _GSTACK_

typedef unsigned long size_t;

typedef struct {
/*
    * element_size: size of the data type in bytes.
    * num_elements: number of elements currently present in the stack.
    * max_elements: capacity of the stack.
*/
    void *elements;
    size_t element_size, num_elements, max_elements;
} STACK;

int init_stack (STACK *s, int element_size, int capacity);
void free_stack(STACK *s);
bool is_empty(const STACK *s);
int push(STACK *s, const void *eptr);
int pop(STACK *s, void *eptr);

#endif // _GSTACK_
