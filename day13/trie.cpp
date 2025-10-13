#include <iostream>
#include <print>
#include <vector>
#include <cassert>
#include <utility>
#include <functional>
#include <queue>

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

const int ALPHABET = int(26);
const int INT_NULL = int(-1);
const char MIN_CHAR = char('a');
const char NULL_CHAR = char('\0');

struct node_info {
    int node_index, level;
};

struct node {
    char end_of_word;
    std::array<int, ALPHABET> next_index;

    node() : end_of_word(NULL_CHAR) {
        next_index.fill(INT_NULL);
    }

    int add(const char character, const int index) noexcept {
        return next_index[character - MIN_CHAR] = index;
    }

    [[nodiscard]]
    int next(const char character) const {
        assert(std::tolower(character) == character);
        return next_index[character - MIN_CHAR];
    }

    [[nodiscard]]
    bool contains(const char character) const {
        return next_index[character - MIN_CHAR] != INT_NULL;
    }
};

struct trie {
    constexpr static const int ROOT_INDEX = int(0);
    std::vector<node> nodes;

    trie() {
        nodes.emplace_back();   // this is for the root of the tree.
    }

    void add(const std::string &string) {
        const int N = int(string.length());
        int node_index = trie::ROOT_INDEX;

        for (int i = 0; i < N; i++) {
            if (nodes[node_index].contains(string[i])) {
                node_index = nodes[node_index].next(string[i]);
                continue;
            }

            nodes.emplace_back();
            node_index = nodes[node_index].add(string[i], nodes.size() - 1);
        }

        nodes[node_index].end_of_word = string.back();
    }

    [[nodiscard]]
    const node& operator[](const int index) const {
        return nodes[index];
    }

    [[nodiscard]]
    node& operator[](const int index) {
        return nodes[index];
    }
    
    [[nodiscard]]
    bool search(const std::string &string) const {
        const int N = int(string.length());
        int node_index = trie::ROOT_INDEX;

        for (int i = 0; i < N; i++) {
            if (!nodes[node_index].contains(string[i]))
                return false;

            node_index = nodes[node_index].next(string[i]);
        }

        return nodes[node_index].end_of_word;
    }
};

int main() {
    int N;
    std::cin >> N;
    std::vector<std::string> strings(N);
    trie dictionary_trie;

    for (int i = 0; i < N; i++)
        std::cin >> strings[i];

    for (const std::string &string : strings)
        dictionary_trie.add(string);

    std::string candidate;
    std::cin >> candidate;

    bool can_be_broken = false;

    std::println("can_be_broken = {}", can_be_broken);
}
