#include <unordered_set>
#include <iostream>
#include <vector>
#include <print>

int main() {
    int N, sum = 0;
    std::cin >> N;
    std::vector<int> numbers(N);
    std::unordered_set<int> dp;

    for (int &number : numbers) {
        std::cin >> number;
        sum += number > 0 ? number : 0;
    }

    for (int number : numbers) {
        std::vector<int> possible_sums(dp.begin(), dp.end());

        for (int possible_sum : possible_sums)
            dp.insert(possible_sum + number);
        
        dp.insert(number);
    }

    int missing_positive_number = sum + 1;

    for (int number = 1; number < sum + 1; number++) {
        if (!dp.contains(number)) {
            missing_positive_number = number;
            break;
        }
    }
    
    std::println("The missing number is {}", missing_positive_number);
}
