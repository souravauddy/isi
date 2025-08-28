#include "/Users/souravauddy/Documents/isi/day6/linked_lists.h"

const int INT_NULL = (int) -1;

int reverse_list(LIST *list, int previous , int next) {
    if (next == INT_NULL)
        return previous;

    int head = reverse_list(list, next, list->elements[next].next);
    list->elements[next].next = previous;
    return head;
}

int main(const int argc, const char **argv) {
    if (argc < 2)
        ERR_MESG("Linked List not given.");

    const int N = (int) argc - 1;
    LIST *list = (LIST *) malloc(sizeof(LIST));

    init_list(list, N);

    for (int i = 1; i <= N; i++)
        insert_at_end(list, atoi(argv[i]));

    puts("Initial list before reversing");
    print_list(list);

    list->head = reverse_list(list, INT_NULL, list->head);

    puts("after reversing");
    print_list(list);

    free_list(list);
    free(list);
}
