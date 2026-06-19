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
#include <limits>

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

int InputHandler::readInt(int min, int max) const
{
    int value;
    string input;

    while (true) {
        getline(cin, input);

        // Trim whitespace
        size_t first = input.find_first_not_of(" \t");
        if (first != string::npos) {
            input = input.substr(first);
        }

        try {
            size_t pos;
            value = stoi(input, &pos);

            if (pos != input.length()) {
                // Extra characters after the number
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }

            if (value < min || value > max) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }

            return value;
        }
        catch (const invalid_argument&) {
            cin.clear();
            cout << "Invalid choice. Please try again." << endl;
        }
        catch (const out_of_range&) {
            cin.clear();
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int InputHandler::readSongIndex(int maxIndex) const
{
    if (maxIndex <= 0) {
        cout << "No song at this index." << endl;
        return -1;
    }

    int index = readInt(1, maxIndex);
    return index;
}
