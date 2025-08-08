#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <sstream>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <climits>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <memory>

// using namespace std;

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
    std::cerr << std::endl;
}

template<typename Type>
std::ostream& operator<<(std::ostream &os, const std::vector<Type> &other) {
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
    std::cerr << " [" << head << ']';
    debug_out(args...);
}

#ifdef LOCAL
#define debug(...) std::cerr << '(' <<  #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

// REMINDER: remember when outputing vectors there is a double double "[]" parenthesis

struct term {
    static const char MIN_CHAR = char('a');
    int co_efficient;
    std::vector<int> power;

    term() = default;

    term(int co_efficient, const std::vector<int> &power) {
        this->co_efficient = co_efficient;
        this->power.resize(power.size());
        std::copy(power.begin(), power.end(), this->power.begin());
    }

    term operator*(const term &other) const {
        term new_term;
        new_term.co_efficient = co_efficient * other.co_efficient;
        
        for (int i = 0; i < power.size(); i++)
            new_term.power[i] = power[i] + other.power[i];

        return new_term;
    }

    friend std::ostream& operator<<(std::ostream &os, const term &other) noexcept {
        os << other.co_efficient;

        for (int i = 0; i < other.power.size(); i++) {
            if (!other.power[i]) 
                continue;

            os << char(MIN_CHAR + i)  << (other.power[i] > 1) ? os << '^' << other.power[i] : os << other.power[i];
        }
        
        return os;
    }
};

using terms = term;

struct polynomial {
    std::vector<terms> polynomial_terms;

    polynomial() = default;

    polynomial(int number_of_terms) {
        this->polynomial_terms.reserve(number_of_terms);
    }

    polynomial(std::map<std::vector<int>, int> &other) {
        for (const auto &[power, co_efficient] : other) {
            this->polynomial_terms.emplace_back(co_efficient, power);
        }
    }
    
    int size() const {
        return int(polynomial_terms.size());
    }

    term& operator[](int index) {
        return this->polynomial_terms[index];
    }

    const term& operator[](int index) const {
        return this->polynomial_terms[index];
    }

    polynomial operator*(const polynomial &other) {
        std::map<std::vector<int>, int> product;

        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < other.size(); i++) {
                term product_term = (*this)[i] * other[j];
                product[product_term.power] += product_term.co_efficient;
            }
        }

        return polynomial(product);    
    }

    void operator*=(const polynomial &other) {
        (*this) = (*this) * other;
    }

    polynomial pow(int power) {
        polynomial result;

        while (power > 0) {
            if (power & 1)
                result = result * (*this);

            (*this) = (*this) * (*this);
            power >>= 1;
        }

        return result;
    }

    friend std::ostream& operator<<(std::ostream &os, const polynomial &other) noexcept {
        for (int i = 0; i < other.polynomial_terms.size(); i++)
            os << other[i] << " + ";
        
        return os;
    }
};

void inputpolynomial_terms(polynomial &polynomial) {
    
}

int main(const int argc, const char **argv) {
    std::ios_base::sync_with_stdio(false);
#ifndef LOCAL
    std::cin.tie(nullptr);
#endif
    
    int number_of_terms;
    std::cin >> number_of_terms;
    polynomial polynomial1(number_of_terms), polynomial2(number_of_terms);

    inputpolynomial_terms(polynomial1);
    inputpolynomial_terms(polynomial2);

    std::cout << polynomial1 * polynomial2 << '\n';
    std::cout << polynomial1.pow(2) << '\n';
}
