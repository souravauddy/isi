#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <print>

struct edge {
    int source, destination;
    double weight;
};

int main() {
    int vertices, edges;
    std::cin >> vertices >> edges;
    std::vector<edge> edge_list(edges);

    for (auto &edge : edge_list)
        std::cin >> edge.source >> edge.destination >> edge.weight;
    
    std::sort(edge_list.begin(), edge_list.end(), [](const edge &edge1, const edge &edge2) -> bool {
        return edge1.weight < edge2.weight;
    });

    for (const auto &edge : edge_list)
        std::println("{}, {}, {}", edge.source, edge.destination, edge.weight);
}
