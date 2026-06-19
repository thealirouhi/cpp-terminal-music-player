/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
using namespace std;

#include "Song.h"

class Playlist
{
private:
    string name_;
    vector<Song*> songs_;

public:
    explicit Playlist(const string& name);

    string getName() const;
    int getSongCount() const;

    /// Returns the song at the given index, or nullptr if out of range.
    Song* getSong(int index) const;

    /// Returns all songs in this playlist.
    const vector<Song*>& getSongs() const;

    /// Adds a song pointer to this playlist (does NOT take ownership).
    void addSong(Song* song);

    /// Destructor — does NOT delete songs. MusicLibrary owns them.
    ~Playlist() = default;
};

#endif
