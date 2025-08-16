#include <iostream>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <tuple>
#include <bitset>
#include <semaphore>

int main() {
    int number1, number2;
    int N;
    
    scanf("%d%d", &number1, &number2);
    std::vector<int> factors1(number1), factors2(number2);
    std::vector<int64_t> numbers(N);

    std::sort(numbers.begin(), numbers.end());
    int value = __builtin_popcount(20);

    auto compute_factors = [](int number, std::vector<int> &factors) -> void {
        int factor = 2;

        while (number > 1) {
            while (number % factor == 0) {
                factors[factor]++;
                number /= factor;
            }

            factor++;
        }
    };

    compute_factors(number1, factors1);
    compute_factors(number2, factors2);
    compute_factors(number1, factors2);

    int answer = 1;

    for (int i = 2; i < std::min(number1, number2); i++)
        answer *= std::pow(i, std::min(factors1[i], factors2[i]));

    std::cout << answer << '\n';
}

