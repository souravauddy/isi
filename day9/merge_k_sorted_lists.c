#include "../day6/common.h"
#include "heap.h"

#define debug(x) printf("%s = %d\n", #x, x)

const int MAX_SIZE = (int) 100;
const int TYPE_SIZE[3] = {sizeof(int), sizeof(double), sizeof(char *)};
const char *DELIMETERS = " \n";
const double EPSILON = (double) 1e-6;
        
struct generic_list {
    void *list;
    size_t type, element_size, number_of_elements, index;
};

typedef struct generic_list generic_list;

void init_generic_list(generic_list *list, size_t element_size, size_t number_of_elements, size_t type) {
    list->element_size = element_size;
    list->number_of_elements = number_of_elements;
    list->index = 0;
    list->list = malloc(number_of_elements * element_size);
    list->type = type;
    assert(list->list);
}

void read_int_list(generic_list *list, size_t type) {
    int number_of_items;
    scanf(" %d", &number_of_items);
    list->list = (int *) malloc(number_of_items * TYPE_SIZE[type]);
    assert(list->list);
    init_generic_list(list, TYPE_SIZE[type], number_of_items, type);

    for (int i = 0; i < number_of_items; i++) {
        int value;
        scanf("%d", &value);
        memcpy((int *) list->list + i, &value, list->element_size);
    }
}

void read_double_list(generic_list *list, size_t type) {
    int number_of_items;
    scanf("%d", &number_of_items);
    list->list = (double *) malloc(number_of_items * TYPE_SIZE[type]);
    assert(list->list);
    init_generic_list(list, TYPE_SIZE[type], number_of_items, type);

    for (int i = 0; i < number_of_items; i++) {
        double value;
        scanf(" %lf", &value);
        memcpy((double *) list->list + i, &value, list->element_size);
    }
}

void read_string_list(generic_list *list, size_t type) {
    int number_of_items;
    scanf(" %d", &number_of_items);
    list->list = (char **) malloc(number_of_items * TYPE_SIZE[type]);
    assert(list->list);
    init_generic_list(list, TYPE_SIZE[type], number_of_items, type);

    for (int i = 0; i < number_of_items; i++) {
        char *value = (char *) malloc(MAX_SIZE * sizeof(char));
        scanf(" %s", value);
        memcpy((char **) list->list + i, &value, list->element_size);
    }
}

void print_int_list(generic_list *list) {
    for (int i = 0; i < list->number_of_elements; i++)
        printf("%d ", ((int *) list->list)[i]);
    puts("");
}

void print_double_list(generic_list *list) {
    for (int i = 0; i < list->number_of_elements; i++)
        printf("%lf", ((double *) list->list)[i]);
    puts("");
}

void print_string_list(generic_list *list) {
    for (int i = 0; i < list->number_of_elements; i++)
        printf("%s ", ((char **) list->list)[i]);
    puts("");
}

int int_comparator(void *number1, void *number2) {
    return *((int *) number1) - *((int *) number2);
}

int float_comparator(void *number1, void *number2) {
    double float_number1 = *((double *) number1), float_number2 = *((double *) number2);
    return fabs(float_number1 - float_number2) < EPSILON ? 0 : float_number1 - float_number2;
}

int string_comparator(void *string1, void *string2) {
    char *str1 = *((char **) string1), *str2 = *((char **) string2);
    return strcmp((char *) str1, (char *) str2);
}

void (*read_input[3])(generic_list *, size_t) = {&read_int_list, &read_double_list, &read_string_list};
void (*print_list[3])(generic_list *) = {&print_int_list, &print_double_list, &print_string_list};
int (*type_comparator[3])(void *, void *) = {&int_comparator, &float_comparator, &string_comparator};

int list_comparator(void *list, int index1, int index2) {
    generic_list *g_list = (generic_list *) list;
    generic_list *list1 = &g_list[index1];
    generic_list *list2 = &g_list[index2];
    return (*type_comparator[list1->type])((char *) list1->list + list1->index * list1->element_size, (char *) list2->list + list2->index * list2->element_size);
}

int reverse_list_comparator(void *list, int index1, int index2) {
    return -1 * list_comparator(list, index1, index2);
}

int main() {
    int tests;
    scanf("%d", &tests);

    while (tests-- > 0) {
        int number_of_lists, elements_type, total_number_of_elements = 0;
        scanf(" %d %d", &number_of_lists, &elements_type);
        generic_list *lists = (generic_list *) malloc(number_of_lists * sizeof(generic_list));
        HEAP *heap = (HEAP *) malloc(sizeof(HEAP));
        initHeap(heap, sizeof(generic_list), reverse_list_comparator);
        
        for (int i = 0; i < number_of_lists; i++) {
            lists[i].type = elements_type;
            (*read_input[elements_type])(&lists[i], elements_type);
            total_number_of_elements += lists[i].number_of_elements;
        }

        generic_list merged_list;
        init_generic_list(&merged_list, TYPE_SIZE[elements_type], total_number_of_elements, elements_type);
        int merge_index = 0;

        for (int i = 0; i < number_of_lists; i++)
            insert(heap, &lists[i]);

        while (!empty(heap)) {
            generic_list *list = (generic_list *) malloc(sizeof(generic_list));
            deleteMax(heap, list);
            memcpy((char *) merged_list.list + merge_index++ * list->element_size, (char *) list->list + list->index * list->element_size, list->element_size);
            list->index++;

            if (list->index < list->number_of_elements)
                insert(heap, list);

            free(list);
        }

        (*print_list[elements_type])(&merged_list);

        if (elements_type == 2) {
            for (int i = 0; i < number_of_lists; i++) {
                for (int j = 0; j < lists[i].number_of_elements; j++)
                    free(((char **) lists[i].list)[j]);

                free(lists[i].list);
            }
        } else {
            for (int i = 0; i < number_of_lists; i++)
               free(lists[i].list);
        }

        free(merged_list.list);
        free(lists);
        free(heap);
    }
}