#include "../linked_lists.h"

const int INT_NULL = (int) -1;

void reverse_list(LIST *list, int starting_point) {
    
}

int main(const int argc, const char **argv) {
    if (argc < 2)
        ERR_MESG("Linked List not given.");

    const int N = (int) argc - 1;
    LIST *list = (LIST *) malloc(sizeof(LIST));

    for (int i = 1; i <= N; i++)
        insert_at_end(list, atoi(argv[i]));

    int slow, fast, slow_index = 0;
    slow = fast = list->head;

    while (fast != INT_NULL && list->elements[fast].next != INT_NULL) {
        slow = list->elements[slow].next;
        fast = list->elements[fast].next;
        slow_index++;

        if (fast != INT_NULL)
            fast = list->elements[fast].next;
    }


}
