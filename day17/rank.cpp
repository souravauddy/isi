#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <random>
#include <ranges>
#include <vector>
#include <print>

const int INT_NULL = int(-1);

template<typename Type>
struct node {
    inline constexpr static const Type SENTINEL = std::numeric_limits<Type>::max();

    Type data;
    int left, right;
    size_t height, subtree_size;

    node() : data(node::SENTINEL), left(INT_NULL), right(INT_NULL), height(1), subtree_size(1) {}

    [[nodiscard]]
    bool operator<(const node &other) const {
        return data < other.data;
    }

    [[nodiscard]]
    bool operator>(const node &other) const {
        return data > other.data;
    }

    [[nodiscard]]
    bool operator==(const node &other) const {
        return data == other.data;
    }

    [[nodiscard]]
    bool operator!=(const node &other) const {
        return data != other.data;
    }
};

template<typename Type = int>
class avl_tree {
    constexpr static const size_t MIN_CAPACITY = int(20);
    int root, free;
    size_t number_of_nodes, capacity;
    std::vector<node<Type>> nodes;
    std::vector<Type> iterator_container;

    void increase_capacity() noexcept {
        this->capacity = 2 * this->capacity;
        nodes.resize(this->capacity);

        for (int i = this->capacity >> 1; i < this->capacity; i++)
            this->nodes[i].right = i + 1;

        this->nodes[this->capacity - 1].right = INT_NULL;
        this->free = this->capacity >> 1;
    }

    [[nodiscard]]
    size_t get_height(const int node) const {
        if (node == INT_NULL)
            return 0;

        return nodes[node].height;
    }

    void adjust_height(const int node) noexcept {
        nodes[node].height = 1 + std::max(get_height(nodes[node].left), get_height(nodes[node].right));
    }

    [[nodiscard]]
    int get_balance_factor(const int node) const {
        return int(get_height(nodes[node].left)) - int(get_height(nodes[node].right));
    }

    [[nodiscard]]
    bool balanced(const int node) const {
        return std::abs(get_balance_factor(node)) <= 1;
    }

    [[nodiscard]]
    int right_rotation(const int node) noexcept {
        int left_child = nodes[node].left, previous_right_child = nodes[left_child].right;

        nodes[left_child].right = node;
        nodes[node].left = previous_right_child;
        adjust_height(node);
        adjust_height(left_child);

        return left_child;
    }

    [[nodiscard]]
    int left_rotation(const int node) {
        int right_child = nodes[node].right, previous_left_child = nodes[right_child].left;

        nodes[right_child].left = node;
        nodes[node].right = previous_left_child;
        adjust_height(node);
        adjust_height(right_child);

        return right_child;
    }

    [[nodiscard]]
    int balanced_node(const int node) {
        int balance_factor = get_balance_factor(node);

        if (balance_factor > 1) {
            int left_child_balance_factor = get_balance_factor(nodes[node].left);

            if (left_child_balance_factor >= 0)
                return right_rotation(node);

            if (left_child_balance_factor < 0) {
                nodes[node].left = left_rotation(nodes[node].left);
                return right_rotation(node);
            }
        }

        if (balance_factor < -1) {
            int right_child_balance_factor = get_balance_factor(nodes[node].right);

            if (right_child_balance_factor <= 0)
                return left_rotation(node);
            
            if (right_child_balance_factor > 0) {
                nodes[node].right = right_rotation(nodes[node].right);
                return left_rotation(node);
            }
        }

        assert(false);
    }

    void free_node(const int node) noexcept {
        assert(node != INT_NULL);
        nodes[node].data = ::node<Type>::SENTINEL;
        nodes[node].right = free;
        nodes[node].left = INT_NULL;
        nodes[node].height = 1;
        free = node;
    }

    [[nodiscard]]
    int insert_node(const int node, const Type &data) {
        if (node == INT_NULL) {
            if (free == INT_NULL)
                increase_capacity();
            
            int previous_free = free;
            nodes[free].data = data;
            free = nodes[free].right;
            nodes[previous_free].right = INT_NULL;
            number_of_nodes++;
            return previous_free;
        }

        if (nodes[node].data > data)
            nodes[node].left = insert_node(nodes[node].left, data);

        if (nodes[node].data < data)
            nodes[node].right = insert_node(nodes[node].right, data);
        
        adjust_height(node);

        if (!balanced(node))
            return balanced_node(node);
            
        return node;
    }

    void inorder(int node) {
        if (node == INT_NULL)
            return;

        inorder(nodes[node].left);
        iterator_container.push_back(nodes[node].data);
        inorder(nodes[node].right);
    }

    [[nodiscard]]
    int adjust_path_heights(const int node) noexcept {
        if (node == INT_NULL)
            return INT_NULL;

        nodes[node].left = adjust_path_heights(nodes[node].left);
        adjust_height(node);
        return !balanced(node) ? balanced_node(node) : node;
    }

