#include "./binary_trees.h"
#include <iostream>
#include <stack>
#include <vector>

void debug_out() {
    std::cerr << std::endl;
}

template<typename Type>
std::ostream& operator<<(std::ostream &os, const std::vector<Type> &other) {
    const int size = other.size();
    if (size <= 0) 
        return os << '[' << ']';
    os << '[';
    for (int i = 0; i < size - 1; i++) 
        os << other[i] << ", ";
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    std::cerr << " [" << head << ']';
    debug_out(args...);
}

#ifdef LOCAL
#define debug(...) std::cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

void iterative_preorder(BINARY_TREE *tree) {
    std::stack<int> stack;
    stack.push(tree->root);

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        std::cout << tree->nodes[node].data << ' ';

        if (tree->nodes[node].left != INT_NULL)
            stack.push(tree->nodes[node].left);

        if (tree->nodes[node].right != INT_NULL)
            stack.push(tree->nodes[node].right);
    }

    std::cout << '\n';
}

void iterative_inorder(BINARY_TREE *tree) {
    std::stack<int> stack;
    stack.push(tree->root);

    std::vector<bool> processed(tree->capacity, false);

    while (!stack.empty()) {
        int node = stack.top();
        int left_child = tree->nodes[node].left, right_child = tree->nodes[node].right;

        if (!processed[left_child] && left_child != INT_NULL) {
            stack.push(left_child);
            continue;
        }

        std::cout << tree->nodes[node].data << ' ';
        stack.pop();
        processed[node] = true;

        if (right_child != INT_NULL)
            stack.push(right_child);
    }

    std::cout << '\n';
}

void iterative_postorder(BINARY_TREE *tree) {
    std::stack<int> stack;
    stack.push(tree->root);
    
    std::vector<bool> processed(tree->capacity);

    while (!stack.empty()) {
        int node = stack.top();

        if (!processed[tree->nodes[node].left] && tree->nodes[node].left != INT_NULL) {
            stack.push(tree->nodes[node].left);
            continue;
        }

        if (!processed[tree->nodes[node].right] && tree->nodes[node].right != INT_NULL) {
            stack.push(tree->nodes[node].right);
            continue;
        }

        stack.pop();
        std::cout << tree->nodes[node].data << ' ';
        processed[node] = true;        
    }

    std::cout << '\n';
}

int main() {
    BINARY_TREE *tree = (BINARY_TREE *) malloc(sizeof(BINARY_TREE));
    assert(tree);

    int capacity;
    std::cin >> capacity;

    init_tree(tree, capacity);
    read_tree(tree);
    init_root(tree, 0);

    iterative_preorder(tree);
    iterative_inorder(tree);
    iterative_postorder(tree);

    free_tree(tree);
}
