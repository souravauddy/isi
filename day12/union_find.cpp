#include <iostream>
#include <cassert>
#include <vector>
#include <numeric>
#include <print>
#include <queue>
#include <sstream>
#include <functional>

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

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

struct union_find {  // union find using rank and path compression, only valid for un-directed graphs
    std::vector<int> parent, rank;
    int components = 0;

    union_find(int size) {
        parent.assign(size + 1, 0);
        rank.assign(size + 1, 1);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int vertex) {
        if (parent[vertex] == vertex)
            return vertex;
        return parent[vertex] = find(parent[vertex]);
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);

        if (a == b) 
            return false;

        if (rank[a] < rank[b])
            std::swap(a, b);

        parent[b] = parent[a];
        rank[a] += rank[b];
        components++;

        return true;
    }
};

void print_components(std::vector<std::vector<int>> &adjancency_list) {
    const int N = int(adjancency_list.size());
    std::vector<bool> visited(N, false);

    for (int node = 1; node < N; node++) {
        if (!visited[node]) {
            std::vector<int> component_nodes;
            std::queue<int> queue;
            queue.push(node);
            
            while (!queue.empty()) {
                int current_node = queue.front();
                visited[current_node] = true;
                component_nodes.push_back(current_node);
                queue.pop();

                for (int neighbor : adjancency_list[current_node]) {
                    if (!visited[neighbor])
                        queue.push(neighbor);
                }
            }

            std::print("{} ", component_nodes);
        }
    }

    std::println();
}

int main() {
    std::string line;
    std::getline(std::cin, line);
    int capacity = atoi(line.c_str());

    std::vector<std::vector<int>> adjancency_list(capacity + 1);
    union_find UF(capacity);

    while (std::getline(std::cin, line)) {
        std::string operation, string_node1, string_node2;
        std::stringstream in(line);
        in >> operation >> string_node1 >> string_node2;
        int node1 = atoi(string_node1.c_str()), node2 = atoi(string_node2.c_str());

        if (operation == "Union") {
            int connection_required = UF.unite(node1, node2);

            if (connection_required) {
                adjancency_list[node1].push_back(node2);
                adjancency_list[node2].push_back(node1);
            }

            print_components(adjancency_list);
        }
        
        if (operation == "Connected") {
            std::println("{}", UF.find(node1) == UF.find(node2) ? "Connected" : "Not Connected");
        }
    }
}
