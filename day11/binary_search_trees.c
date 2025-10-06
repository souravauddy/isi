#include "binary_search_tree.h"
#include <stdbool.h>
#include <assert.h>

void init_tree(TREE *tree, int capacity, int type_size, int (*comparator)(DATA, DATA)) {
    tree->capacity = capacity;
    tree->type_size = type_size;
    tree->comparator = comparator;
    tree->number_of_nodes = tree->free = 0;
    tree->root = INT_NULL;
    tree->nodes = (node *) malloc(capacity * sizeof(node));
    assert(tree->nodes);

    for (int i = 0; i < tree->capacity; i++) {
        tree->nodes[i].data = (void *) malloc(tree->type_size);
        tree->nodes[i].left = INT_NULL;
        tree->nodes[i].right = i + 1;
        assert(tree->nodes[i].data);
    }

    tree->nodes[capacity - 1].right = INT_NULL;    
}

void increase_capacity(TREE *tree) {
    tree->nodes = (node *) realloc(tree->nodes, 2 * tree->capacity * sizeof(node));
    assert(tree->nodes);

    for (int i = tree->capacity; i < 2 * tree->capacity; i++) {
        tree->nodes[i].left = INT_NULL;
        tree->nodes[i].right = i + 1;
        tree->nodes[i].data = (void *) malloc(tree->type_size);
        assert(tree->nodes[i].data);
    }

    tree->free = tree->capacity;
    tree->capacity = 2 * tree->capacity;
    tree->nodes[tree->capacity - 1].right = INT_NULL;;
}

inline void insert(TREE *tree, DATA data) {
    tree->root = insert_node(tree, tree->root, data);
}

int insert_node(TREE *tree, int node, DATA data) {
    if (node == INT_NULL) {
        if (tree->number_of_nodes == tree->capacity)
            increase_capacity(tree);

        int previous_free = tree->free;
        memcpy(tree->nodes[tree->free].data, data, tree->type_size);
        tree->free = tree->nodes[tree->free].right;
        tree->nodes[previous_free].right = tree->nodes[previous_free].left = INT_NULL;
        tree->number_of_nodes++;

        return previous_free;
    }

    int compare_value = (*tree->comparator)(tree->nodes[node].data, data);

    if (compare_value > 0)
        tree->nodes[node].left = insert_node(tree, tree->nodes[node].left, data);

    if (compare_value < 0)
        tree->nodes[node].right = insert_node(tree, tree->nodes[node].right, data);

    return node;
}

int search(TREE *tree, int node, DATA data) {
    if (node == INT_NULL)
        return INT_NULL;

    int compare_value = (*tree->comparator)(tree->nodes[node].data, data);

    if (compare_value > 0)
        return search(tree, tree->nodes[node].left, data);
    
    if (compare_value < 0)
        return search(tree, tree->nodes[node].right, data);

    return node;
}

int iterative_search(TREE *tree, DATA data) {
    int node = tree->root, parent = INT_NULL;

    while (node != INT_NULL) {
        int compare_value = (*tree->comparator)(tree->nodes[node].data, data);
        
        if (compare_value == 0)
            return node;

        if (compare_value > 0) {
            node = tree->nodes[node].left;
            continue;
        }
        
        node = tree->nodes[node].right;
    }

    return INT_NULL;
}

inline void delete(TREE *tree, DATA data) {
    tree->root = delete_node(tree, tree->root, data);
}

static inline void free_node(TREE *tree, int node) {
    tree->nodes[node].left = INT_NULL;
    tree->nodes[node].right = tree->free;
    tree->free = node;
}

int delete_node(TREE *tree, int node, DATA data) {
    if (node == INT_NULL)
        return INT_NULL;

    int compare_value = (*tree->comparator)(tree->nodes[node].data, data);

    if (compare_value > 0) {
        tree->nodes[node].left = delete_node(tree, tree->nodes[node].left, data);
        return node;
    }
    
    if (compare_value < 0) {
        tree->nodes[node].right = delete_node(tree, tree->nodes[node].right, data);
        return node;
    }

    tree->number_of_nodes--;

    if (tree->nodes[node].left != INT_NULL && tree->nodes[node].right != INT_NULL) {
        int right_child = tree->nodes[node].right, current = right_child;

        while (tree->nodes[current].left != INT_NULL)
            current = tree->nodes[current].left;
        
        tree->nodes[current].left = tree->nodes[node].left;
        free_node(tree, node);

        return right_child;
    }

    if (tree->nodes[node].left != INT_NULL) {
        int left_child_index = tree->nodes[node].left;
        free_node(tree, node);
        return left_child_index;
    }

    if (tree->nodes[node].right != INT_NULL) {
        int right_child = tree->nodes[node].right;
        free_node(tree, node);
        return right_child;
    }

    free_node(tree, node);
    return INT_NULL;
}

void free_tree(TREE *tree) {
    for (int i = 0; i < tree->capacity; i++)
        free(tree->nodes[i].data);

    free(tree->nodes);
    free(tree);
}

void dump_table(TREE *tree, FILE *file) {
    fprintf(file, "%d\n", tree->capacity);

    for (int node = 0; node < tree->capacity; node++)
        fprintf(file, "%d %d %d\n", *((int *) tree->nodes[node].data), tree->nodes[node].left, tree->nodes[node].right);

    fprintf(file, "%d\n", tree->root);
}

void preorder(TREE *tree, int node, void (*print_data)(DATA)) {
    if (node == INT_NULL)
        return;

    (*print_data)(tree->nodes[node].data);
    preorder(tree, tree->nodes[node].left, print_data);
    preorder(tree, tree->nodes[node].right, print_data);
}

void inorder(TREE *tree, int node, void (*print_data)(DATA)) {
    if (node == INT_NULL)
        return;

    inorder(tree, tree->nodes[node].left, print_data);
    (*print_data)(tree->nodes[node].data);
    inorder(tree, tree->nodes[node].right, print_data);
}
