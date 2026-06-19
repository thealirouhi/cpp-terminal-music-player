/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(UIRenderer& renderer, InputHandler& input,
                   const string& lastPlayed)
    : renderer_(renderer),
      input_(input),
      lastPlayed_(lastPlayed),
      selectedOption_(-1)
{
}

void MainMenu::render()
{
    renderer_.clearScreen();
    renderer_.printBanner();

    if (!lastPlayed_.empty()) {
        renderer_.drawLabelLine("Last played", lastPlayed_);
    } else {
        renderer_.drawEmptyLine();
    }

    renderer_.drawDivider("╠", "═", "╣", "");
    renderer_.drawTextLine("1.  Now Playing");
    renderer_.drawTextLine("2.  Playlists");
    renderer_.drawTextLine("3.  Browse Playlist");
    renderer_.drawTextLine("4.  Settings");
    renderer_.drawDivider("╠", "═", "╣", "");
    renderer_.drawTextLine("0.  Quit (saves state)");
    renderer_.drawBottomBorder();
    renderer_.printPrompt("Enter choice: ");
}

void MainMenu::handleInput()
{
    selectedOption_ = input_.readInt(0, 4);
}

bool MainMenu::hasExited() const
{
    return selectedOption_ == 0;
}

void MainMenu::resetExit()
{
    selectedOption_ = -1;
}

int MainMenu::getSelectedOption() const
{
    return selectedOption_;
}
