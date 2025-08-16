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
        os << other[i] << ' ';
    return os << other[size - 1] << ']';
}   

template<typename Head, typename... Tail>
void debug_out(Head head, Tail... args) {
    cerr << " [" << head << ']';
    debug_out(args...);
}

template<typename Type>
void output_matrix(const vector<vector<Type>> &matrix) {  
    const int row = matrix.size();
    const int column = matrix[0].size();

    for (int i = 0; i < row; i++) 
        for (int j = 0; j < column; j++) 
            cout << matrix[i][j] << " \n"[j + 1 == column];
}

template<typename T_vector>
void output_vector(T_vector &numbers, bool add_one = false) {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] + add_one << " \n"[i + 1 == numbers.size()];
    }
}

#define debug(...) cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)

const double EPSILON = double(1e-6);

int main() {    // this solution works for any number of variables and any number of equations
    int row, column;
    cin >> row >> column;   // row denotes the number of equations, column denotes the number of variables 
    vector<vector<double>> coefficent_matrix(row, vector<double>(column, 0));
    long double trace = 0, sum = 0;

    if (row < column) {
        cout << "The solution cannot be found" << '\n';
        return 0;
    }

    assert(row == column);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cin >> coefficent_matrix[i][j];

            if (i == j) {
                trace += coefficent_matrix[i][i];
            } else {
                sum += coefficent_matrix[i][j];
            }
        }
    }

    output_matrix(coefficent_matrix);   // this is the coefficient matrix

    // assert(sum <= trace);   // this is a necessary condition for the problem

    vector<double> solution(row, 0);   
    for (auto &s: solution) {
        cin >> s;
    }

    const int N = column;
    vector<double> initial(N, 0);
    vector<double> intermediate(N, 0);
    vector<double> computed(N, 0);

    auto sufficient = [&]() -> bool {
        for (int i = 0; i < N; i++) 
            if (abs(computed[i] - intermediate[i]) < EPSILON)
                return false;
                
        return true;
    };

    while (true) {
        for (int i = 0; i < row; i++) {
            double computed_value = 0;

            for (int j = 0; j < column; j++) 
                if (i != j)
                    computed_value = computed_value - coefficent_matrix[i][j] * initial[j];

            computed_value += solution[i];
            computed[i] = (double) computed_value / coefficent_matrix[i][i];
            intermediate[i] = initial[i];
            initial[i] = computed[i];
        }   

        if (!sufficient())
            break;

        intermediate = computed;
    }

    output_vector(computed);
}

/*
4 4
9.17 3.62 -1.68 -2.26
1.44 6.95 -2.14 1.86
2.32 1.95 -8.27 1.58
3.21 -0.86 2.42 -7.20

3 
4 1 2
3 5 1
1 1 3
4 7 3

5.21 1.42 2.16 3.28

ax + by + cz = k
x = k + (-cz - by) / a
y = k + (-cz - ax) / b
*/