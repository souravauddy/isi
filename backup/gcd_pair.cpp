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

ostream& operator<<(ostream &os, pair<int, int> &value) {
    return os << value.first << ' ' << value.second;
}

void run_case() {
    int a, b;
    cin >> a >> b;

    if (a + 2 > b) {
        cout << -1 << '\n';
        return;
    }

    if (a % 2 == 0) {
        cout << a << ' ' << a + 2 << '\n';
        return;
    } 

    int number = a + 1;
    while (number <= b && number <= a + 5 && __gcd(number, a) < 2)
        number++;

    int candidate1 = a + a + 4;
    int candidate2 = number + a;

    if (candidate1 == candidate2) {
        if (number > b && a + 3 > b) {
            cout << -1 << '\n';
            return;
        }

        int Min = min(number, a + 3);
        if (Min > b) {
            cout << -1 << '\n';
            return;
        }

        if (Min == number) {
            cout << a << ' ' << number << '\n';  
        } else {
            cout << a + 1 << ' ' << a + 3 << '\n';
        }
        return;
    }

    if (candidate1 < candidate2) {
        if (a + 3 > b) {
            return;
        }

        cout << a + 1 << ' ' << a + 3 << '\n';
        return;
    }

    if (number > b) {
        // debug(a);
        // debug(b);
        // debug(number);
        cout << -1 << '\n';
        return;
    }

    assert(number <= b);
    cout << a << ' ' << number << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;

    while (tests-- > 0)
        run_case();
}

/*
13
19 22
23 27
25 29
33 34
9 12
1 3
2 4
2 8
3 5
3 9
15 17
20 21
25 27


*/