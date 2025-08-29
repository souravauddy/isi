#include "../day6/common.h"

#ifndef Tree
#define Tree

typedef int DATA;

const int INT_NULL = int(-1);
const int SENTINEL = int(1e9 + 7);

struct NODE {
    DATA data;
    int left, right, parent;
};

struct BINARY_TREE {
    NODE *nodes;
    int root, capacity, number_of_nodes, free;
};

int init_tree(BINARY_TREE *tree, int capacity);
void free_tree(BINARY_TREE *tree);
void read_tree(BINARY_TREE *tree);
void print_tree(BINARY_TREE *tree);

#endif
