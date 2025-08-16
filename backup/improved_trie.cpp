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

using namespace std;

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
    cerr << endl;
}

template<typename Type>
ostream& operator<<(ostream &os, const vector<Type> &other) {
    const int size = other.size();
    if (size <= 0) 
        return os << '[' << ']';
    os << '[';
    for (int i = 0; i < size - 1; i++) 
        os << other[i] << ' ';
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    cerr << " [" << head << ']';
    debug_out(args...);
}

#ifdef LOCAL
#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

constexpr const int ALPHABET = int(26);
constexpr const char MIN_CHAR = char('a');

struct node {
    array<int, ALPHABET> indicies;
    bool leaf;

    node() : leaf(true) {
        indicies.fill(-1);
    }

    int add(char character, int index) {
        leaf = false;
        return indicies[character - MIN_CHAR] = index;
    }

    int next(char character) const {
        assert(contains(character));
        return indicies[character - MIN_CHAR];
    }

    bool contains(char character) const {
        return ~indicies[character - MIN_CHAR];
    }
};

struct trie {
    vector<node> nodes;

    trie() {
        nodes.emplace_back(); // ROOT is at index = 0
    }

    trie(const vector<string> &strings) {
        nodes.emplace_back();
        build(strings);
    }

    void build(const vector<string> &strings) {
        for (const string &str : strings)
            this->add(str);
    }

    void add(const string &str) {
        int index = 0;

        for (int i = 0; i < str.length(); i++) {
            if (nodes[index].contains(str[i])) {
                index = nodes[index].next(str[i]);
                continue;
            }

            nodes.emplace_back();
            index = nodes[index].add(str[i], nodes.size() - 1);
        }
    }

    int find(const string &str, const bool return_index = true) const {
        int index = 0;

        for (int i = 0; i < str.length(); i++) {
            if (!nodes[index].contains(str[i]))
                return false;

            index = nodes[index].next(str[i]);
        }

        if (return_index)
            return nodes[index].leaf ? index : -1; 
        return nodes[index].leaf;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif
    
    int N;
    cin >> N;
    vector<string> strings(N);

    for (string &str : strings)
        cin >> str;

    const string &str = strings.front();
    trie trie(strings);

    cout << trie.find(str) << '\n';
}
