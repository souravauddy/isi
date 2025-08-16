#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

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

struct TreeNode {
    int data;
    TreeNode *left, *right;

    TreeNode(int data = -1, TreeNode *left = nullptr, TreeNode *right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

TreeNode * create_tree(TreeNode *root) {
    int value;
    std::cout << "Enter the value for the node" << '\n';
    std::cin >> value;

    if (value == -1)
        return nullptr;

    if (root == nullptr)
        root = new TreeNode(value);

    std::cout << "Enter the value for the left leaf" << '\n';
    root->left = create_tree(root->left);
    std::cout << "Enter the value for the right leaf" << '\n';
    root->right = create_tree(root->right);

    return root;
}

void dfs(TreeNode *node) {
    std::cout << node->data << '\n';
    
    if (node->left)
        dfs(node->left);
    if (node->right)
        dfs(node->right);
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif
    
    TreeNode *root = nullptr;
    root = create_tree(root);
    
    if (root) {
        dfs(root);
    } else {
        std::cout << "The root is a nullptr" << '\n';
        throw nullptr;
    }
}