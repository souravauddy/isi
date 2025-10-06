#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct special_queue {
    int *container;
    size_t tos1, tos2, capacity;
};

typedef struct special_queue special_queue;

void init_queue(special_queue *queue, size_t capacity) {
    queue->container = (int *) malloc(2 * capacity * sizeof(int));
    queue->capacity = 2 * capacity;
    queue->tos1 = 0;
    queue->tos2 = queue->capacity - 1;
}

void _push1(special_queue *queue, int value) {
    assert(queue->tos1 <= queue->tos2);
    queue->container[queue->tos1++] = value;
}

void _push2(special_queue *queue, int value) {
    assert(queue->tos1 <= queue->tos2);
    queue->container[queue->tos2--] = value;
}

int _pop1(special_queue *queue) {
    assert(queue->tos1 >= 0 && queue->tos1 < queue->capacity);
    return queue->container[--queue->tos1];
}

int _pop2(special_queue *queue) {
    assert(queue->tos2 >= 0 && queue->tos2 < queue->capacity);
    return queue->container[++queue->tos2];
}

bool _empty1(special_queue *queue) {
    return queue->tos1 == 0;
}

bool _empty2(special_queue *queue) {
    return queue->tos2 == queue->capacity - 1;
}

bool empty(special_queue *queue) {
    return _empty1(queue) && _empty2(queue);
}

static inline size_t size(special_queue *queue) {
    return queue->tos1 + (queue->capacity - queue->tos2 - 1);
}

void enqueue(special_queue *queue, int value) {
    _push1(queue, value);
}

int dequeue(special_queue *queue) {
    if (!_empty2(queue))
        return _pop2(queue);

    while (!_empty1(queue))
        _push2(queue, _pop1(queue));

    return _pop2(queue);
}

int main() {
    int capacity;
    scanf("%d", &capacity);
    special_queue *queue = (special_queue *) malloc(sizeof(special_queue));
    init_queue(queue, capacity);

    int numbers[] = {1, 49, 288, 2848, 208, 224};

    for (int i = 0; i < 6; i++)
        enqueue(queue, numbers[i]);

    while (!empty(queue))
        printf("%d\n", dequeue(queue));

    free(queue->container);
    free(queue);
}
