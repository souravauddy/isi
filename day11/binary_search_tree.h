#ifndef BST_ALT_H
#define BST_ALT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef void * DATA;

extern const int INT_NULL;

struct node {
    DATA data;
    int left, right;
};

typedef struct node node;

struct TREE {
    int number_of_nodes, capacity, type_size, root, free;
    node *nodes;
    int (*comparator)(DATA, DATA);
};

typedef struct TREE TREE;

extern void init_tree(TREE *tree, int capacity, int type_size, int (*comparator)(DATA, DATA));
extern void insert(TREE *tree, DATA data);
extern int insert_node(TREE *tree, int node, DATA data);
extern void preorder(TREE *, int root, void (*print_data)(DATA));
extern void inorder(TREE *, int root, void (*print_data)(DATA));
extern void delete(TREE *tree, DATA data);
extern int delete_node(TREE *tree, int node, DATA data);
extern int search(TREE *, int root, DATA d);
extern int iterative_search(TREE *tree, DATA data);
extern void free_tree(TREE *tree);
extern void dump_table(TREE *tree, FILE *file);

#endif
