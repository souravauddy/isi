#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <array>

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

const int DIRS = int(8);
const std::array<int, DIRS> ROW_DIR = {+1, +1, +1, 0, 0, -1, -1, -1};
const std::array<int, DIRS> COL_DIR = {+1, -1, 0, +1, -1, -1, +1, 0};

int main() {
    int M, N;
    std::cin >> M >> N;
    std::vector<std::vector<int>> matrix(M, std::vector<int>(N, 0));
    std::vector<std::vector<bool>> visited(M, std::vector<bool>(N, false));

    for (int m = 0; m < M; m++)
        for (int n = 0; n < N; n++)
            std::cin >> matrix[m][n];

    auto valid = [&](int row, int column) -> bool {
        return row >= 0 && row < M && column >= 0 && column < N;
    };

    auto dfs = y_combinator([&](auto self, int row, int column, int &count) -> void {
        if (!valid(row, column) || visited[row][column] || matrix[row][column] == 0)
            return;

        visited[row][column] = true;
        count++;

        for (int d = 0; d < DIRS; d++)
            self(row + ROW_DIR[d], column + COL_DIR[d], count);
    });

    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            if (!visited[m][n] && matrix[m][n] == 1) {
                int count_component_elements = 0;
                dfs(m, n, count_component_elements);
                std::cout << n << ' ' << m << ' ' << count_component_elements << '\n';
            }
        }
    }
}