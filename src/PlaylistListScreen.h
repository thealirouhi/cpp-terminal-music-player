/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef PLAYLISTLISTSCREEN_H
#define PLAYLISTLISTSCREEN_H

#include "Screen.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "Playlist.h"
#include <vector>
#include <string>
using namespace std;

class PlaylistListScreen : public Screen
{
public:
    PlaylistListScreen(UIRenderer& renderer, InputHandler& input,
                       vector<Playlist*>& playlists, int& activeIndex);

    void render() override;
    void handleInput() override;

private:
    UIRenderer& renderer_;
    InputHandler& input_;
    vector<Playlist*>& playlists_;
    int& activeIndex_;
};

#endif
