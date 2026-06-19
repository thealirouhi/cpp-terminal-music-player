/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "PlaylistListScreen.h"
#include <iostream>

PlaylistListScreen::PlaylistListScreen(UIRenderer& renderer,
    InputHandler& input, vector<Playlist*>& playlists, int& activeIndex)
    : renderer_(renderer), input_(input),
      playlists_(playlists), activeIndex_(activeIndex), exited_(false)
{
}

void PlaylistListScreen::render()
{
    renderer_.clearScreen();
    renderer_.printBanner();
    renderer_.drawTextLine("Playlists", true);
    renderer_.drawDivider("╠", "═", "╣", "");
    renderer_.drawTextLine("#   Name                    Songs");

    for (size_t i = 0; i < playlists_.size(); i++) {
        string line = to_string(i + 1) + "   " + playlists_[i]->getName();

        string count = " (" + to_string(playlists_[i]->getSongCount()) + ")";

        if (static_cast<int>(i) == activeIndex_) {
            count += "  [active]";
        }

        renderer_.drawTextLine(line + count);
    }

    renderer_.drawDivider("╠", "═", "╣", "");
    renderer_.drawTextLine("Enter number to switch active playlist.");
    renderer_.drawBottomBorder();
    renderer_.printPrompt("Choice: ");
}

void PlaylistListScreen::handleInput()
{
    int choice = input_.readInt(0, static_cast<int>(playlists_.size()));

    if (choice == 0) {
        exited_ = true;
        return;
    }

    int newIndex = choice - 1;
    if (newIndex >= 0 && newIndex < static_cast<int>(playlists_.size())) {
        activeIndex_ = newIndex;
    }
}

bool PlaylistListScreen::hasExited() const { return exited_; }
void PlaylistListScreen::resetExit() { exited_ = false; }
