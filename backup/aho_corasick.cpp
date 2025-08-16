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
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>
#include <random>
#include <vector>
#include <cassert>
#include <semaphore>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <memory>

// using namespace std;

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

template<const char MIN_CHAR = char('a'), const size_t ALPHABET = size_t(26)>
struct _state {
    constexpr const static int INITIAL = int(0);
    constexpr const static int SENTINEL = int(-1);
    constexpr const static char NULL_CHARACTER = char('\0');

    std::array<int, ALPHABET> next_link;
    size_t suffix_link, parent_link, output_link;
    bool output_state;
    char character;

    _state() noexcept : suffix_link(INITIAL), parent_link(INITIAL), output_link(INITIAL), character(NULL_CHARACTER), output_state(false) {
        next_link.fill(SENTINEL);
    }

    [[nodiscard]]
    bool contains(const char character) const {
        return contains(character - MIN_CHAR);
    }

    [[nodiscard]]
    bool contains(const int index) const {
        return next_link[index] != SENTINEL;
    }

    [[nodiscard]]
    int next(const char character) const {
        return next(character - MIN_CHAR);
    }

    [[nodiscard]]
    int next(const int index) const {
        return next_link[index];
    }

    void add(const char character, const int index) {
        this->next_link[character - MIN_CHAR] = index;
    }

    void update(const char character, const int parent_link) {
        this->character = character;
        this->parent_link = parent_link;
    }
};

template<char _MIN_CHAR = char('a'), size_t _ALPHABET = size_t(26)>
struct aho_corasick {
    using state = _state<_MIN_CHAR, _ALPHABET>;
    std::vector<state> trie;

    aho_corasick() noexcept {
        trie.emplace_back();
    }

    void build(const std::vector<std::string> &strings) {
        for (const std::string &word : strings)
            add(word);

        std::queue<int> queue;

        auto update_queue = [&](const int current_state) -> void {
            for (int link = 0; link < _ALPHABET; link++)
                if (trie[current_state].contains(link))
                    queue.push(trie[current_state].next(link));
        };

        update_queue(state::INITIAL);
        assert(!queue.empty());

        int next_states_count = queue.size();

        for (int next_state = 0; next_state < next_states_count; next_state++) {
            update_queue(queue.front());
            queue.pop();
        }

        while (!queue.empty()) {
            int current_state = queue.front();
            queue.pop();

            int parent = trie[current_state].parent_link;
            char character = trie[current_state].character;

            while (!trie[trie[parent].suffix_link].contains(character) && parent != state::INITIAL)
                parent = trie[parent].parent_link;

            if (trie[trie[parent].suffix_link].contains(character) && current_state != state::INITIAL)
                trie[current_state].suffix_link = trie[trie[parent].suffix_link].next(character);

            trie[current_state].output_link = trie[trie[current_state].suffix_link].output_state ? trie[current_state].suffix_link : trie[trie[current_state].suffix_link].output_link;
            update_queue(current_state);
        }
    }

    void add(const std::string &word) {
        int current_state = state::INITIAL, parent_state;

        for (const char character : word) {
            if (trie[current_state].contains(character)) {
                current_state = trie[current_state].next(character);
                continue;
            }

            trie[current_state].add(character, trie.size());
            parent_state = current_state;
            current_state = trie.size();
            trie.emplace_back();
            trie[current_state].update(character, parent_state);
        }

        trie[current_state].output_state = true;
    }

    [[nodiscard]]
    int get_count(int current_state) const {
        int count = trie[current_state].output_state;

        while (trie[trie[current_state].output_link].output_state)
            current_state = trie[current_state].output_link, count++;

        return count;
    }

    [[nodiscard]]
    int count_occurences(const std::string &string) const {
        int count = 0, current_state = state::INITIAL;

        for (const char character : string) {
            if (trie[current_state].contains(character)) {
                current_state = trie[current_state].next(character);
                count += get_count(current_state);
                continue;
            }

            while (!trie[current_state].contains(character) && current_state != state::INITIAL)
                current_state = trie[current_state].suffix_link;

            current_state = trie[current_state].contains(character) ? trie[current_state].next(character) : state::INITIAL;
            count += get_count(current_state);
        }

        return count;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif

    int N;
    std::cin >> N;
    std::vector<std::string> words(N);

    for (std::string &word : words)
        std::cin >> word;

    std::string pattern;
    std::cin >> pattern;

    aho_corasick AC;
    AC.build(words);

    std::cout << AC.count_occurences(pattern) << '\n';
}


/*
5
acc
atc
cat
gcg
cgc
gcatcgcg
*/