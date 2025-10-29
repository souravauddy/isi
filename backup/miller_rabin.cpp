#include <iostream>
#include <print>

int binpow(int base, int power, const int MOD) {
    int result = 1;

    while (power > 0) {
        if (power & 1)
            result = ((int64_t) result * base) % MOD;

        base = ((int64_t) base * base) % MOD;
        power >>= 1;
    }

    return result;
}

bool composite_number(const int number, const int base, const int r, const int d) {
    int candidate = binpow(base, d, number);

    if (candidate == 1 || candidate == number - 1)
        return false;

    for (int s = 0; s < r - 1; s++) {
        candidate = ((int64_t) candidate * candidate) % number;

        if (candidate == number - 1)
            return false;
    }

    return true;
}

bool miller_rabin(const int number) {
    if (number < 2 || (number > 2 && number % 2 == 0))
        return false;
    
    const int r = std::countr_zero<uint32_t>(number - 1), d = (number - 1) >> r;

    for (const int base : {2, 3, 5, 7}) {
        if (number == base)
            return true;

        if (composite_number(number, base, r, d))
            return false;
    }

    return true;
}

int main() {
    int number;
    std::cin >> number;

    std::println("{}", miller_rabin(number));
}
