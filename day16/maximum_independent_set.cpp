#include <functional>
#include <iostream>
#include <vector>
#include <queue>
#include <print>

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

constexpr const int SOURCE = int(0);

int main() {
    int vertices, edges;
    std::cin >> vertices >> edges;
    std::vector<std::vector<int>> adjancency_list(vertices);

    for (int e = 0; e < edges; e++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adjancency_list[u].push_back(v);
        adjancency_list[v].push_back(u);
    }

    /* dp1[i] - represents the maximum independent set rooted at the node 'i'. */
    /* dp2[i] - represents the maximum independent set of its children nodes. */

    std::vector<int> dp1(vertices, 1), dp2(vertices, 0);
    std::vector<bool> visited(vertices, false);

    y_combinator([&](auto dfs, const int node) -> void {
        visited[node] = true;

        for (const int child : adjancency_list[node]) {
            if (!visited[child]) {
                dfs(child);
                dp2[node] += dp1[child];
                dp1[node] += dp2[child];
            }
        }
        
        dp1[node] = std::max(dp1[node], dp2[node]);
    })(SOURCE);

    std::println("{}", dp1[SOURCE]);
}

/*
8 7
1 2
1 3
2 4
2 5
3 6
5 7
5 8
*/
