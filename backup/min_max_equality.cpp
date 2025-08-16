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

vector<int64_t> factorial(20);

void preprocess() {
    factorial[0] = 1;

    for (int i = 1; i < 22; i++) {
        factorial[i] = i * factorial[i - 1];
    }
}

void run_case() {
    int n, k;
    cin >> n >> k;
    vector<int> numbers(n);
    map<int, int> frequency;

    auto permuation = [&](int64_t value) -> int64_t {
        if (value - 2 <= 0) {
            return (int64_t) factorial[value];
        }

        return int64_t(factorial[value] / factorial[value - 2]);
    };
    
    for (int &x : numbers) {
        cin >> x;
        frequency[x]++;
    }

    int64_t answer = 0;
    for (auto &freq : frequency)
        cout << freq.first << ' ' << freq.second << '\n';
    cout << '\n';

    cout << answer << '\n'; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    preprocess();

    int tests = 1;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }   
}

/*
3
3 1
1 2 3
4 2
3 3 3 1
5 1
1 1 1 2 4
1 3 1 2 4 -> 4 + 1 = 5
1 1 3 2 4
*/