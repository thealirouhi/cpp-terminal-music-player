/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "UIRenderer.h"
#include <iostream>
#include <iomanip>

void UIRenderer::clearScreen() const
{
    cout << "\033[2J\033[1;1H";
}

void UIRenderer::printBanner() const
{
    drawTopBorder();
    drawTextLine("♫  Terminal Music Player  ♫", true);
    drawDivider("╠", "═", "╣", "");
}

void UIRenderer::drawTopBorder() const
{
    cout << "╔";
    for (int i = 0; i < BOX_WIDTH; i++) cout << "═";
    cout << "╗" << endl;
}

void UIRenderer::drawBottomBorder() const
{
    cout << "╚";
    for (int i = 0; i < BOX_WIDTH; i++) cout << "═";
    cout << "╝" << endl;
}

void UIRenderer::drawEmptyLine() const
{
    cout << "║ " << string(BOX_WIDTH, ' ') << " ║" << endl;
}

void UIRenderer::drawTextLine(const string& text, bool center) const
{
    string content;
    if (center) {
        content = centerText(text, BOX_WIDTH);
    } else {
        content = text + string(
            max(0, BOX_WIDTH - static_cast<int>(text.length())), ' ');
    }
    cout << "║ " << left << setw(BOX_WIDTH) << content << " ║" << endl;
}

void UIRenderer::drawDivider(const string& left, const string& horizontal,
                              const string& right, const string& label) const
{
    cout << left;
    if (label.empty()) {
        for (int i = 0; i < BOX_WIDTH; i++) cout << horizontal;
    } else {
        int labelLen = static_cast<int>(label.length());
        int sideLen = (BOX_WIDTH - labelLen - 2) / 2;
        for (int i = 0; i < sideLen; i++) cout << horizontal;
        cout << " " << label << " ";
        int remaining = BOX_WIDTH - sideLen - labelLen - 2;
        for (int i = 0; i < remaining; i++) cout << horizontal;
    }
    cout << right << endl;
}

void UIRenderer::drawLabelLine(const string& label, const string& value) const
{
    string line = label + ": " + value;
    drawTextLine(line, false);
}

void UIRenderer::printError(const string& message) const
{
    cout << "Error: " << message << endl;
}

void UIRenderer::printPrompt(const string& message) const
{
    cout << message;
}

string UIRenderer::truncate(const string& text, int maxLen) const
{
    if (static_cast<int>(text.length()) <= maxLen) return text;
    return text.substr(0, maxLen - 3) + "...";
}

string UIRenderer::centerText(const string& text, int width) const
{
    int textLen = static_cast<int>(text.length());
    if (textLen >= width) return text;
    int padding = (width - textLen) / 2;
    return string(padding, ' ') + text;
}
