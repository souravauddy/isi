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

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

void debug_out() {
    cerr << endl;
}

template<typename Type>
ostream& operator<<(ostream &os, const vector<Type> &other) {
    const int size = other.size();
    if (size <= 0) 
        return os << '[' << ']';
    os << '[';
    for (int i = 0; i < size - 1; i++) 
        os << other[i] << ", ";
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    cerr << " [" << head << ']';
    debug_out(args...);
}

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

template<typename Type>
void output_vector(vector<Type> &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

void run_case() {
    int N;
    string direction;
    cin >> N >> direction;
    vector<int> initial(N);

    for (int i = 0; i < N; i++) 
        initial[i] = direction[i] == 'L' ? i : N - i - 1;

    int64_t sum = accumulate(initial.begin(), initial.end(), 0LL);
    vector<int64_t> final(N);
    array<int, 2> dir;
    dir[0] = 0, dir[1] = N - 1;
    const int center = N / 2;

    debug(sum);

    for (int k = 0; k < N; k++) {
        bool changed = false;
        int64_t prev = sum;
        
        while (!changed && (dir[0] < center || dir[1] > center)) {
            if (dir[0] < center && (N - dir[0] - 1 > dir[1])) {
                if (direction[dir[0]] == 'L') {
                    changed = true;
                    sum += N - dir[0] - 1;
                    sum -= dir[0];
                    direction[dir[0]] = 'R';
                    dir[0]++;
                    break;
                }

                dir[0]++;
            } else {
                if (dir[1] >= center && direction[dir[1]] == 'R') {
                    changed = true;
                    sum += dir[1];
                    sum -= N - dir[1] - 1;
                    direction[dir[1]] = 'L';
                    dir[1]--;
                    break;
                }

                dir[1]--;
            }
        }

        final[k] = sum;
    }

    output_vector(final);
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef LOCAL
    cin.tie(nullptr);
#endif

    int tests;
    cin >> tests;

    while (tests-- > 0) {
        run_case();
    }
}