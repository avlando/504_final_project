## PHY 504 Computation in Physics and Astrophysics Final Project

## Overview

This is my final project for PHY 504 Computation in Physics and Astrophysics for Spring 2024. This Wordle game is a simple word-guessing game where the player tries to guess a target word within a limited number of attempts. The game provides feedback on each guess, indicating whether the guessed word contains correct letters in the correct positions, correct letters in incorrect positions, or incorrect letters.

## Features

- Randomly selects a target word from a list of words.
- Allows the player a fixed number of attempts to guess the word.
- Provides feedback on each guess, indicating matches and partial matches.
- Supports both uppercase and lowercase inputs.
- Offers a simple command-line interface for interaction.

## Dependencies

- C++ compiler
- `words.txt` file containing a list of words to choose from.
- Windows operating system (due to the use of `Windows.h` for console color matching support).

## Usage

1. Compile the `wordle.cpp` file using a C++ compiler.

   ```bash
   g++ wordle.cpp -o wordle
   
3. Ensure that the words.txt file is present in the same directory as the compiled executable.
4. Run the compiled executable `./wordle`
5. Follow the on-screen instructions to play the Wordle game.

## Testing

1. Compile the `wordle.cpp` and `test.cpp` files using a C++ compiler.

   ```bash
   g++ wordle.cpp test.cpp -o test

2. Ensure that you are in the output directory
3. Run the compiled executable `.\'test.exe'`
4. If terminal prints "All tests passed successfully!", then all tests completely passes

# Customization
- You can adjust the `length_word` constant in the wordle.cpp file to change the length of the target word.
Note: Changing the `length_word` constant means that `word.txt` needs to be updated to include the appropriate words with given length 
- Modify the `number_of_tries` constant in the main function to change the number of attempts allowed for the player.

Credits
Author: Alex Landry
Date: May 2nd, 2024
