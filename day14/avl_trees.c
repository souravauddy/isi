#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "avl_tree.h"

const int INT_NULL = (int) -1;
const int SENTINEL = (int) 0x7fffffff;
const int *SENTINEL_POINTER = (int *) &SENTINEL;
const int MIN_CAPACITY = (int) 2;

static inline int max(const int a, const int b) {
    return a > b ? a : b;
}

void init_tree(avl_tree *tree, const int capacity, const int type_size, int (*comparator)(DATA, DATA)) {
    tree->capacity = max(capacity, MIN_CAPACITY);
    tree->type_size = type_size;
    tree->free = tree->number_of_nodes = 0;
    tree->root = INT_NULL;
    tree->nodes = (node *) malloc(tree->capacity * sizeof(node));
    tree->comparator = comparator;

    for (int i = 0; i < tree->capacity; i++) {
        tree->nodes[i].left = INT_NULL;
        tree->nodes[i].right = i + 1;
        tree->nodes[i].height = 1;
        tree->nodes[i].data = (void *) malloc(tree->type_size);
        memcpy(tree->nodes[i].data, SENTINEL_POINTER, tree->type_size);
    }

    tree->nodes[tree->capacity - 1].right = INT_NULL;
}

void init_root(avl_tree *tree, const int root) {
    tree->root = root;
}

void _increase_capacity(avl_tree *tree) {
    tree->nodes = (node *) realloc(tree->nodes, 2 * tree->capacity * sizeof(node));

    for (int i = tree->capacity; i < 2 * tree->capacity; i++) {
        tree->nodes[i].left = INT_NULL;
        tree->nodes[i].right = i + 1;
        tree->nodes[i].height = 1;
        tree->nodes[i].data = (void *) malloc(tree->type_size);
        memcpy(tree->nodes[i].data, SENTINEL_POINTER, tree->type_size);
    }

    tree->free = tree->capacity;
    tree->capacity = 2 * tree->capacity;
    tree->nodes[tree->capacity - 1].right = INT_NULL;
}

int _get_height(const avl_tree *tree, const int node) {
    if (node == INT_NULL)
        return 0;

    return tree->nodes[node].height;
}

static inline void _adjust_height(avl_tree *tree, const int node) {
    tree->nodes[node].height = 1 + max(_get_height(tree, tree->nodes[node].left), _get_height(tree, tree->nodes[node].right));
}

static inline int _get_balance_factor(avl_tree *tree, const int node) {
    const int left_child = tree->nodes[node].left, right_child = tree->nodes[node].right;
    return _get_height(tree, left_child) - _get_height(tree, right_child);
}

static inline bool _balanced(avl_tree *tree, const int node) {
    return abs(_get_balance_factor(tree, node)) <= 1;
}

int _right_rotation(avl_tree *tree, const int node) {
    int left_child = tree->nodes[node].left, previous_right_child = tree->nodes[left_child].right;

    tree->nodes[left_child].right = node;
    tree->nodes[node].left = previous_right_child;
    _adjust_height(tree, node);
    _adjust_height(tree, left_child);

    return left_child;
}

int _left_rotation(avl_tree *tree, const int node) {
    int right_child = tree->nodes[node].right, previous_left_child = tree->nodes[right_child].left;
    
    tree->nodes[right_child].left = node;
    tree->nodes[node].right = previous_left_child;
    _adjust_height(tree, node);
    _adjust_height(tree, right_child);

    return right_child;
}

int _balanced_node(avl_tree *tree, const int node) {
    const int node_balance_factor = _get_balance_factor(tree, node);

    if (node_balance_factor > 1) {
        /* Some form of right balancing required. */
        int left_subtree_balance_factor = _get_balance_factor(tree, tree->nodes[node].left);

        /* right right rotation. */
        if (left_subtree_balance_factor > 0)
            return _right_rotation(tree, node);

        /* right left rotation. */
        if (left_subtree_balance_factor < 0) {
            tree->nodes[node].left = _left_rotation(tree, tree->nodes[node].left);
            return _right_rotation(tree, node);
        }

        assert(false);
    }

    if (node_balance_factor < -1) {
        /* Some form of left balancing required. */
        int right_subtree_balance_factor = _get_balance_factor(tree, tree->nodes[node].right);

        /* left left rotation. */
        if (right_subtree_balance_factor < 0)
            return _left_rotation(tree, node);

        /* left right rotation. */
        if (right_subtree_balance_factor > 0) {
            tree->nodes[node].right = _right_rotation(tree, tree->nodes[node].right);
            return _left_rotation(tree, node);
        }

        assert(false);
    }

    assert(false);
}

