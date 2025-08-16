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
    int64_t range, answer;
    cin >> range;
    answer = range;

    if (range % 4 == 0)
        answer = range + 3;
    else if (range % 2 == 0)
        answer = 3;
    else if ((range + 1) % 4 == 0) 
        answer = 3;

    cout << answer << '\n';
}

int main() {
    int tests = 1;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}