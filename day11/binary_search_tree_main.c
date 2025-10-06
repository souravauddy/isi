#include "binary_search_tree.h"

const double EPSILON = (double) 1e-6;
const int MIN_CAPACITY = (int) 2;
extern const int INT_NULL;

struct pair {
    int first, second;
};

typedef struct pair pair;

void print_int(DATA data) {
    printf("%d ", *((int *) data));
}

void print_double(DATA data) {
    printf("%lf ", *((double *) data));
}

void print_string(DATA data) {
    printf("(%s) ", *((char **) data));
}

void print_pair(DATA data) {
    pair *pair_data = (pair *) data;
    printf("(%d, %d) ", pair_data->first, pair_data->second);
}

int int_comparator(DATA data1, DATA data2) {
    int int_data_1 = *((int *) data1), int_data_2 = *((int *) data2);
    return (int_data_1 - int_data_2);
}

int double_comparator(DATA data1, DATA data2) {
    double double_data1 = *((double *) data1), double_data2 = *((double *) data2);
    double difference = double_data1 - double_data2;

    if (fabs(difference) < EPSILON)
        return 0;

    return difference > 0 ? 1 : -1;
}

int string_comparator(DATA data1, DATA data2) {
    return strcmp(*((char **) data1), *((char **) data2));
}

int pair_comparator(DATA data1, DATA data2) {
    return ((pair *) data1)->first - ((pair *) data2)->first;
}

int main() {
    int data[] = {20, 40, 500, 2, 5, 25};
    // char *data[6] = {"sourav", "auddy", "sourav auddy", "auddy sourav", "SOURAV", "AUDDY"};
    // double data[] = {25.24, 44.52, 999.529, 81.25, 2049184.2, 44};
    // pair data[] = {{20, 40}, {40, 50}, {2, 29}, {24, 28}, {4000, 28}, {285, 241}, {245, 2222}};

    TREE *tree = (TREE *) malloc(sizeof(TREE));
    init_tree(tree, MIN_CAPACITY, sizeof(int), int_comparator);

    insert(tree, data + 0);
    insert(tree, data + 1);
    insert(tree, data + 2);
    insert(tree, data + 3);
    insert(tree, data + 4);
    insert(tree, data + 5);
    
    puts("Preorder Traversal");
    preorder(tree, tree->root, print_int);
    puts("");

    puts("Inorder Traversal");
    inorder(tree, tree->root, print_int);
    puts("");

    printf("search index = %d\n", iterative_search(tree, data + 6));

    delete(tree, data + 2);
    puts("Inorder Traversal");
    inorder(tree, tree->root, print_int);
    puts("");

    printf("number of nodes = %d\n", tree->number_of_nodes);

    delete(tree, data + 2);
    puts("Inorder Traversal");
    inorder(tree, tree->root, print_int);
    puts("");

    printf("number of nodes = %d\n", tree->number_of_nodes);

    delete(tree, data + 3);
    puts("Inorder Traversal");
    inorder(tree, tree->root, print_int);
    puts("");

    printf("number of nodes = %d\n", tree->number_of_nodes);

    puts("Preorder Traversal");
    preorder(tree, tree->root, print_int);
    puts("");

    printf("root = ");
    print_int(tree->nodes[tree->root].data);
    puts("");

    delete(tree, data + 0);
    puts("Inorder Traversal");
    inorder(tree, tree->root, print_int);
    puts("");

    printf("number of nodes = %d\n", tree->number_of_nodes);

    puts("Preorder Traversal");
    preorder(tree, tree->root, print_int);
    puts("");

    insert(tree, data + 2);
    puts("Inorder Traversal");
    inorder(tree, tree->root, print_int);
    puts("");

    puts("Preorder Traversal");
    preorder(tree, tree->root, print_int);
    puts("");

    dump_table(tree, stderr);
    free_tree(tree);
}
