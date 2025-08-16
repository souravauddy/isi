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

template<typename Type>
void output_matrix(vector<vector<Type>> &matrix, int start = 0) {
    const int row = matrix.size();
    const int column = matrix[0].size();

    for (int i = start; i < row; i++) 
        for (int j = start; j < column; j++) 
            cout << setw(4) << matrix[i][j] << " \n"[j + 1 == column];
}

int main () {
    string A, B;
    cin >> A >> B;
    const int N = int(A.length()), M = int(B.length());

    vector<vector<int>> dp(N + 1, vector<int>(M + 1, 0));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                continue;
            }

            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    std::cout << "The common subsequence is = " << dp[N][M] << '\n';

    int Aindex = N, Bindex = M, common_subsequence_length = dp[N][M];
    string subsequence;

    while (common_subsequence_length > 0 && Aindex != 0 && Bindex != 0) {  
        if (A[Aindex - 1] == B[Bindex - 1]) {   
            subsequence.push_back(A[Aindex - 1]);
            common_subsequence_length--;
            Aindex--, Bindex--;
        } else if (dp[Aindex - 1][Bindex] > dp[Aindex][Bindex - 1]) {
            Aindex--;
        } else { 
            Bindex--;
        }
    }

    std::reverse(subsequence.begin(), subsequence.end());

    cout << (subsequence.empty() ? "There is no common subsequence present " : subsequence) << '\n';
}