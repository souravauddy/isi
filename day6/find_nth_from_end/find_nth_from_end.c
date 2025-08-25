#include "../linked_lists.h"

#define debug(x) printf("%s = %d\n", #x, x)

const int INT_NULL = (int) -1;

int main(const int argc, const char **argv) {
    if (argc < 2)
        ERR_MESG("List is not given as input.");
        
    const int N = (int) argc - 2, K = atoi(argv[1]);
    LIST *list = (LIST *) malloc(sizeof(list));

    init_list(list, N);

    for (int i = 2; i <= N + 1; i++)
        insert_at_end(list, atoi(argv[i]));

    print_list(list);

    int current = list->head;

    for (int i = 0; i < N - K; i++)
        current = list->elements[current].next;

    printf("%d\n", list->elements[current].data);

    free_list(list);
    free(list);
}
