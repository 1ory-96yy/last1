#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

std::string cleanWord(const std::string& word) {
    std::string cleaned_word;
    for (char c : word) {
        if (isalpha(c) || c == '-') {
            cleaned_word += tolower(c);
        }
    }
    return cleaned_word;
}

int main() {
    std::string filename = "input.txt";
    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return 1;
    }

    std::map<std::string, int> word_freq;

    std::string word;
    while (input_file >> word) {
        std::string cleaned_word = cleanWord(word);

        if (!cleaned_word.empty()) {
            word_freq[cleaned_word]++;
        }
    }

    input_file.close();

    std::ofstream output_file("output.txt");
    if (!output_file.is_open()) {
        std::cerr << "Cannot open output file." << std::endl;
        return 1;
    }

    output_file << "Frequency dictionary:\n";
    for (const auto& pair : word_freq) {
        output_file << pair.first << " : " << pair.second << "\n";
    }

    auto most_frequent_word = std::max_element(
        word_freq.begin(), word_freq.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second < b.second;
        }
    );

    if (most_frequent_word != word_freq.end()) {
        output_file << "\nMost frequent word: " << most_frequent_word->first
            << " (used " << most_frequent_word->second << " times)\n";
    }

    output_file.close();

    std::cout << "Results have been written to output.txt\n";

    return 0;
}
