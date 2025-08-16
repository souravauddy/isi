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
#include <queue>
#include <stack>
#include <climits>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>
#include <type_traits>

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

int main() {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);  
#endif

    int N;
    std::cin >> N;
    std::vector<int> connections(N);

    for (int &connection : connections)
        std::cin >> connection;

    int node1, node2;
    std::cin >> node1 >> node2;
    
    auto bfs = [&](int source) -> std::vector<int> {
        std::queue<int> queue;
        std::vector<int> traversal;
        std::vector<bool> visited(N, false);

        queue.push(source);

        while (!queue.empty()) {
            int node = queue.front();
            visited[node] = true;
            traversal.push_back(node);
            queue.pop();

            if (connections[node] != -1 && !visited[connections[node]])
                queue.push(connections[node]);
        }

        return traversal;
    };

    std::vector<int> traversal_source_1 = bfs(node1);
    std::vector<int> traversal_source_2 = bfs(node2);
    std::vector<int> common_nodes;
    std::set<int> nodes_from_source1(traversal_source_1.cbegin(), traversal_source_1.cend());
    std::set<int> nodes_from_source2(traversal_source_2.cbegin(), traversal_source_2.cend());

    std::set_intersection(nodes_from_source1.cbegin(), nodes_from_source1.cend(), nodes_from_source2.cbegin(), nodes_from_source2.cend(), std::back_inserter(common_nodes));

    std::unordered_set<int> common_nodes_set(common_nodes.cbegin(), common_nodes.cend());
    std::unordered_map<int, int> common_nodes_with_added_distance;

    auto update_map = [&](const std::vector<int> &traversal) -> void {
        for (int i = 0; i < traversal.size(); i++)
            if (common_nodes_set.find(traversal[i]) != common_nodes_set.end())
                common_nodes_with_added_distance[traversal[i]] += i + 1;
    };

    update_map(traversal_source_1);
    update_map(traversal_source_2);

    std::vector<std::pair<int, int>> sorted_common_nodes(common_nodes_with_added_distance.cbegin(), common_nodes_with_added_distance.cend());

    std::stable_sort(sorted_common_nodes.begin(), sorted_common_nodes.end(), [](const auto &a, const auto &b) -> bool {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
    });

    std::cout << (sorted_common_nodes.empty() ? -1 : sorted_common_nodes[0].first) << '\n';
}
