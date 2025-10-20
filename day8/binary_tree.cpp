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

    for (int node = 0; node < tree->capacity; node++) {
        std::cin >> data >> left >> right;

        tree->nodes[node].data = data;
        tree->nodes[node].left = left;
        tree->nodes[node].right = right;

        if (left != INT_NULL)
            tree->nodes[left].parent = node;
        
        if (right != INT_NULL)
            tree->nodes[right].parent = node;
    }

    tree->number_of_nodes = tree->capacity;
    tree->free = INT_NULL;
}

void print_tree(BINARY_TREE *tree) {
    if (tree == NULL)
        ERR_MESG("Not a Valid Tree.");

    for (int i = 0; i < tree->capacity; i++)
        std::cout << i << ' ' << tree->nodes[i].data << ' ' << tree->nodes[i].left << ' ' << tree->nodes[i].right << ' ' << tree->nodes[i].parent << '\n';
}

void dump_tree(BINARY_TREE *tree, FILE *file) {
    fprintf(file, "%d\n", tree->capacity);

    for (int node = 0; node < tree->capacity; node++)
        fprintf(file, "%d %d %d\n", tree->nodes[node].data, tree->nodes[node].left, tree->nodes[node].right);

    fprintf(file, "%d\n", tree->root);
}

int increase_capacity(BINARY_TREE *tree) {
    tree->nodes = (NODE *) realloc(tree->nodes, tree->capacity * 2 * sizeof(NODE));
    
    if (tree->nodes == NULL)
        return -1;

    tree->free = tree->capacity;
    tree->capacity = 2 * tree->capacity;

    for (int i = tree->capacity >> 1; i < tree->capacity; i++)
        tree->nodes[i].left = i + 1;
    tree->nodes[tree->capacity - 1].left = INT_NULL;
    
    return 1;
}

void init_root(BINARY_TREE *tree, int root_index) {
    tree->root = root_index;
}
