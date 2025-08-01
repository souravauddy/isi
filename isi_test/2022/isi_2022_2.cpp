#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <iomanip>

int main() {
    std::vector<std::string> inputs;
    std::string line;
    std::set<char> roman_letters;

    for (char c = 'a'; c <= 'z'; c++) {
        roman_letters.insert(c);
        roman_letters.insert(toupper(c));
    }

    while (std::getline(std::cin, line))
        inputs.push_back(line);

    for (std::string &line : inputs)
        for (char &c : line)
            c = tolower(c);
   
    for (auto line : inputs) {
        std::map<std::string, int> frequency;
        
        for (int i = 0; i < line.size() - 1; i++)
            if (roman_letters.contains(line[i]) && roman_letters.contains(line[i + 1]))
                frequency[std::string({line[i], line[i + 1]})]++;
        
        for (auto [bigram, count] : frequency)
            std::cout << bigram << ' ' << count << '\n';
    }
}