int _insert_node(avl_tree *tree, const int node, const DATA data) {
    if (node == INT_NULL) {
        if (tree->free == INT_NULL) {
            assert(tree->number_of_nodes == tree->capacity);
            _increase_capacity(tree);
        }

        int previous_free = tree->free;
        memcpy(tree->nodes[tree->free].data, data, tree->type_size);
        tree->free = tree->nodes[tree->free].right;
        assert(tree->nodes[previous_free].left == INT_NULL);
        tree->nodes[previous_free].right = INT_NULL;
        tree->number_of_nodes++;
        return previous_free;
    }

    int compare_value = (*tree->comparator)(tree->nodes[node].data, data);

    if (compare_value > 0)
        tree->nodes[node].left = _insert_node(tree, tree->nodes[node].left, data);

    if (compare_value < 0)
        tree->nodes[node].right = _insert_node(tree, tree->nodes[node].right, data); 

    _adjust_height(tree, node);

    if (!_balanced(tree, node))
        return _balanced_node(tree, node);

    return node;
}

inline void insert(avl_tree *tree, const DATA data) {
    tree->root = _insert_node(tree, tree->root, data);
}

int _get_sucessor(avl_tree *tree, const int node) {
    int current = tree->nodes[node].right;

    while (current != INT_NULL && tree->nodes[current].left != INT_NULL)
        current = tree->nodes[current].left;

    return current;
}

static inline void _free_node(avl_tree *tree, const int node) {
    tree->nodes[node].left = INT_NULL;
    tree->nodes[node].height = 1;
    tree->nodes[node].right = tree->free;
    tree->free = node;
    memcpy(tree->nodes[tree->free].data, SENTINEL_POINTER, tree->type_size);
}

int _adjust_path_heights(avl_tree *tree, const int node) {
    if (node == INT_NULL)
        return INT_NULL;

    tree->nodes[node].left = _adjust_path_heights(tree, tree->nodes[node].left);
    _adjust_height(tree, node);
    return !_balanced(tree, node) ? _balanced_node(tree, node) : node;
}

int _delete_node(avl_tree *tree, const int node, const DATA data) {
    if (node == INT_NULL)
        return INT_NULL;

    int compare_value = (*tree->comparator)(tree->nodes[node].data, data);

    if (compare_value == 0) {
        tree->number_of_nodes--;
        const int left_child = tree->nodes[node].left, right_child = tree->nodes[node].right;

        if (left_child != INT_NULL && right_child != INT_NULL) {
            int current = right_child, parent = node;

            while (tree->nodes[current].left != INT_NULL) {
                parent = current;
                current = tree->nodes[current].left;
            }

            if (parent == node) {
                tree->nodes[right_child].left = left_child;
                _adjust_height(tree, right_child);
                _free_node(tree, node);
                return !_balanced(tree, right_child) ? _balanced_node(tree, right_child) : right_child;
            }

            tree->nodes[parent].left = tree->nodes[current].right;
            _adjust_height(tree, parent);
            tree->nodes[current].left = tree->nodes[node].left;
            tree->nodes[current].right = tree->nodes[node].right;
            _free_node(tree, node);
            tree->nodes[current].right = _adjust_path_heights(tree, tree->nodes[current].right);
            _adjust_height(tree, current);

            return !_balanced(tree, current) ? _balanced_node(tree, current) : current;
        }

        _free_node(tree, node);

        if (left_child != INT_NULL)
            return left_child;

        if (right_child != INT_NULL)
            return right_child;

        return INT_NULL;
    }
    
    if (compare_value > 0)
        tree->nodes[node].left = _delete_node(tree, tree->nodes[node].left, data);

    if (compare_value < 0)
        tree->nodes[node].right = _delete_node(tree, tree->nodes[node].right, data);

    _adjust_height(tree, node);
    return !_balanced(tree, node) ? _balanced_node(tree, node) : node;
}

inline void delete(avl_tree *tree, const DATA data) {
    tree->root = _delete_node(tree, tree->root, data);
}

int search(avl_tree *tree, const DATA data) {
    int current = tree->root;

    while (current != INT_NULL) {
        int compare_value = (*tree->comparator)(tree->nodes[current].data, data);

        if (compare_value > 0) {
            current = tree->nodes[current].left;
            continue;   
        }

        if (compare_value < 0) {
            current = tree->nodes[current].right;
            continue;
        }

        return current;
    }

    return INT_NULL;
}

void dump_tree(avl_tree *tree, FILE *file) {
    fprintf(file, "%zu\n", tree->capacity);

    for (int i = 0; i < tree->capacity; i++)
        fprintf(file, "%d %d %d\n", *((int *) tree->nodes[i].data), tree->nodes[i].left, tree->nodes[i].right);
    
    fprintf(file, "%d\n", tree->root);
}

inline void free_tree(avl_tree *tree) {
    for (int i = 0; i < tree->capacity; i++) {
        assert(_balanced(tree, i) == true);
        free(tree->nodes[i].data);
    }

    free(tree->nodes);
    free(tree);
}
