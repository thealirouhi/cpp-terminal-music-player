/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef UIRENDERER_H
#define UIRENDERER_H

#include <string>
#include <vector>
using namespace std;

#include "Song.h"

class UIRenderer
{
public:
    static const int BOX_WIDTH = 54;

    /// Clears the terminal screen.
    void clearScreen() const;

    /// Draws a horizontal divider line with optional label in the middle.
    void drawDivider(char corner, char horizontal, char vertical,
                     const string& label = "") const;

    /// Draws a full box with top, bottom, and content lines.
    void drawTopBorder() const;
    void drawBottomBorder() const;
    void drawEmptyLine() const;
    void drawTextLine(const string& text, bool center = false) const;
    void drawLabelLine(const string& label, const string& value) const;

    /// Prints a formatted song row for the playlist view.
    void printSongRow(int index, const Song& song) const;

    /// Prints a formatted song row showing just number, title, and artist.
    void printSimpleSongRow(int index, const Song& song) const;

    /// Prints an error message.
    void printError(const string& message) const;

    /// Prints a prompt message.
    void printPrompt(const string& message) const;

    /// Prints the app title banner.
    void printBanner() const;

private:
    string truncate(const string& text, int maxLen) const;
    string centerText(const string& text, int width) const;
};

#endif
