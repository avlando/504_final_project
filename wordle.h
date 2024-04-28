#ifndef WORDLE_H
#define WORDLE_H

#include <string>
#include <vector>

void toUpperCase(std::string &input);
std::string getRandomWord();
bool isValid(std::string word);
void markMatch(std::vector<std::vector<int>> &matches, int tryIndex, std::string target, std::string guess);
bool isAllMatch(std::string target, std::string guess);
void printWordle(std::vector<std::string> tries, std::vector<std::vector<int>> matches, int currentTry);

#endif // WORDLE_H