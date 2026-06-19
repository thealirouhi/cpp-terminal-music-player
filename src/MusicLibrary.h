/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <string>
#include <vector>
using namespace std;

#include "Song.h"

class MusicLibrary
{
private:
    vector<Song*> songs_;

public:
    /// Adds a song to the library (library takes ownership).
    void addSong(Song* song);

    /// Returns the number of songs in the library.
    int getSongCount() const;

    /// Returns a pointer to the song at the given index, or nullptr if out of range.
    Song* getSong(int index) const;

    /// Returns all songs in the library.
    const vector<Song*>& getAllSongs() const;

    /// Returns songs filtered by artist (case-insensitive).
    vector<Song*> filterByArtist(const string& artist) const;

    /// Returns songs filtered by album (case-insensitive).
    vector<Song*> filterByAlbum(const string& album) const;

    /// Destructor — deletes all owned Song objects.
    ~MusicLibrary();
};

#endif
