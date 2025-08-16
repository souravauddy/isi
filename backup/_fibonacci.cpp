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
#include <ext/pb_ds/assoc_container.hpp>

#define debug(x) cerr << #x << " = " << x << '\n'

using namespace std;
using namespace __gnu_pbds;

using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false, int start = -1, int end = -1) {
    if (start == -1) start = 0;
    if (end == -1) end = numbers.size() - 1;

    for (int i = start; i <= end; i++) {
        cout << numbers[i] + add_one << "\n "[i < end];
    }
}

int main() {
    int term;
    cin >> term;
    vector<int> dp(term);  
    term--;
    dp[1] = 1;

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cout << rng() << '\n';
    uniform_int_distribution<int> distribute(20, 200);

    auto random_int = [&]() {
        return distribute(rng);
    };

    cout << random_int() << '\n';
    return 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                for (int l = 0; l < n; l++) 
                    for (int g = 0; g < n; g++)
                        for (int t = 0; t < n; t++) 
                            for (int z = 0; z < n; z++) 
                                for (int x = 0; x < n; x++) 

    function<int(int)> fibonacci = [&](int number) -> int {
        if (number == 0)
            return 0;

        if (number == 1)
            return 1;

        if (dp[number] == 0)
            dp[number] = fibonacci(number - 1) + fibonacci(number - 2);

        return dp[number]; 
    };

    cout << fibonacci(term) << '\n';
    output_vector(dp);
}   