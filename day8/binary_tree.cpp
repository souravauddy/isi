#include "binary_trees.h"
#include <iostream>
#include <vector>

int init_tree(BINARY_TREE *tree, int capacity) {
    tree->nodes = (NODE *) malloc(capacity * sizeof(NODE));

    if (tree->nodes == NULL)
        return -1;

    tree->capacity = capacity;
    tree->number_of_nodes = 0;
    tree->root = INT_NULL;

    for (int i = 0; i < capacity; i++) {
        tree->nodes[i].left = i + 1;    // to maintain the free list.
        tree->nodes[i].right = INT_NULL;
        tree->nodes[i].parent = INT_NULL;
        tree->nodes[i].data = SENTINEL;
    }

    tree->nodes[capacity - 1].left = -1;

    return 1;
}

void read_tree(BINARY_TREE *tree) {
    int data, left, right;

    for (int i = 0; i < tree->capacity; i++) {
        std::cin >> data >> left >> right;

        tree->nodes[i].data = data;
        tree->nodes[i].left = left;
        tree->nodes[i].right = right;

        if (left != INT_NULL)
            tree->nodes[tree->nodes[i].left].parent = i;

        if (right != INT_NULL)
            tree->nodes[tree->nodes[i].right].parent = i;
    }
}

void print_tree(BINARY_TREE *tree) {
    if (tree == NULL)
        ERR_MESG("Not a Valid Tree.");

    for (int i = 0; i < tree->capacity; i++)
        std::cout << i << ' ' << tree->nodes[i].data << ' ' << tree->nodes[i].left << ' ' << tree->nodes[i].right << ' ' << tree->nodes[i].parent << '\n';
}

void free_tree(BINARY_TREE *tree) {
    if (tree == NULL)
        ERR_MESG("Not a Valid Tree.");

    free(tree->nodes);
    free(tree);
}
