## PHY 504 Computation in Physics and Astrophysics Final Project

## Overview

This Wordle game is a simple word-guessing game where the player tries to guess a target word within a limited number of attempts. The game provides feedback on each guess, indicating whether the guessed word contains correct letters in the correct positions, correct letters in incorrect positions, or incorrect letters.

## Features

- Randomly selects a target word from a list of words.
- Allows the player a fixed number of attempts to guess the word.
- Provides feedback on each guess, indicating matches and partial matches.
- Supports both uppercase and lowercase inputs.
- Offers a simple command-line interface for interaction.

## Dependencies

- C++ compiler with C++11 support.
- `words.txt` file containing a list of words to choose from.
- Windows operating system (due to the use of `Windows.h` for console color support).

## Usage

1. Compile the `wordle.cpp` file using a C++ compiler.

   ```bash
   g++ wordle.cpp -o wordle
   
3. Ensure that the words.txt file is present in the same directory as the compiled executable.
4. Run the compiled executable `./wordle`
5. follow the on-screen instructions to play the Wordle game.

# Customization
- You can adjust the WORD_LENGTH constant in the wordle.cpp file to change the length of the target word.
- Modify the numberOfTries constant in the main function to change the number of attempts allowed for the player.

Credits
Author: Alex Landry
Date: April 27, 2023
