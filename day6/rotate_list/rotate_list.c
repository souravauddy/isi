#include "../linked_lists.h"

const int INT_NULL = (int) -1;

int main(const int argc, const char **argv) {
    if (argc < 2)
        ERR_MESG("Linked List not given.");

    const int N = (int) argc - 2;
    int k = (N + atoi(argv[1])) % N;

    /*
    * list is considered as a singly linked list.
    */

    LIST *list = (LIST *) malloc(sizeof(LIST));    
    init_list(list, N);

    for (int i = 2; i <= N + 1; i++)
        insert_at_end(list, atoi(argv[i]));

    if (k == 0) {
        print_list(list);
        return 0;
    }

    int current = list->head;

    while (--k > 0)
        current = list->elements[current].next;
    
    int original_head = list->head;
    list->head = list->elements[current].next;
    list->elements[list->tail].next = original_head;
    list->elements[current].next = INT_NULL;

    print_list(list);

    free_list(list);
    free(list);
}
