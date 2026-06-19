/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "InputHandler.h"
#include <iostream>
#include <algorithm>
#include <cctype>

string InputHandler::readLine() const
{
    string input;
    getline(cin, input);

    // Trim leading whitespace
    size_t first = input.find_first_not_of(" \t");
    if (first == string::npos) {
        return "";
    }

    // Trim trailing whitespace
    size_t last = input.find_last_not_of(" \t");
    return input.substr(first, last - first + 1);
}

string InputHandler::readKey() const
{
    string input;
    getline(cin, input);
    if (input.empty()) {
        return "";
    }
    return string(1, input[0]);
}
