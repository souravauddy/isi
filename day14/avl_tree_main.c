#include <stdio.h>
#include "avl_tree.h"

void print_int(DATA data) {
    printf("%d ", *((int *) data));
}

void _inorder(avl_tree *tree, const int node, void (*print_int)(DATA data)) {
    if (node == INT_NULL)
        return;

    _inorder(tree, tree->nodes[node].left, print_int);
    (*print_int)(tree->nodes[node].data);
    _inorder(tree, tree->nodes[node].right, print_int);
}

void inorder(avl_tree *tree, void (*print_int)(DATA data)) {
    _inorder(tree, tree->root, print_int);
    puts("");
}

static inline int int_comparator(DATA data1, DATA data2) {
    return *((int *) data1) - *((int *) data2);
}

int get_height(const avl_tree *tree, const int node) {
    return tree->nodes[node].height - 1;
}

int main() {
    int array[] =    {1, 2, 3, 4, 50, 6, 17, 8, 19, 11, 10, 12, 45, 14, 25};
    // int indicies[] = {0, 1, 2, 3, 4,  5,  6, 7,  8,  9, 10, 11, 12, 13, 14};

    avl_tree *tree = (avl_tree *) malloc(sizeof(avl_tree));

    init_tree(tree, 20, sizeof(int), int_comparator);

    for (int i = 0; i < 15; i++)
        insert(tree, &array[i]);

    delete(tree, array + 0);
    delete(tree, array + 14);
    delete(tree, array + 6);
    delete(tree, array + 7);

    insert(tree, array + 4);
    inorder(tree, print_int);

    dump_tree(tree, stderr);
    free_tree(tree);
}
