/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "SettingsScreen.h"
#include <iostream>

SettingsScreen::SettingsScreen(UIRenderer& renderer,
                               InputHandler& input, Player& player)
    : renderer_(renderer), input_(input), player_(player), exited_(false)
{
}

void SettingsScreen::render()
{
    renderer_.clearScreen();
    renderer_.printBanner();
    renderer_.drawTextLine("Settings", true);
    renderer_.drawDivider("╠", "═", "╣", "");

    string current = "Playback Mode  (current: "
                     + modeDescription(player_.getMode()) + ")";
    renderer_.drawTextLine(current);

    renderer_.drawEmptyLine();
    renderer_.drawTextLine("1.  NO_REPEAT     play in order, stop at end");
    renderer_.drawTextLine("2.  REPEAT_ONE    repeat current song forever");
    renderer_.drawTextLine("3.  REPEAT_ALL    loop whole playlist");
    renderer_.drawTextLine("4.  SHUFFLE       random order");

    renderer_.drawDivider("╠", "═", "╣", "");
    renderer_.drawTextLine("0.  Back (changes saved automatically)");
    renderer_.drawBottomBorder();
    renderer_.printPrompt("Choice: ");
}

void SettingsScreen::handleInput()
{
    int choice = input_.readInt(0, 4);

    switch (choice) {
        case 1: player_.setMode(Player::NO_REPEAT);  break;
        case 2: player_.setMode(Player::REPEAT_ONE);  break;
        case 3: player_.setMode(Player::REPEAT_ALL);  break;
        case 4: player_.setMode(Player::SHUFFLE);     break;
        case 0:
            exited_ = true;
            return;
    }
}

bool SettingsScreen::hasExited() const { return exited_; }
void SettingsScreen::resetExit() { exited_ = false; }

string SettingsScreen::modeDescription(Player::PlaybackMode mode) const
{
    switch (mode) {
        case Player::NO_REPEAT:  return "NO_REPEAT";
        case Player::REPEAT_ONE: return "REPEAT_ONE";
        case Player::REPEAT_ALL: return "REPEAT_ALL";
        case Player::SHUFFLE:    return "SHUFFLE";
        default:                 return "";
    }
}
