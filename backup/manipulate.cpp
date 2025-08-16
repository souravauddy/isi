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
    int x, y;
    cin >> x >> y;
    
    if (y % x == 0) {
        cout << y / x - 1 << '\n';
        return;
    }

    cout << y / x << '\n';
}

int main() {
    int tests;
    cin >> tests;

    while (tests-- > 0)
        run_case();
}