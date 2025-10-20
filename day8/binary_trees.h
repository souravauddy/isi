#ifndef _LOCAL_Tree

#define _LOCAL_Tree

#include "../day6/common.h"

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

void free_tree(BINARY_TREE *tree, bool local = false);
void read_tree(BINARY_TREE *tree);
void print_tree(BINARY_TREE *tree);
int increase_capacity(BINARY_TREE *tree);
int init_tree(BINARY_TREE *tree, int capacity);
void init_root(BINARY_TREE *tree, int root_index);
void dump_tree(BINARY_TREE *tree, FILE *file);

#endif
