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

struct Edge {
    int edge, capacity, flow;

    Edge(int _edge = 0, int _capacity = 0, int _flow = 0) : edge(_edge), capacity(_capacity), flow(_flow) {}
};

const int BACKWARD_EDGE_CAPACITY = int(0);
const int INF = int(1e9 + 5);

int main() {
    int vertices, edges;
    cin >> vertices >> edges;
    vector<vector<Edge>> adjacenct_list(vertices);

    for (int i = 0; i < edges; i++) {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        adjacenct_list[u].emplace_back(v, capacity);
        adjacenct_list[v].emplace_back(u, BACKWARD_EDGE_CAPACITY);
    }

    int source, sink;
    cin >> source >> sink;
    vector<bool> visited(vertices, false);
    int minimum = INF;
    int maximum_flow = 0;

    auto get_vertex = [&](int source, int destination) -> Edge& {
        assert(source >= 0 && source < vertices);
        assert(destination >= 0 && destination < vertices);

        for (auto &node : adjacenct_list[source])
            if (node.edge == destination)
                return node;
                
        assert(false);
    };

    auto dfs = y_combinator([&](auto self, int vertex) -> bool {
        if (vertex == sink) {
            return true;
        }

        visited[vertex] = true;
        bool found_sink = false, found_forward_edge = false;

        for (auto &node : adjacenct_list[vertex]) {
            if (!visited[node.edge] && node.capacity - node.flow > 0 && node.capacity > 0) {
                found_forward_edge = true;
                minimum = min(minimum, node.capacity - node.flow);
                found_sink = self(node.edge); 
            } 

            if (found_sink) {
                node.flow = node.flow + minimum;
                auto &backward_edge = get_vertex(node.edge, vertex);
                backward_edge.flow = backward_edge.flow - minimum;
                return true;
            }
        }

        if (!found_forward_edge) {
            for (auto &node : adjacenct_list[vertex]) {
                if (node.capacity == BACKWARD_EDGE_CAPACITY && !visited[node.edge] && node.capacity - node.flow > 0) {
                    minimum = min(minimum, abs(node.capacity - node.flow));
                    found_sink = self(node.edge);
                }

                if (found_sink) {
                    node.flow = node.flow - minimum;
                    auto &forward_edge = get_vertex(vertex, node.edge);
                    forward_edge.flow = forward_edge.flow - minimum;
                    return true;
                }
            }
        }

        return false;
    });

    while (dfs(source)) {
        maximum_flow += minimum;
        fill(visited.begin(), visited.end(), false);
        minimum = INF;
    }

    cout << "The maximum flow is " << maximum_flow << '\n';
}

/*
input:
4 5
0 1 100
1 3 100
0 2 100
2 3 100
1 2 1
0 3

Input:
6 7
0 1 10
1 2 25
2 5 10
4 1 6
4 5 10
3 4 15
0 3 10
0 5
*/