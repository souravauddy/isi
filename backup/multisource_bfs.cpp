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

const int INF = int(1e9 + 5);

template<typename Type>
void output_vector(const vector<Type> &numbers, const bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int vertices, edges;
    cin >> vertices >> edges;
    vector<vector<int>> adjacency_list(vertices);

    for (int e = 0; e < edges; e++) {
        int u, v;
        cin >> u >> v;
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }

    int sources;
    cin >> sources;
    assert(sources > 0);    
    queue<int> queue;
    vector<bool> visited(vertices, false);
    vector<int> distance(vertices, INF);

    for (int s = 0; s < sources; s++) {
        int source;
        cin >> source;
        distance[source] = 0;
        visited[source] = true;
        queue.push(source);
    }

    int depth = 0;

    while (!queue.empty()) {
        int size = queue.size();

        for (int iter = 0; iter < size; iter++) {
            int node = queue.front();
            visited[node] = true;

            for (auto edge : adjacency_list[node])
                if (!visited[edge])
                    queue.push(edge);

            distance[node] = min(distance[node], depth);
            queue.pop();
        }

        depth++;
    }

    output_vector(distance);
}