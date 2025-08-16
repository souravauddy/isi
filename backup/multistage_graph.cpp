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

constexpr static const int INF = int(1e9 + 5);

template<typename Type = int>
void output_vector(std::vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

constexpr static const int INF = int(1e9 + 5);

struct node {
    int vertex, weight;

    node(int _vertex = 0, int _weight = 0) : vertex(_vertex), weight(_weight) {}
};

std::vector<int> compute_cost(std::vector<std::vector<node>> &adjacency_list, int source, int destination) {
    const int vertices = int(adjacency_list.size());
    std::queue<int> queue;
    std::vector<int> cost(vertices, INF);

    cost[source] = 0;
    queue.push(source);

    while (!queue.empty()) {    // time complexity O(vertices + edges)
        int node = queue.front();
        queue.pop();

        for (auto &next : adjacency_list[node]) {
            cost[next.vertex] = std::min(cost[next.vertex], cost[node] + next.weight);
            queue.push(next.vertex);
        }
    }

    std::cout << cost[destination] << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int stages, vertices, edges, source, destination;
    std::cin >> stages >>  source >> destination >> vertices >> edges;
    std::vector<std::vector<int>> adjacency_matrix(vertices, std::vector<int>(vertices, 0));
    std::vector<std::vector<node>> adjacency_list(vertices);

    for (int e = 0; e < edges; e++) {
        int source, destination, weight;
        std::cin >> source >> destination >> weight;
        adjacency_matrix[source][destination] = weight;
        adjacency_list[source].emplace_back(destination, weight);
    }

    std::vector<int> cost(vertices, INF);
    std::queue<int> queue;

    cost[source] = 0;
    queue.push(source);

    while (!queue.empty()) {    // time complexity is O(vertices * vertices)
        int node = queue.front();
        queue.pop();

        for (int next = 0; next < vertices; next++) {
            if (adjacency_matrix[node][next]) {
                queue.push(next);
                cost[next] = std::min(cost[next], cost[node] + adjacency_matrix[node][next]);
            }
        }
    }

    std::cout << "cost = " << cost[destination] << '\n';
    
    std::vector<int> computed_cost = compute_cost(adjacency_list, source, destination);

    std::cout << "cost = " << cost[destination] << '\n';
}
