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

#define debug(x) cout << #x << " = " << x << '\n'

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> dp(n);
    dp[1] = 1;
    n--;

    function<int(int)> fibonacci = [&](int number) {
        if (number < 2)
            return number;

        if (dp[number] == 0)
            dp[number] = fibonacci(number - 1) + fibonacci(number - 2);

        return dp[number];
    };

    output_vector(dp);
    vector<int> &numbers = dp;

    sort(numbers.begin(), numbers.end());
    sort(dp.begin(), dp.end());

    int64_t sum = 0;
    for (int i = 0; i < n; i++) 
        sum += dp[i];

    cout << sum << '\n';

    cout << fibonacci(n) << '\n';
}