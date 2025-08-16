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
#include <cstdlib>
#include <set>
#include <queue>
#include <stack>
#include <climits>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>

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

struct node {
    int indegree, vertex, sum;

    node() = default;

    node(int _vertex = 0, int _indegree = 0, int _sum = 0) : vertex(_vertex), indegree(_indegree), sum(_sum) {}

    [[nodiscard]]
    constexpr auto operator<=>(const node &) const = default;
};

[[nodiscard]]
inline int get_answer(int answer) {
    return answer ? answer : -1;
}

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

    std::vector<int> indegree(N);

    for (int node = 0; node < N; node++)
        if (connections[node] != -1)
            indegree[connections[node]]++;

    std::vector<node> nodes;

    for (int vertex = 0; vertex < N; vertex++)
        nodes.emplace_back(vertex, indegree[vertex], vertex);

    std::sort(nodes.begin(), nodes.end());

    for (int vertex = 0; vertex < N; vertex++) {
        const node &current_node = nodes[vertex];
        nodes[connections[current_node.vertex]].sum += current_node.sum;
    }

    std::cout << get_answer(int(std::max_element(nodes.begin(), nodes.end(), [](const node &a, const node &b) -> bool {
        return a.sum < b.sum;
    }) - nodes.begin())) << '\n';
}
