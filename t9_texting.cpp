#include <functional>
#include <iostream>
#include <cassert>
#include <vector>
#include <format>
#include <array>

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

    [[nodiscard]]
    bool leaf() const noexcept {
        for (int a = 0; a < ALPHABET; a++)
            if (next_index[a] != INT_NULL)
                return false;

        return true;
    }
};

struct trie {
    inline constexpr static const int ROOT_INDEX = int(0);
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

constexpr const int KEYS = int(11);
constexpr const std::array<std::string, KEYS> KEYBOARD = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqr", "tuv", "wxyz"};
constexpr const char MIN_DIGIT = char('0');

int main() {
    int number_of_dictionary_items;
    std::cin >> number_of_dictionary_items;
    trie dictionary;
    std::string word;
    
    for (int i = 0; i < number_of_dictionary_items; i++) {
        std::cin >> word;
        dictionary.add(word);
    }

    std::string t9_text, suggestion;
    std::cin >> t9_text;
    suggestion.reserve(t9_text.length());

    y_combinator([&](auto dfs, const int trie_index, const int t9_index) -> void {
        if (dictionary[trie_index].end_of_word)
            std::println("{}", suggestion);

        if (t9_index == t9_text.length())
            return;

        for (const char letter : KEYBOARD[t9_text[t9_index] - MIN_DIGIT]) {
            if (dictionary[trie_index].contains(letter)) {
                suggestion.push_back(letter);
                dfs(dictionary[trie_index].next(letter), t9_index + 1);
                suggestion.pop_back();
            }
        }
    })(trie::ROOT_INDEX, 0);
}
