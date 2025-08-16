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

struct strongly_connected_components {
    std::vector<std::vector<int>> adjacency_list, components;
    int vertices;

    strongly_connected_components() = default;

    strongly_connected_components(std::vector<std::vector<int>> &_adjacency_list) : adjacency_list(_adjacency_list), vertices(_adjacency_list.size()) {}

    void build() noexcept {
        std::stack<int> traversal_order = topological_sort(adjacency_list);
        
        reverse_list(adjacency_list);

        std::vector<bool> visited(vertices);
        std::vector<int> component;

        auto dfs = y_combinator([&](auto self, int node) -> void {
            component.push_back(node);
            visited[node] = true;

            for (int vertex : adjacency_list[node])
                if (!visited[vertex])
                    self(vertex);
        });

        while (!traversal_order.empty()) {
            const int node = traversal_order.top();
            traversal_order.pop();

            if (!visited[node]) {
                dfs(node);
                components.push_back(component);
                component.clear();
            }
        }
    }

    void add_edge(int source, int destination) noexcept {
        adjacency_list[source].push_back(destination);
    }

    [[nodiscard]]
    size_t count() const {
        return components.size();
    }

    [[nodiscard]]
    auto get_components() const {
        return components;
    }

    void reverse_list(std::vector<std::vector<int>> &adjacency_list) noexcept {
        std::vector<std::vector<int>> reverse_adjacency_list(vertices);

        for (int vertex = 0; vertex < vertices; vertex++)
            for (int node : adjacency_list[vertex])
                reverse_adjacency_list[node].push_back(vertex);

        adjacency_list = std::move(reverse_adjacency_list);
    }

    [[nodiscard]]
    std::stack<int> topological_sort(auto &adjancency_list) const {
        std::vector<bool> visited(vertices);
        std::stack<int> sorted_vertices;
        int index = vertices - 1;

        auto dfs = y_combinator([&](auto dfs, int node) -> void {
            visited[node] = true;

            for (auto vertex : adjacency_list[node])
                if (!visited[vertex]) 
                    dfs(vertex);

            sorted_vertices.push(node);
        });

        for (int node = 0; node < vertices; node++)
            if (!visited[node])
                dfs(node);

        return sorted_vertices;
    }
};

int main(const int argc, const char **argv, const char **envp, const char **apple) {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int vertices, edges;
    std::cin >> vertices >> edges;
    std::vector<std::vector<int>> adjacency_list(vertices);

    for (int e = 0; e < edges; e++) {
        int source, destination;
        std::cin >> source >> destination;
        adjacency_list[source].push_back(destination);
    }

    strongly_connected_components SCC(adjacency_list);
    SCC.build();

    std::cout << SCC.count() << '\n';
}
