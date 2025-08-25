#include "../linked_lists.h"

const int INT_NULL = (int) -1;

int main(const int argc, const char **argv) {
    if (argc < 2)
        ERR_MESG("List not given.");

    const int N = (int) argc - 1;
    LIST *list = (LIST *) malloc(sizeof(LIST));

    init_list(list, N);

    for (int i = 1; i <= N; i++)
        insert_at_end(list, atoi(argv[i]));

    int slow = list->head, fast = list->head;

    while (fast != INT_NULL && list->elements[fast].next != INT_NULL) {
        slow = list->elements[slow].next;
        fast = list->elements[fast].next;
        
        if (fast != INT_NULL)
            fast = list->elements[fast].next;
    }

    printf("%d\n", list->elements[slow].data);

    free_list(list);
    free(list);
}
