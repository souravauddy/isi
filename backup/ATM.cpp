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

void run_case() {
    int n, k;
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        
        if (a <= k) {
            cout << 1;
            k -= a;
        } else {
            cout << 0;
        }
    }

    cout << '\n';
}

int main() {
    int tests;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}