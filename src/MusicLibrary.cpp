/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "MusicLibrary.h"

void MusicLibrary::addSong(Song* song)
{
    songs_.push_back(song);
}

int MusicLibrary::getSongCount() const
{
    return static_cast<int>(songs_.size());
}

Song* MusicLibrary::getSong(int index) const
{
    if (index < 0 || index >= static_cast<int>(songs_.size())) {
        return nullptr;
    }
    return songs_[index];
}

const vector<Song*>& MusicLibrary::getAllSongs() const
{
    return songs_;
}

MusicLibrary::~MusicLibrary()
{
    for (Song* song : songs_) {
        delete song;
    }
}
