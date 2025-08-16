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

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;
    vector<vector<int>> adjacency_list(vertices);

    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }

    vector<int> vertex_colour(vertices);
    vector<bool> visited(vertices, false);
    set<int> colours;
    int source, colour = 0;     
    cin >> source;

    auto get_colour = [&](int vertex) -> int {
        set<int> bad_colours;
        int need_colour;

        for (int node : adjacency_list[vertex])
            if (visited[node]) {
                bad_colours.insert(vertex_colour[node]);
            }

        if (bad_colours.size() == colours.size()) {
            colours.insert(colour);
            need_colour = colour++;
        } else {
            for (auto colour : colours)
                if (bad_colours.find(colour) == bad_colours.end()) {
                    need_colour = colour;
                    break;
                }
        }

        return need_colour;
    };

    y_combinator([&](auto Dfs, int vertex) -> void {
        visited[vertex] = true;
        vertex_colour[vertex] = get_colour(vertex);

        for (int node : adjacency_list[vertex]) 
            if (!visited[node])
                Dfs(node);
    })(source);

    output_vector(vertex_colour);
    cout << "The chromatic number is " << colours.size() << '\n';
}

/*
4 5
0 1
1 2
3 1
2 3
0 3
0
*/