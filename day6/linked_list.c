#include "linked_lists.h"

#define debug(x) printf("%s = %d\n", #x, x)

int init_list(LIST *list, const int size) {
    list->elements = (NODE *) malloc(size * sizeof(NODE));

    if (list->elements == NULL)
        ERR_MESG("No Memory left");

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

static inline void create_head(LIST *list, const DATA data) {
    list->head = list->free;
    list->elements[list->head].data = data;
    list->tail = list->head;
    list->free = list->elements[list->free].next;
    list->elements[list->head].next = -1;
    list->elements[list->head].prev = -1;
    list->length++; 
}

static int increase_capacity(LIST *list) {
    list->free = list->capacity;
    list->capacity = list->capacity * 2;
    list->elements = (NODE *) realloc(list->elements, list->capacity * sizeof(NODE));

    if (list->elements == NULL)
        ERR_MESG("Heap is out of Memory");

    for (int i = list->capacity / 2; i < list->capacity; i++) {
        list->elements[i].next = i + 1;
        list->elements[i].prev = -1;
    }

    list->elements[list->capacity - 1].next = -1;

    return 1;
}

int insert_at_begining(LIST *list, DATA data) {
    if (list->head == -1) {
        create_head(list, data);
        return 1;
    }

    if (list->free == -1)
        increase_capacity(list);

    int next_free = list->elements[list->free].next;
    list->elements[list->free].data = data;
    list->elements[list->free].next = list->head;
    list->elements[list->head].prev = list->free;
    list->head = list->free;
    list->free = next_free;
    list->elements[list->head].prev = -1;
    list->length++;

    return 1;
}

int insert_at_end(LIST *list, DATA data) {
    if (list->head == -1) {
        create_head(list, data);
        return 1;
    }

    if (list->free == -1)
        increase_capacity(list);

    int next_free = list->elements[list->free].next;
    list->elements[list->tail].next = list->free;
    list->elements[list->free].prev = list->tail;
    list->elements[list->free].data = data;
    list->tail = list->free;
    list->elements[list->tail].next = -1;
    list->free = next_free;
    list->length++;

    return 1;
}

int insert(LIST *list, unsigned int index, DATA data) {
    if (list->head == -1) {
        create_head(list, data);
        return 1;
    }

    if (list->free == -1)
        increase_capacity(list);

    if (index > list->length)
        ERR_MESG("Insertion at Invalid Index Requested.");

    if (index == 0)
        return insert_at_begining(list, data);

    if (index == list->length)
        return insert_at_end(list, data);

    int current = list->head, next_free = list->elements[list->free].next;
    list->elements[list->free].data = data;
    list->length++;

    while (--index > 0)
        current = list->elements[current].next;

    if (list->elements[current].next != -1)
        list->elements[list->elements[current].next].prev = list->free;

    list->elements[list->free].prev = current;
    list->elements[list->free].next = list->elements[current].next;
    list->elements[current].next = list->free;
    list->free = next_free;

    return 1;
}

int delete_at_begining(LIST *list, DATA *data) {
    if (list->length == 0)
        ERR_MESG("Invalid Deletion Request.");

    int next_head = list->elements[list->head].next;
    *data = list->elements[list->head].data;
    list->elements[list->head].next = list->free;
    list->free = list->head;
    list->head = next_head;

    if (next_head != -1)
        list->elements[next_head].prev = -1;

    list->length--;

    return 1;
}

int delete_at_end(LIST *list, DATA *data) {
    if (list->length <= 1)
        return delete_at_begining(list, data);

    int current_tail = list->tail;
    *data = list->elements[list->tail].data;
    list->tail = list->elements[list->tail].prev;
    list->elements[list->tail].next = -1;
    list->elements[current_tail].prev = -1;
    list->elements[current_tail].next = list->free;
    list->free = current_tail;
    list->length--;

    return 1;
}

int delete(LIST *list, unsigned int index, DATA *data) {
    puts("In the delete function");

    if (list->length == 0 || index >= list->length)
        ERR_MESG("Invalid Request");
    
    if (index == 0)
        return delete_at_begining(list, data);

    if (index + 1 == list->length)
        return delete_at_end(list, data);

    int current = list->head;

    while (--index > 0)
        current = list->elements[current].next;

    int next = list->elements[current].next, next_to_next = list->elements[next].next;
    list->elements[current].next = next_to_next;
    list->elements[next_to_next].prev = current;
    list->elements[next].next = list->free;
    list->free = next;
    list->length--;
    
    return 1;
}

int find_index_of(const LIST *list, DATA data) {
    int current = list->head, position = 0;

    while (current != -1 && list->elements[current].data != data) {
        current = list->elements[current].next;
        position++;
    }
    
    return current == -1 ? -1 : position;
}

int find_value_at(const LIST *list, unsigned int index, DATA *data) {
    if (index >= list->length)
        return -1;

    int current = list->head;

    while (index-- > 0)
        current = list->elements[current].next;
    *data = list->elements[current].data;

    return 1;
}

void print_list(const LIST *list) {
    int current = list->head;

    while (current != -1) {
        printf("%d ", list->elements[current].data);
        current = list->elements[current].next;
    }

    puts("");
}

void print_list_reverse(const LIST *list) {
    int current = list->tail;

    while (current != -1) {
        printf("%d ", list->elements[current].data);
        current = list->elements[current].prev;
    }

    puts("");
}

void free_list(LIST *list) {
    list->head = list->tail = list->free = -1;
    list->length = list->capacity = 0;
    free(list->elements);
    list->elements = NULL;
}
