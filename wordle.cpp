/**
 * @file wordle.cpp
 * @brief Contains the main program logic for the Wordle game.
 *
 * This file contains the main program logic for the Wordle game. It includes
 * the necessary headers and defines constants for the word length, match types,
 * and initializes the random number generator. The program prompts the user to
 * enter a word, checks if it is valid, and keeps track of the user's attempts and
 * matches. It keeps generating random words until the user finds the correct word
 * or runs out of attempts.
 *
 * @author Alex Landry
 * @date 2023-05-02
 *
 * @par Inputs:
 * - The user enters a word to guess.
 *
 * @par Outputs:
 * - The program prints the wordle board, the user's attempts, and the target
 *   word if the user finds the correct word.
 */
#include "wordle.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <Windows.h>

const int length_word = 5; ///< The length of a word.
const int no_match = 0;    ///< No match.
const int part_match = 1; ///< Partial match.
const int match = 2;         ///< Full match.

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
 * @brief Returns a random word from the "words.txt" file.
 *
 * This function opens the "words.txt" file and reads each word into a vector of strings.
 * If the file cannot be opened, an empty string is returned. If the file is empty,
 * an empty string is returned. Otherwise, a random index is generated and the word
 * at that index is returned.
 *
 * @return A random word from the "words.txt" file, or an empty string if the file
 *         cannot be opened or is empty.
 *
 * @throws None
 */
std::string get_random_word() {
    std::ifstream file("words.txt");
    std::vector<std::string> words;
    std::string word;

    if (!file.is_open()) {
        std::cerr << "Error opening file: words.txt" << std::endl;
        return "";
    }

    while (std::getline(file, word)) {
        words.push_back(word);
    }
    file.close();

    if (words.empty()) {
        std::cerr << "No words found in the file." << std::endl;
        return "";
    }

    int randomIndex = std::rand() % words.size();
    return words[randomIndex];
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
    if (word.length() != length_word) {
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
 * not in the same position, it sets the value to part_match. The inputs are a reference to a 2D vector of integers
 * representing the matches, an integer representing the index of the try, a string representing the target word,
 * and a string representing the guess word. The outputs are none, but the input 2D vector is modified.
 *
 * @param matches A reference to a 2D vector of integers representing the matches.
 * @param tryIndex An integer representing the index of the try.
 * @param target A string representing the target word.
 * @param guess A string representing the guess word.
 */
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
        matches[tryIndex][i] = no_match;
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
                    matches[tryIndex][j] = match;
                    break;
                }
                else
                {
                    matches[tryIndex][j] = part_match;
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
bool all_match(std::string target, std::string guess)
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

/**
 * @brief Prints a Wordle game board with the given tries and matches.
 *
 * This function prints the Wordle game board, which includes a row for each try in the tries vector,
 * and a column for each character in each word in the tries vector. The matches vector is used to
 * determine the color of each character in each try.
 *
 * @param tries A vector of strings representing the tries in the game.
 * @param matches A 2D vector of integers representing the matches between each try and each character.
 * @param current_try An integer representing the index of the current try.
 *
 * @throws None.
 */
void print_wordle(std::vector<std::string> tries, std::vector<std::vector<int>> matches, int current_try)
{
    // Iterate over each try in the tries vector
    for (int i = 0; i <= current_try && i < tries.size(); i++)
    {
        // Generate the separator line for the board
        std::string separator = "-";
        // Generate the padding line for the board
        std::string padding = "|";
        // Generate the text line for the board
        std::string text = "|";
        // Iterate over each character in the current try
        for (int j = 0; j < tries[i].length(); j++)
        {
            // Add a separator segment for each character
            separator += "------";
            // Add a padding segment for each character
            padding += "     |";
            // Add the current character to the text line, with color if necessary
            char value = std::toupper(tries[i][j]);
            text += "  ";
            if (matches[i][j] == part_match)
            {
                text += "\033[33m";
            }
            else if (matches[i][j] == match)
            {
                text += "\033[32m";
            }
            text += value;
            if (matches[i][j] == part_match || matches[i][j] == match)
            {
                text += "\033[0m";
            }
            text += "  |";
        }
        // Print the separator line if this is the first try
        if (i == 0)
        { 
            std::cout << separator << std::endl;
        }
        // Print the padding line
        std::cout << padding << std::endl;
        // Print the text line
        std::cout << text << std::endl;
        // Print the padding line
        std::cout << padding << std::endl; 
        // Print the separator line
        std::cout << separator << std::endl;
    }
}

/**
 * @brief Main function that plays the Wordle game.
 *
 * This function plays the Wordle game. It takes in the number of tries as an input.
 * It initializes the tries vector and matches vector, seeds the random number generator,
 * gets a random word, and enters a loop to get user input and check if the word is found.
 *
 * @param number_of_tries The number of tries the user has to guess the word.
 *
 * @return 0 if the program runs successfully.
 *
 * @throws None
 */
int main() {
    // Set the number of tries
    const int number_of_tries = 6;

    // Vector to store the tries
    std::vector<std::string> tries(number_of_tries);

    // 2D vector to store the matches between a target word and a guess
    std::vector<std::vector<int>> matches(number_of_tries, std::vector<int>(length_word));

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Get a random word
    std::string target_word = get_random_word();

    // To upper case
    capitalize(target_word);

    // Input string
    std::string input;

    // Current try index
    int current_try = 0;

    // Loop to get user input and check if the word is found
    while (current_try < number_of_tries) {
        do {
            // Prompt the user to enter a guess or Q to quit
            std::cout << "Please enter your guess (word length must be " + std::to_string(length_word) + ") or type Q to quit: ";
            std::getline(std::cin, input);

            // To upper case
            capitalize(input);
        } while (input != "Q" && !valid_word(input));

        // Exit the loop if the user quits
        if (input == "Q") {
            std::cout << "Quit game" << std::endl;
            break;
        }

        // Store the input in the tries vector
        tries[current_try] = input;

        // Fill a 2D vector of integers representing the matches between a target word and a guess
        mark_match(matches, current_try, target_word, input);

        // Print the tries and matches
        print_wordle(tries, matches, current_try);

        // Exit the loop if the word is found
        if (all_match(target_word, input)) {
            std::cout << "You found the word!" << std::endl;
            break;
        }
        // Exit the loop if the number of tries is reached
        else if (current_try == number_of_tries - 1) {
            std::cout << "You didn't find the word" << std::endl;
            std::cout << "The word was: " << target_word << std::endl;
        }

        // Increment the current try index
        current_try++;
    }

    // Return 0 if the program runs successfully
    return 0;
}
