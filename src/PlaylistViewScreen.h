/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef PLAYLISTVIEWSCREEN_H
#define PLAYLISTVIEWSCREEN_H

#include "Screen.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "Player.h"
#include "Playlist.h"
#include <vector>
#include <string>
using namespace std;

class PlaylistViewScreen : public Screen
{
public:
    PlaylistViewScreen(UIRenderer& renderer, InputHandler& input,
                       Player& player, Playlist*& currentPlaylist);

    void render() override;
    void handleInput() override;

    int getSelectedSongIndex() const;

private:
    UIRenderer& renderer_;
    InputHandler& input_;
    Player& player_;
    Playlist*& currentPlaylist_;

    vector<Song*> displayedSongs_;
    bool searchMode_;
    string searchQuery_;
    int sortField_;    // 0=default, 1=title, 2=artist, 3=album, 4=year, 5=duration
    bool sortAscending_;
    int selectedSongIndex_;

    void refreshDisplayedSongs();
    void enterSearchMode();
    void enterSortMode();
    void applySort();
    void applySearch();
};

#endif
