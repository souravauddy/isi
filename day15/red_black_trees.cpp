#include <string_view>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <random>
#include <vector>
#include <limits>
#include <format>
#include <print>

const int INT_NULL = int(-1);

enum class colour : bool {
    RED, BLACK,
};

template<>
struct std::formatter<colour> : std::formatter<std::string_view> {
    constexpr auto format(const colour &color, std::format_context &context) const noexcept {
        return std::formatter<std::string_view>::format(color == colour::RED ? "RED" : "BLACK", context);
    }
};

template<typename Type>
struct node {
    inline constexpr static const Type SENTINEL = std::numeric_limits<Type>::max();
    
    Type data;
    int left, right;
    colour color;

    node(Type _data = node::SENTINEL) : data(_data), left(INT_NULL), right(INT_NULL), color(colour::RED) {}
};

template<typename Type = int32_t>
class red_black_tree {
    inline constexpr static const size_t MIN_CAPACITY = size_t(20);

    std::vector<node<Type>> nodes;
    size_t capacity, number_of_nodes;
    int free, root;

    void increase_capacity() {
        this->capacity *= 2;
        this->nodes.resize(capacity);

        for (int i = capacity >> 1; i < this->capacity; i++)
            this->nodes[i].right = i + 1;

        this->nodes[this->capacity - 1].right = INT_NULL;
        this->free = this->capacity >> 1;
    }

    bool can_be_flipped_colors(const int node) {
        return nodes[node].left != INT_NULL && nodes[node].right != INT_NULL && nodes[nodes[node].left].color == colour::RED && nodes[nodes[node].right].color == colour::RED && nodes[node].color == colour::BLACK;
    }

    int left_rotation(const int node) {
        int right_child = nodes[node].right, previous_left_child = nodes[right_child].left;

        nodes[right_child].left = node;
        nodes[node].right = previous_left_child;
        std::swap(nodes[right_child].color, nodes[nodes[right_child].left].color);

        return right_child;
    }

    int right_rotation(const int node) {
        int left_child = nodes[node].left, previous_right_child = nodes[left_child].right;

        nodes[left_child].right = node;
        nodes[node].left = previous_right_child;
        std::swap(nodes[left_child].color, nodes[nodes[left_child].right].color);

        if (can_be_flipped_colors(left_child))
            return flip_colors(left_child);

        return left_child;
    }
    
    [[nodiscard]]
    int flip_colors(const int node) noexcept {
        nodes[nodes[node].left].color = colour::BLACK;
        nodes[nodes[node].right].color = colour::BLACK;
        nodes[node].color = colour::RED;
        return node;
    }

    [[nodiscard]]
    int insert_node(int node, const Type &data) {
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

        /* Write the correct insertion logic here. */

        if (can_be_flipped_colors(node))
            return flip_colors(node);

        if (nodes[node].right != INT_NULL && nodes[nodes[node].right].color == colour::RED)
            return left_rotation(node);

        if (nodes[node].left != INT_NULL && nodes[nodes[node].left].color == colour::RED)
            if (nodes[nodes[node].left].left != INT_NULL && nodes[nodes[nodes[node].left].left].color == colour::RED)
                return right_rotation(node);

        return node;
    }
    
    [[nodiscard]]
    int erase_node(int node, const Type &data) noexcept {
        if (node == INT_NULL)
            return INT_NULL;

        if (nodes[node].data > data)
            nodes[node].left = erase_node(nodes[node].left, data);

        if (nodes[node].data < data)
            nodes[node].right = erase_node(nodes[node].right, data);

        const int left_child = nodes[node].left, right_child = nodes[node].right;
    }

public:

    red_black_tree(const size_t _capacity = red_black_tree::MIN_CAPACITY) : capacity(std::max(_capacity, red_black_tree::MIN_CAPACITY)), root(INT_NULL), number_of_nodes(0), free(0) {
        nodes.resize(capacity);

        for (int i = 0; i < capacity; i++)
            nodes[i].right = i + 1;

        nodes[capacity - 1].right = INT_NULL;
    }

    void insert(const Type &data) noexcept {
        this->root = insert_node(root, data);
        this->nodes[this->root].color = colour::BLACK;        
    }

    void erase(const Type &data) noexcept {
        this->root = erase_node(root, data);

        if (this->root != INT_NULL)
            this->nodes[this->root].color = colour::BLACK;
    }

    [[nodiscard]]
    bool contains(const Type &data) const {
        return find(data) != INT_NULL;
    }

    [[nodiscard]]
    int find(const Type &data) const {
        int current = root;

        while (current != INT_NULL) {
            if (nodes[current] == data)
                return current;

            if (nodes[current] > data) {
                current = nodes[current].left;
                continue;
            }

            current = nodes[current].right;
        }

        return INT_NULL;
    }

    [[nodiscard]]
    node<Type>& operator[](const int node_index) {
        return this->nodes[node_index];
    }

    [[nodiscard]]
    const node<Type>& operator[](const int node_index) const {
        return this->nodes[node_index];
    }

    [[nodiscard]]
    size_t size() const {
        return this->number_of_nodes;
    }

    [[nodiscard]]
    bool empty() const {
        return this->number_of_nodes == 0;
    }

    [[nodiscard]]
    int get_root() const noexcept {
        return root;
    }

    void read(const int ROOT = 0) {
        std::cin >> capacity;
        nodes.resize(capacity);

        for (int i = 0; i < capacity; i++)
            std::cin >> nodes[i].data >> nodes[i].left >> nodes[i].right;

        free = INT_NULL;
        root = ROOT;
        number_of_nodes = capacity;
    }

    void dump(bool colors = false, FILE *file = stderr) {
        std::println(file, "{}", capacity);
        
        if (colors)
            for (int i = 0; i < capacity; i++)
                std::println(file, "{} {} {} {}", (nodes[i].data == INT_MAX) ? 1e9 + 5 : nodes[i].data, nodes[i].left, nodes[i].right, nodes[i].color);
        else
            for (int i = 0; i < capacity; i++)
                std::println(file, "{} {} {}", ((nodes[i].data == INT_MAX) ? 1e9 + 5 : nodes[i].data), nodes[i].left, nodes[i].right);

        std::println(file, "{}", root);
        std::fflush(stderr);
    }

    ~red_black_tree() = default;
};

void inorder(const red_black_tree<int> &tree, const int node) {
    if (node == INT_NULL)
        return;

    inorder(tree, tree[node].left);
    std::print("{} ", (tree[node].data == INT_MAX) ? (1e9 + 5) : tree[node].data);
    inorder(tree, tree[node].right);
}

void preorder(const red_black_tree<int> &tree, const int node) {
    if (node == INT_NULL)
        return;

    std::print("{} ", tree[node].data);
    preorder(tree, tree[node].left);
    preorder(tree, tree[node].right);
}

int main() {
    std::vector<int> numbers{2, 4, 11, 5, 3, 4, 24, 21, 15, 33, 123, 6};
    red_black_tree<int> tree;

    tree.read();
    
    // std::random_device device;
    // std::mt19937 generator(device());
    // std::vector<int> values;

    // for (int i = 0; i < 8; i++) {
    //     values.push_back(generator() % 1000);
    // }

    // std::sort(values.begin(), values.end());

    // for (int value : values)
    //     tree.insert(value);

    // const int N = int(numbers.size());

    // for (int i = 0; i < N; i++)
    //     tree.insert(numbers[i]);

    tree.dump();
    tree.dump(true); // dump with colors.
}
