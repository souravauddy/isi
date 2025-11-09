#include <iostream>
#include <sstream>
#include <vector>
#include <print>
#include <array>

int main() {
    std::string string_vertices;
    std::getline(std::cin, string_vertices);
    int vertices = atoi(string_vertices.c_str());
    std::string line;
    std::vector<std::vector<int>> adjacency_list(vertices);

    for (int v = 0; std::getline(std::cin, line); v++) {
        std::stringstream in(line);
        std::string string_neighbor, _;
        in >> _;

        while (in >> string_neighbor)
            adjacency_list[v].push_back(atoi(string_neighbor.c_str()));
    }
    
    std::vector<std::array<int, 2>> edge_list;

    for (int v = 0; v < vertices; v++) {
        for (const int neighbor : adjacency_list[v])
            if (v < neighbor)
                edge_list.push_back({v, neighbor});
    }

    std::println("{}", edge_list);
}
