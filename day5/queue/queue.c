#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

struct QUEUE {
    void *elements;
    size_t element_size, num_elements, capacity, front, rear;
};

typedef struct QUEUE QUEUE;

QUEUE * allocate_queue() {
    return (QUEUE *) malloc(sizeof(QUEUE));
}

static inline void free_queue(QUEUE *queue) {
    free(queue->elements);
    free(queue);
}

static inline int mod(int value, const int MOD) {
    return value >= MOD ? value - MOD : value;
}

int init_queue(QUEUE *queue, int element_size, int capacity) {
    queue->elements = malloc((capacity) * element_size);

    if (queue->elements == NULL)
        return 0;

    queue->element_size = element_size;
    queue->capacity = capacity;
    queue->num_elements = 0;
    queue->front = queue->rear = -1;

    return 1;
}

int enqueue(QUEUE *queue, void *element) {
    if (queue->num_elements == queue->capacity)
        return 0; // queue is full.

    queue->front = mod(queue->front + 1, queue->capacity);
    memcpy((char *) queue->elements + queue->front * queue->element_size, element, queue->element_size);
    queue->num_elements++;

    return 1;
}

int dequeue(QUEUE *queue, void *element) {
    if (queue->num_elements == 0)
        return 0; // queue has no elements to delete

    queue->rear = mod(queue->rear + 1, queue->capacity);
    memcpy(element, (char *) queue->elements + queue->rear * queue->element_size, queue->element_size);
    queue->num_elements--;

    return 1; // dequeue is successful
}

int front(QUEUE *queue, void *element) {
    if (queue->num_elements == 0)
        return 0;

    memcpy(element, (char *) queue->elements + mod(queue->rear + 1, queue->capacity) * queue->element_size, queue->element_size);

    return 1;
}

const int MAX_SIZE = (int) 5;

int main() {
    QUEUE *queue = allocate_queue();
    init_queue(queue, sizeof(int), MAX_SIZE);

    int *elements = (int *) malloc(MAX_SIZE * sizeof(int));

    for (int i = 0; i < MAX_SIZE; i++)
        elements[i] = i + 1;

    for (int i = 0; i < MAX_SIZE; i++)
        enqueue(queue, elements + i);

    int *element = (int *) malloc(sizeof(int));

    for (int i = 0; i < MAX_SIZE; i++) {
        dequeue(queue, element);
        printf("%d ", *((int *) element));
    }

    puts("");
    free(element);
    free_queue(queue);
}
