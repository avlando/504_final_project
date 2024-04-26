#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Function to read words from file and store them in a vector
std::vector<std::string> readWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> words;
    std::string word;

    if (file.is_open()) {
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }

    return words;
}

// Function to generate a random number between min and max (inclusive)
int getRandomNumber(int min, int max) {
    static bool initialized = false;
    if (!initialized) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        initialized = true;
    }
    return min + std::rand() % ((max - min) + 1);
}

int main() {
    // Read words from file
    std::vector<std::string> words = readWordsFromFile("words.txt");

    // Check if there are words in the file
    if (words.empty()) {
        std::cerr << "No words found in the file." << std::endl;
        return 1;
    }

    // Generate a random index to pick a word from the vector
    int randomIndex = getRandomNumber(0, words.size() - 1);

    // Output the randomly chosen word
    std::cout << "Random word: " << words[randomIndex] << std::endl;

    return 0;
}
