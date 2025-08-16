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
#include <mutex>
#include <semaphore>

using namespace __gnu_pbds;
using namespace std;

struct check {
    int something;

    check() {}
    
    check(auto&&) : something(20) {}

    check operator=(check &&other) {
        *this = std::move(other);
    }

    check operator|(const check &other) {
        check new_check(*this);
        new_check.something = this->something | other.something;
        return new_check;
    }
};

int main() {
    if (cout) {
        cout << "this is a true" << '\n';
    }

    int64_t sum = 0, a = 0;
    check check;
    check = check | check;

    std::cout << check.something << '\n';

    cout << a << '\n';
}

/*
input:
9
4qVjygF9ERv 
9NNiy7zdtFN 
3qXwn@BQNjs 
6sTMу4ZwGxC 
71GXhFVLUBA 
5uy1671SbPg 
8SKHU6evJtd
*/
