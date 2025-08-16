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

#define debug(x) cerr << #x << " = " << x << '\n'

const int INF = int(1e9 + 5);

template<typename Type>
void output_matrix(vector<vector<Type>> &matrix, int start = 0) {
    const int row = matrix.size();
    const int column = matrix[0].size();

    for (int i = start; i < row; i++) 
        for (int j = start; j < column; j++) 
            cout << setw(4) << (matrix[i][j] == INF ? "INF" : to_string(matrix[i][j])) << " \n"[j + 1 == column];
}

struct Item {
    int profit;
    int weight;

    Item(int _profit = 0, int _weight = 0) : profit(_profit), weight(_weight) {}
    
    bool operator<(const Item &other) {
        return profit < other.profit;
    }
};

int main() {
    cout << "Enter the number of items" << '\n';
    int n;
    cin >> n;
    vector<Item> items(n + 1);

    cout << "Enter the profit and the weight of the items" << '\n';
    for (int i = 1; i <= n; i++)
        cin >> items[i].profit >> items[i].weight;

    cout << "Enter the knapsack capacity" << '\n';
    int capacity;
    cin >> capacity;

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= capacity; j++) {
            dp[i][j] = max(dp[i - 1][j], items[i].profit + dp[i - 1][max(0, j - items[i].weight)]);
        }
    }

    output_matrix(dp);
    cout << "The max profit is: " << dp[n][capacity] << '\n';
}

/*
4
20 1
30 3
10 4
50 6
10

6
5 20
3 30
3 30
2 50
4 60
2 70
13

3
60 20
100 30
120 40
50

A modified input f strings

for x in range(n):
    for y in range(n):
        print(x, y)
*/