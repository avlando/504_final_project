#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

/**
 * @brief Converts a given string to uppercase.
 *
 * This function takes a reference to a std::string object and transforms each
 * character in the string to its uppercase equivalent using std::toupper.
 *
 * @param input The string to be converted to uppercase.
 *
 * @throws None
 */
void capitalize(std::string &input)
{
    std::transform(input.begin(), input.end(), input.begin(), []
                   (unsigned char c) { return std::toupper(c); });
}

/**
 * @brief Checks if a given word is a valid 5-letter word consisting of uppercase letters only.
 *
 * This function takes in a std::string word as input and checks if it meets the following criteria:
 * - The length of the word is exactly 5 characters.
 * - The word consists only of uppercase letters (A-Z).
 *
 * @param word The word to be validated.
 *
 * @return True if the word meets the criteria, false otherwise.
 *
 * @throws None.
 */
bool valid_word(std::string word) 
{
    // Check if the length of the word is 5 characters
    if (word.length() != 5) {
        return false;
    }

    // Check if the word consists only of uppercase letters
    if (word.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos) {
        return false;
    }

    return true;
}

/**
 * @brief Fills a 2D vector of integers representing the matches between a target word and a guess.
 *
 * This function takes in a reference to a 2D vector of integers representing the matches, the index of the try,
 * the target word, and the guess word. It initializes all the values in the 2D vector to no_match.
 * For each character in the guess, it checks if it is present in the target word.
 * If it is, and it is in the same position, it sets the value in the 2D vector to match. If it is present, but
 * not in the same position, it sets the value to part_match.
 *
 * @param[out] matches A reference to a 2D vector of integers representing the matches.
 * @param tryIndex An integer representing the index of the try.
 * @param target A string representing the target word.
 * @param guess A string representing the guess word.
 *
 * @throws None.
 */
void mark_match(std::vector<std::vector<int>> &matches, int tryIndex, std::string target, std::string guess)
{
    // Initialize all values in the 2D vector to no_match
    for (int i = 0; i < guess.length(); i++)
    {
        matches[tryIndex][i] = 0;
    }
    // For each character in the guess, check if it is present in the target word
    for (int j = 0; j < guess.length(); j++)
    {
        // Check if the character is in the target word and in the same position
        for (int i = 0; i < target.length(); i++)
        {
            if (guess[j] == target[i])
            {
                if (i == j)
                {
                    matches[tryIndex][j] = 2;
                    break;
                }
                else
                {
                    matches[tryIndex][j] = 1;
                }
            }
        }
    }
}

/**
 * @brief Checks if all characters in the guess word match their corresponding characters in the target word.
 *
 * This function takes in two std::strings, target and guess. It checks if each character in the guess
 * word matches its corresponding character in the target word. If any character does not match,
 * the function returns false. If all characters match, the function returns true.
 *
 * @param target A std::string representing the target word.
 * @param guess A std::string representing the guess word.
 *
 * @return True if all characters in the guess word match their corresponding characters in the target word, false otherwise.
 *
 * @throws None.
 */
bool is_all_match(std::string target, std::string guess)
{
    // Check if each character in the guess word matches its corresponding character in the target word
    for (int i = 0; i < guess.length(); i++)
    {
        // If any character does not match, return false
        if (guess[i] != target[i])
            return false;
    }
    // If all characters match, return true
    return true;
}

int main() {
    // Test if the function correctly converts a lowercase string to uppercase
    {
        std::string input = "hello";
        capitalize(input);
        assert(input == "HELLO");
    }

    // Test if the function correctly handles strings with mixed cases
    {
        std::string input = "HeLLo";
        capitalize(input);
        assert(input == "HELLO");
    }

    // Test if the function correctly validates a 5-letter uppercase word
    {
        std::string word = "ABCDE";
        assert(valid_word(word) == true);
    }

    // Test if the function correctly rejects words with invalid length or characters
    {
        std::string word = "ABCDEF"; // 6 characters
        assert(valid_word(word) == false);
        
        word = "ABCD1"; // Contains a non-alphabetic character
        assert(valid_word(word) == false);

        word = "AB"; // Too short
        assert(valid_word(word) == false);
    }

    // Test mark_match function
    {
        std::vector<std::vector<int>> matches(1, std::vector<int>(5, 0));
        mark_match(matches, 0, "ABCDE", "AXYBZ");
        // Expectation: A (match), X (not found), Y (not found), B (match), Z (not found)
        std::vector<int> expected = {2, 0, 0, 1, 0};
        assert(matches[0] == expected);
    }

    // Test is_all_match function
    {
        std::string target_word = "ABCDE";
        assert(is_all_match(target_word, "ABCDE") == true); // All match
        assert(is_all_match(target_word, "ABCDD") == false); // Last character does not match
        assert(is_all_match(target_word, "AXYBZ") == false); // Partial match
        assert(is_all_match(target_word, "AXYZZ") == false); // Partial match and last character does not match
    }

    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}
