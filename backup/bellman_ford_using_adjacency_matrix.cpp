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

const int INF = int(1e9 + 5);

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    int vertices;
    cin >> vertices;
    vector<vector<int>> adjacency_matrix(vertices, vector<int>(vertices, 0));

    for (int u = 0; u < vertices; u++) 
        for (int v = 0; v < vertices; v++) {
            cin >> adjacency_matrix[u][v];

            if (adjacency_matrix[u][v] == 0)
                adjacency_matrix[u][v] = INF;
        }

    int source;
    cin >> source;
    vector<int> distance(vertices, INF);
    distance[source] = 0;

    for (int iter = 0; iter < vertices; iter++) 
        for (int i = 0; i < vertices; i++) 
            for (int j = 0; j < vertices; j++) 
                if (adjacency_matrix[i][j] != INF) 
                    distance[j] = min(distance[j], distance[i] + adjacency_matrix[i][j]);

    for (int i = 0; i < vertices; i++) 
        for (int j = 0; j < vertices; j++) 
            if (distance[i] + adjacency_matrix[i][j] < distance[j]) {
                cout << "The graph contains a negative edge cycle" << '\n';
                return 0;
            }
          
    output_vector(distance);
}