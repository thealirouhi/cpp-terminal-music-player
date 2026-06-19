/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "NowPlayingScreen.h"
#include <iostream>

NowPlayingScreen::NowPlayingScreen(UIRenderer& renderer,
                                   InputHandler& input, Player& player)
    : renderer_(renderer), input_(input), player_(player)
{
}

void NowPlayingScreen::render()
{
    renderer_.clearScreen();
    renderer_.printBanner();
    renderer_.drawTextLine("Now Playing", true);
    renderer_.drawDivider("╠", "═", "╣", "");

    Song* song = player_.getCurrentSong();

    if (song == nullptr) {
        renderer_.drawTextLine("No song selected.");
    } else {
        renderer_.drawLabelLine("Title", song->getTitle());
        renderer_.drawLabelLine("Artist", song->getArtist());
        renderer_.drawLabelLine("Album", song->getAlbum());
        renderer_.drawLabelLine("Genre", song->getGenre());
    }

    renderer_.drawDivider("╠", "═", "╣", "");

    string status = (song != nullptr)
        ? stateLabel() + "   Mode: " + modeLabel()
        : "STOPPED";
    renderer_.drawTextLine(status);

    if (song != nullptr) {
        renderer_.drawLabelLine("Duration", song->getFormattedDuration());
    }

    renderer_.drawDivider("╠", "═", "╣", "");
    renderer_.drawTextLine("[p] pause  [n] next  [b] prev  [s] stop  [q] menu");
    renderer_.drawBottomBorder();
    renderer_.printPrompt("");
}

void NowPlayingScreen::handleInput()
{
    string key = input_.readKey();

    if (key == "p") {
        if (player_.getState() == Player::PLAYING) {
            player_.pause();
        } else if (player_.getState() == Player::PAUSED) {
            player_.resume();
        }
    } else if (key == "n") {
        player_.next();
    } else if (key == "b") {
        player_.previous();
    } else if (key == "s") {
        player_.stop();
    } else if (key == "q") {
        // Back to main menu
    }
}

string NowPlayingScreen::stateLabel() const
{
    switch (player_.getState()) {
        case Player::PLAYING: return "▶  PLAYING";
        case Player::PAUSED:  return "⏸  PAUSED";
        case Player::STOPPED: return "⏹  STOPPED";
        default:              return "";
    }
}

string NowPlayingScreen::modeLabel() const
{
    switch (player_.getMode()) {
        case Player::NO_REPEAT:  return "NO_REPEAT";
        case Player::REPEAT_ONE: return "REPEAT_ONE";
        case Player::REPEAT_ALL: return "REPEAT_ALL";
        case Player::SHUFFLE:    return "SHUFFLE";
        default:                 return "";
    }
}
