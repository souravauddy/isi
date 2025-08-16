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
    int n, m;
    cin >> n >> m;

    cout << ((n * m) & 1 ? "NO" : "YES") << '\n';
}

int main() {
    int tests;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}