#ifndef _AVL_TREE_

#define _AVL_TREE_

#include <stdio.h>
#include <stdlib.h>

extern const int INT_NULL;
extern const int SENTINEL;
extern const int *SENTINEL_POINTER;
extern const int MIN_CAPCITY;

typedef void * DATA;

struct node {
    DATA data;
    int left, right, height;
};

typedef struct node node;

struct avl_tree {
    node *nodes;
    int root, free;
    size_t number_of_nodes, capacity, type_size;
    int (*comparator)(DATA, DATA);
};

typedef struct avl_tree avl_tree;

extern void init_tree(avl_tree *tree, const int capacity, const int type_size, int (*compator)(DATA, DATA));
extern void init_root(avl_tree *tree, const int root);
extern void insert(avl_tree *tree, const DATA data);
extern void delete(avl_tree *tree, const DATA data);
extern int search(avl_tree *tree, const DATA data);
extern void free_tree(avl_tree *tree);
extern void dump_tree(avl_tree *tree, FILE *file);

#endif
