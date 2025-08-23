#include "linked_lists.h"

#define debug(x) printf("%s = %d\n", #x, x)

int init_list(LIST *list, int size) {
    list->elements = (NODE *) malloc(size * sizeof(NODE));

    if (list->elements == NULL) {
        ERR_MESG("No Memory left");
    }

    list->head = -1;
    list->free = list->length = list->tail = 0;
    list->capacity = size;

    for (int i = 0; i < list->capacity; i++) {
        list->elements[i].next = i + 1;
        list->elements[i].prev = -1;
    }

    list->elements[list->capacity - 1].next = -1;

    return 1;
}

int insert(LIST *list, unsigned int index, DATA data) {
    if (list->head == -1) {
        list->head = list->free;
        list->elements[list->head].data = data;
        list->tail = list->head;
        list->free = list->elements[list->free].next;
        list->elements[list->head].next = -1;
        list->elements[list->head].prev = -1;
        list->length++;
        return 1;
    }

    if (list->free == -1) {
        ERR_MESG("Out of Memory");
    }

    if (index > list->capacity) {
        ERR_MESG("Out of Limit Insertion Requested");
    }

    int current = list->head, next_free = list->elements[list->free].next;
    list->elements[list->free].data = data;
    list->length++;

    if (index == 0) {
        list->elements[list->free].next = list->head;
        list->elements[list->head].prev = list->free;
        list->head = list->free;
        list->free = next_free;
        return 1;
    }

    while (--index > 0)
        current = list->elements[current].next;

    if (list->elements[current].next != -1) {
        list->elements[list->elements[current].next].prev = list->free;
    } else {
        list->tail = list->free;
    }

    list->elements[list->free].prev = current;
    list->elements[list->free].next = list->elements[current].next;
    list->elements[current].next = list->free;
    list->free = next_free;

    return 1;
}

int find_index_of(LIST *list, DATA data) {
    int current = list->head, position = 0;

    while (current != -1 && list->elements[current].data != data) {
        current = list->elements[current].next;
        position++;
    }
    
    return current == -1 ? -1 : position;
}

int find_value_at(LIST *list, unsigned int index, DATA *data) {
    if (index >= list->capacity)
        return -1;

    int current = list->head;

    while (--index > 0)
        current = list->elements[current].next;
    *data = list->elements[current].data;

    return 1;
}

void print_list(LIST *list) {
    int current = list->head;

    while (current != -1) {
        printf("%d ", list->elements[current].data);
        current = list->elements[current].next;
    }

    puts("");
}

void print_list_reverse(LIST *list) {
    int current = list->tail;

    while (current != -1) {
        printf("%d ", list->elements[current].data);
        current = list->elements[current].prev;
    }

    puts("");
}

void free_list(LIST *list) {
    for (int i = 0; i < list->capacity; i++)
        list->elements[i].next = i + 1;
    list->elements[list->capacity - 1].next = -1;\

    list->free = 0;
    free(list->elements);
}
