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

constexpr static const int MAX_VERTICES = int(1e5 + 5);

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int edges, vertices;
    std::cin >> edges >> vertices;
    std::vector<std::vector<int>> adjacency_list(vertices);

    for (int e = 0; e < edges; e++) {
        int source, destination;
        std::cin >> source >> destination;
        adjacency_list[source].push_back(destination);
        adjacency_list[destination].push_back(source);
    }

    std::unordered_set<int> articulation_points;
    std::vector<bool> visited(vertices);
    std::vector<int> discovery_time(vertices), lowest_time(vertices);
    int parent_root_count = 0, current_time = 0;

    y_combinator([&](auto dfs, const int node, const int parent) -> void {
        visited[node] = true;
        discovery_time[node] = lowest_time[node] = current_time++;
        parent_root_count += parent == 0;

        for (const int vertex : adjacency_list[node]) {
            if (vertex == parent)
                continue;

            if (visited[vertex]) {
                lowest_time[node] = std::min(lowest_time[node], discovery_time[vertex]);
                continue;
            }

            dfs(vertex, node);

            if (parent == -1)
                continue;

            lowest_time[node] = std::min(lowest_time[node], lowest_time[vertex]);

            if (lowest_time[vertex] >= discovery_time[node])
                articulation_points.insert(node);
        }
    })(0, -1);

    if (parent_root_count > 1)
        articulation_points.insert(0);

    for (const int point : articulation_points)
        std::cout << point << '\n';
}
