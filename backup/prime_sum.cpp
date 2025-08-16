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

void run_case() {
    int64_t a, b; 
    cin >> a >> b; 
    
    if (a == 1 || b == 1) {
        cout << -1 << '\n';
        return;
    }

    if (__gcd(a, b) > 1) {
        cout << 0 << '\n';
        return;
    }

    cout << 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests = 1;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }   
}

/*
5
2 94
29 4
2 4
2 5
1 24
*/