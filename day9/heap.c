#include "../day6/common.h"
#include "heap.h"

void initHeap(HEAP *h, size_t element_size, int (*comparator)(void *, int, int)) {
    h->element_size = element_size;
    h->num_allocated = 10;
    h->num_used = 0;
    if (NULL == (h->array = malloc(h->num_allocated * element_size))) {
        perror("initHeap: out of memory");
        exit(-1);
    }
    h->comparator = comparator;
    return;
}


static void swap(HEAP *h, int i, int j)
{
    /* NOTE: One-based indexing is used. h->array[0] is unused and 
     * can be used as the temporary location while swapping
     */
    char *ip = (char *) h->array + i * h->element_size;
    char *jp = (char *) h->array + j * h->element_size;
    char *tp = (char *) h->array;
    memcpy((void *) tp, (void *) ip, h->element_size);
    memcpy((void *) ip, (void *) jp, h->element_size);
    memcpy((void *) jp, (void *) tp, h->element_size);
    return;
}


static void swapUp(HEAP *h, int k)
{
    while (k > 1 && (h->comparator(h->array, k/2, k) < 0)) {
        swap(h, k, k/2);
        k = k/2;
    }
    return;
}

void insert(HEAP *h, void *x)
{
    /* First, make sure there's space for another element */
    if (h->num_used + 1 == h->num_allocated) {
        h->num_allocated *= 2;
        if (NULL == (h->array = realloc(h->array, h->num_allocated * h->element_size))) {
            perror("insert: out of memory");
            exit(-1);
        }
    }
    /* Insert element at end */
    h->num_used++;
    memcpy((char *) h->array + h->num_used * h->element_size,
           x,
           h->element_size);
    /* Restore heap property */
    swapUp(h, h->num_used);
    return;
}


static void swapDown(HEAP *h, int k)
{
    while (2*k <= h->num_used) {
        int j = 2*k;
        /* choose child with larger key */
        if (j < h->num_used && (h->comparator(h->array, j, j+1) < 0))
            j++;
        if (h->comparator(h->array, k, j) >= 0) break;
        swap(h, k, j);
        k = j;
    }
    return;
}

void deleteMax(HEAP *h, void *max)
{
    /* Max is at the root (index 1) */
    memcpy(max, h->array + h->element_size, h->element_size);
    /* Copy last element to root */
    memcpy(h->array + h->element_size,
           h->array + h->num_used * h->element_size,
           h->element_size);
    h->num_used--;
    /* Restore heap property */
    swapDown(h, 1);
    return;
}

void buildheap(HEAP *h)
{
    int k;

    for (k = h->num_used / 2; k >= 1; k--)
        swapDown(h, k);
    return;
}

void heap_sort(void *a, int N, size_t element_size, int (*comparator)(void *, int, int))
{
  HEAP h;

  h.element_size = element_size;
  h.num_allocated = h.num_used = N;
  h.array = a;
  h.comparator = comparator;
  /* Make heap out of array */
  buildheap(&h);
  /* Sort by successive deleteMax */
  while (h.num_used > 1) {
      swap(&h, 1, h.num_used); // move max to end
      h.num_used--;
      swapDown(&h, 1);
  }

  return;
}

int empty(HEAP *heap) {
    return heap->num_used == 0;
}
