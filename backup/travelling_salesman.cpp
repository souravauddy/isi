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
    explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) { return fun_(ref(*this), std::forward<Args>(args)...); }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<decay_t<Fun>>(std::forward<Fun>(fun)); }

template<typename Type>
ostream& operator<<(ostream &os, const vector<Type> &other) {
    const int size = other.size();
    if (size <= 0) 
        return os << '{' << '}';
    os << '{';
    for (int i = 0; i < size - 1; i++)   
        os << other[i] << ", ";
    return os << other[size - 1] << '}';
}  

void debug_out() { cerr << endl; } 

template<typename Head, typename... Tail> void debug_out(Head head, Tail... args) { cerr << " [" << head << ']'; debug_out(args...); }

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

template<typename Type>
void output_matrix(const vector<vector<Type>> &matrix) {  
    const int row = matrix.size();
    const int column = matrix[0].size();

    for (int i = 0; i < row; i++) 
        for (int j = 0; j < column; j++) 
            cout << matrix[i][j] << " \n"[j + 1 == column];
}

const int INF = int(1e9) + 5;

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

string binary(int64_t number) {
    string binary = "";

    while (number) {
        binary = to_string(number & 1) + binary;
        number >>= 1;
    }

    return binary;
}

int main() {
    int vertices;
    cin >> vertices;
    vector<vector<int>> adjacency_matrix(vertices, vector<int>(vertices, 0));

    for (int i = 0; i < vertices; i++) 
        for (int j = 0; j < vertices; j++) {
            cin >> adjacency_matrix[i][j];  

            if (i != j && adjacency_matrix[i][j] == 0)
                adjacency_matrix[i][j] = INF;
        }

    const int ALL_VISITED = (1 << vertices) - 1;
    vector<int> path(vertices, 0);
    vector<int> best_path;
    vector<vector<int>> dp(vertices + 1, vector<int>(1 << (1 + vertices), INF));
    int best = INF;
    int repetitions = 0;

    auto get_cost = y_combinator([&](auto self, vector<int> &path, int64_t visited, int vertex, int64_t cost, int index) -> int {
        visited |= 1 << vertex;
        path[index] = vertex;

        if (visited == ALL_VISITED) {
            int previous = best;
            best = min<int64_t>({best, 2 * cost, cost + adjacency_matrix[path.back()][0]});

            if (best != previous)
                best_path = path;

            return best;
        }

        if (dp[vertex][visited] < INF) {
            debug(vertex, binary(visited));
            repetitions++;
            return dp[vertex][visited];
        }

        int minimum = INF;

        for (int v = 0; v < vertices; v++) {
            auto weight = adjacency_matrix[vertex][v];

            if (weight && weight != INF && !((visited >> v) & 1)) {  // if weight is 0 that means that there is no edge between the vertex
                int travelling_cost = self(path, visited, v, cost + weight, index + 1);
                minimum = min(minimum, travelling_cost);
            } 
        }

        dp[vertex][visited] = minimum;

        return minimum;
    });

    debug(repetitions);

    for (int vertex = 0; vertex < vertices; vertex++) {
        best = min(best, get_cost(path, 0LL, vertex, 0LL, 0));
    }

    cout << '\n';
    cout << "The optimal cost is " << (best >= INF ? "INF" : to_string(best)) << '\n';
    output_vector(best_path);
}

/*
input:
4
0 10 15 20
10 0 35 25 
15 35 0 30
20 25 30 0

4
0 10 15 20
10 0 0 25 
15 35 0 30
20 0 30 0

4
0 10 20 94 
0 0 0 0
0 0 0 0
20 0 0 0 

5
0 49 29 599 5
29 0 299 5 2
29 595 0 95 5
29 49 294 0 2
49 92 95 92 0

10
000 374 200 223 108 178 252 285 240 356
374 000 255 166 433 199 135 095 136 017
200 255 000 128 277 128 180 160 131 247
223 166 128 000 430 047 052 084 040 155
108 433 277 430 000 453 478 344 389 423
178 199 128 047 453 000 091 118 064 181
252 135 180 052 478 091 000 114 083 117
285 095 160 884 344 110 114 000 047 078
240 136 131 040 389 064 083 047 000 118
356 017 247 155 423 181 117 078 118 000


4
0 4 1 3
4 0 2 1
1 2 0 5
3 1 5 0

5
0 0 0 0 0
0 0 10 15 20
0 10 0 25 25
0 15 25 0 30
0 20 25 30 0
*/