#include "../linked_lists.h"

int main(const int argc, const char **argv) {
    if (argc < 2)
        ERR_MESG("Linked List not given.");

    const int N = (int) argc - 1;
    LIST *list = (LIST *) malloc(sizeof(LIST));

    init_list(list, N);

    for (int i = 1; i <= N; i++)
        insert_at_end(list, atoi(argv[i]));

    int previous = -1, current = list->head;

    while (current != -1) {
        int next = list->elements[current].next;
        list->elements[current].next = previous;
        previous = current;
        current = next;
    }

    list->head = previous;
    print_list(list);

    free_list(list);
    free(list);
}
