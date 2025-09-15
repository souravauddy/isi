#include "heap.h"

int init_heap(HEAP *heap, size_t element_size, size_t capacity, int (*comparator)(void *, int, int)) {
    heap->array = (void *) malloc(capacity * element_size);

    if (heap->array == NULL)
        return -1;

    heap->element_size = element_size;
    heap->num_allocated = capacity;
    heap->num_used = 0;
    heap->comparator = comparator;

    return 1;
}

void increase_capacity(HEAP *heap) {
    heap->array = realloc(heap->array, 2 * heap->num_allocated);
    heap->num_allocated = 2 * heap->num_allocated;
}

void insert(HEAP *heap, void *element) {
    if (heap->num_used == heap->num_allocated)
        increase_capacity(heap);

    memcpy(heap + heap->element_size * heap->num_used, element, heap->element_size);
    heap->num_used++;
}
