#include <functional>
#include <iostream>
#include <cassert>
#include <vector>
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

int main() {
    int number_of_words;
    std::cin >> number_of_words;
    std::vector<std::string> words(number_of_words);
    trie tri;

    for (auto &word : words) {
        std::cin >> word;
        tri.add(word);
    }

    std::string typed_word, suggestion;
    std::cin >> typed_word;
    int word_index = 0, current = trie::ROOT_INDEX;
    std::vector<std::string> suggestions;

    while (word_index < typed_word.length()) {
        if (!tri[current].contains(typed_word[word_index]))
            break;

        current = tri[current].next(typed_word[word_index]);
        suggestion.push_back(typed_word[word_index]);
        word_index++;
    }

    y_combinator([&](auto dfs, const int node) -> void {
        if (tri[node].end_of_word && !suggestion.empty())
            suggestions.push_back(suggestion);

        for (int a = 0; a < ALPHABET; a++) {
            if (tri[node].contains(char(a + MIN_CHAR))) {
                suggestion.push_back(char(a + MIN_CHAR));
                dfs(tri[node].next(char(a + MIN_CHAR)));
                suggestion.pop_back();
            }
        }
    })(current);

    for (int i = 0; i < suggestions.size(); i++)
        std::println("{}.> {}", i + 1, suggestions[i]);

    int chosen_suggestion_index;
    std::cin >> chosen_suggestion_index;

    if (chosen_suggestion_index == -1) {
        std::println("Invalid Index so adding word to the trie: {}", typed_word);
        tri.add(typed_word);
        return 0;
    }

    std::println("{}", suggestions[chosen_suggestion_index - 1]);
}
