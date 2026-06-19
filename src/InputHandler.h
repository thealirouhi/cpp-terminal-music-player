/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>
using namespace std;

class InputHandler
{
public:
    /// Reads a full line of text from the user.
    /// Trims leading/trailing whitespace.
    string readLine() const;

    /// Reads a single character from the user.
    /// Returns the character as a string.
    string readKey() const;

    /// Reads an integer between min and max (inclusive).
    /// Re-prompts on invalid input with "Invalid choice. Please try again."
    /// Clears cin on non-numeric input.
    int readInt(int min, int max) const;

    /// Reads a song index (1-based) within the given range.
    /// Returns -1 on invalid, prints "No song at this index."
    int readSongIndex(int maxIndex) const;
};

#endif
