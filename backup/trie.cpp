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

const int ALPHABET = int(26);
const char MIN_CHAR = char('a');


struct node {
    bool last_node;
    vector<node *> edges;   // using pointers saves significant amount of memory

    node() {
        last_node = true;
        edges.assign(ALPHABET, nullptr);
    }

    bool contains(char character) {
        return edges[character - MIN_CHAR] != nullptr;
    }

    node * add(char character) {
        int index = int(character - MIN_CHAR);
        node *new_node = new node();
        edges[index] = new_node;
        last_node = false;
        return edges[index];
    }

    node * next(char character) {
        int index = int(character - MIN_CHAR);
        assert(edges[index] != nullptr);
        return edges[index];
    }
};

struct trie {
    node ROOT, *iterator;

    trie() {
        ROOT = node(); // this is the starting node
        iterator = nullptr;
    }

    void add(const string &str) {
        iterator = &ROOT;

        for (char c : str) {
            if (!iterator->contains(c)) { 
                iterator = iterator->add(c);
                continue;
            }

            iterator = iterator->next(c);
        }
    }

    bool find(const string &str) {
        iterator = &ROOT;

        for (char c : str) {
            if (!iterator->contains(c))
                return false;

            iterator = iterator->next(c);
        }

        assert(iterator != nullptr);
        return iterator->last_node;
    }

    void bfs() {    // update this code as required
        iterator = &ROOT;
        queue<node *> queue;
        queue.push(iterator);

        while (!queue.empty()) {    // this is linear time
            int size = queue.size();

            while (size--) {
                node *n = queue.front();
                queue.pop();

                for (int i = 0; i < ALPHABET; i++) {
                    if (n->edges[i]) {
                        cout << char(MIN_CHAR + i) << ' ';
                        queue.push((n->edges[i]));
                    }
                }
            }
        }
    }
};

// this is bad implementation for competitive programming, don't use this implementation, better implementation improved_trie.cpp, saw from codechef stream on trie's.

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

    trie trie;

    for (const string &str : strings)
        trie.add(str);

    trie.bfs();

    cout << trie.find(strings.back()) << '\n';
}