    [[nodiscard]]
    int erase_node(const int node, const Type &data) {
        if (node == INT_NULL)
            return INT_NULL;

        if (nodes[node].data == data) {
            number_of_nodes--;
            const int left_child = nodes[node].left, right_child = nodes[node].right;

            if (left_child != INT_NULL && right_child != INT_NULL) {
                int current = right_child, parent = node;

                while (nodes[current].left != INT_NULL) {
                    parent = current;
                    current = nodes[current].left;
                }

                if (parent == node) {
                    nodes[right_child].left = left_child;
                    adjust_height(right_child);
                    free_node(node);
                    return !balanced(right_child) ? balanced_node(right_child) : right_child;
                }

                nodes[parent].left = nodes[current].right;
                adjust_height(parent);
                nodes[current].left = nodes[node].left;
                nodes[current].right = nodes[node].right;
                free_node(node);
                nodes[current].right = adjust_path_heights(nodes[current].right);
                adjust_height(current);

                return !balanced(current) ? balanced_node(current) : current;
            }

            free_node(node);

            if (left_child != INT_NULL)
                return left_child;

            if (right_child != INT_NULL)
                return right_child;

            return INT_NULL;
        }

        if (nodes[node].data > data)
            nodes[node].left = erase_node(nodes[node].left, data);
        
        if (nodes[node].data < data)
            nodes[node].right = erase_node(nodes[node].right, data);

        adjust_height(node);
        return !balanced(node) ? balanced_node(node) : node;
    }

    int compute_subtree_sizes(const int node) {
        if (node == INT_NULL)
            return 0;

        return nodes[node].subtree_size += compute_subtree_sizes(nodes[node].left) + compute_subtree_sizes(nodes[node].right);
    }

    int compute_heights(const int node) {
        if (node == INT_NULL)
            return 1;

        return nodes[node].height = 1 + std::max(compute_heights(nodes[node].left), compute_heights(nodes[node].right));
    }

public:

    avl_tree(const size_t capacity = avl_tree::MIN_CAPACITY) : root(INT_NULL), number_of_nodes(0), free(0) {
        this->capacity = std::max<size_t>(capacity, MIN_CAPACITY);
        nodes.resize(this->capacity);

        for (int i = 0; i < this->capacity; i++)
            this->nodes[i].right = i + 1;

        this->nodes[this->capacity - 1].right = INT_NULL;
    }

    avl_tree(const size_t capacity, const int _root) : avl_tree(capacity), root(_root) {}

    void insert(const Type data) noexcept {
        root = insert_node(root, data);
    }
    
    void erase(const Type data) noexcept {
        root = erase_node(root, data);
    }

    [[nodiscard]]
    int find(const Type& data) const noexcept {
        int current = root;

        while (current != INT_NULL) {
            if (nodes[current].data == data)
                return current;
            
            if (nodes[current].data > data) {
                current = nodes[current].left;
                continue;
            }

            current = nodes[current].right;
        }

        return INT_NULL;
    }

    [[nodiscard]]
    bool contains(const Type &data) const noexcept {
        return find(data) != INT_NULL;
    }

    [[nodiscard]]
    int size() const {
        return number_of_nodes;
    }

    [[nodiscard]]
    node<Type>& operator[](const int index) noexcept {
        return nodes[index];
    }

    void read(const int ROOT = 0) {
        std::cin >> capacity;
        nodes.resize(capacity);

        for (int i = 0; i < capacity; i++)
            std::cin >> nodes[i].data >> nodes[i].left >> nodes[i].right;

        root = ROOT;
        number_of_nodes = capacity;
        free = INT_NULL;

        compute_heights(root);
    }

    void dump(bool dump_heights = false, FILE *file = stderr) const {
        std::println(file, "{}", capacity);

        if (!dump_heights)
            for (const auto &node : nodes)
                std::println(file, "{} {} {}", node.data == ::node<Type>::SENTINEL ? 1e9 + 5 : node.data, node.left, node.right);
        else
            for (const auto &node : nodes)
                std::println(file, "{} {} {} {}", node.data, node.left, node.right, node.height);

        std::println(file, "{}", root);
    }

    [[nodiscard]]
    std::vector<Type>::iterator begin() {
        iterator_container.clear();
        inorder(root);
        return iterator_container.begin();
    }

    [[nodiscard]]
    int lower_bound(const Type &data) const {
        int lower_bound_index = INT_NULL, current = root;

        while (current != INT_NULL) {
            if (nodes[current].data == data)
                return current;

            if (nodes[current].data < data) {
                lower_bound_index = current;
                current = nodes[current].right;
                continue;
            }

            current = nodes[current].left;
        }

        return lower_bound_index;
    }

    void preprocess() {
        assert(number_of_nodes == compute_subtree_sizes(root));
    }

    [[nodiscard]]
    int upper_bound(const Type &data) const {
        int upper_bound_index = INT_NULL, current = root;

        while (current != INT_NULL) {
            if (nodes[current].data == data)
                return current;

            if (nodes[current].data > data) {
                upper_bound_index = current;
                current = nodes[current].left;
                continue;
            }

            current = nodes[current].right;
        }

        return upper_bound_index;
    }

    [[nodiscard]]
    int rank(const Type &value) const {
        int current = avl_tree::root, value_rank = 0;

        while (current != INT_NULL) {
            if (nodes[current].data > value) {
                current = nodes[current].left;
                continue;
            }

            value_rank += 1;

            if (nodes[current].left != INT_NULL)
                value_rank += nodes[nodes[current].left].subtree_size;

            if (nodes[current].data == value)
                return value_rank;
        
            current = nodes[current].right;
        }

        return value_rank;
    }

    [[nodiscard]]
    std::vector<Type>::iterator end() {
        return iterator_container.end();
    }

    [[nodiscard]]
    bool empty() const {
        return number_of_nodes == 0;
    }

    ~avl_tree() = default;
};

int main() {
    avl_tree<int> tree;

    for (int i = 0; i < 20; i++)
        tree.insert(i);

    tree.preprocess();

    int low = 5, high = 25;
    std::cout << tree.rank(low) << ' ' << tree.rank(high) << '\n';
    std::cout << tree.rank(high) - tree.rank(low) + tree.contains(low) << '\n';
}
