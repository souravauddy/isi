#include <iostream>
#include <print>
#include <vector>
#include <unordered_map>
#include <unordered_set>

int find_first_index(const std::vector<int> &numbers, const std::unordered_map<int, int> &frequency, std::unordered_map<int, int> &maximum_to_left, const int element) {
    if (!frequency.contains(element))
        return -1;

    const int candidate_index = maximum_to_left.at(element);
    return candidate_index == -1 ? -1 : numbers[candidate_index];
}

int main() {
    int N;
    std::cin >> N;
    std::vector<int> numbers(N);

    for (int &number : numbers)
        std::cin >> number;

    std::unordered_map<int, int> frequency, first_seen_index, maximum_to_left;

    for (int i = 0; i < N; i++)
        frequency[numbers[i]]++;
    
    std::unordered_set<int> seen;
    int maximum_frequency_element_index = 0, maximum_frequency = frequency.at(numbers.front());
    maximum_to_left[numbers.front()] = -1;
    seen.insert(numbers.front());

    for (int i = 1; i < N; i++) {
        if (!seen.contains(numbers[i]))
            maximum_to_left[numbers[i]] = maximum_frequency_element_index;

        if (frequency.at(numbers[i]) > maximum_frequency) {
            maximum_frequency = frequency.at(numbers[i]);
            maximum_frequency_element_index = i;
        }

        seen.insert(numbers[i]);
    }

    int element;
    std::cin >> element;

    std::println("{}", find_first_index(numbers, frequency, maximum_to_left, element));
}
