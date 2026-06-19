/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef FILTERSCREEN_H
#define FILTERSCREEN_H

#include "Screen.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "Playlist.h"
#include "MusicLibrary.h"
#include <vector>
#include <string>
using namespace std;

class FilterScreen : public Screen
{
public:
    FilterScreen(UIRenderer& renderer, InputHandler& input,
                 MusicLibrary& library, Playlist*& currentPlaylist);

    void render() override;
    void handleInput() override;
    bool hasExited() const override;
    void resetExit() override;

    const vector<Song*>& getFilteredSongs() const;
    Playlist* getFilteredPlaylist() const;

private:
    UIRenderer& renderer_;
    InputHandler& input_;
    MusicLibrary& library_;
    Playlist*& currentPlaylist_;

    bool exited_;
    int filterType_;          // 1 = artist, 2 = album, 0 = none
    vector<string> filterValues_;
    vector<Song*> filteredSongs_;
    string selectedFilter_;
    bool filterApplied_;

    void collectUniqueArtists();
    void collectUniqueAlbums();
    void applyArtistFilter(const string& artist);
    void applyAlbumFilter(const string& album);
};

#endif
