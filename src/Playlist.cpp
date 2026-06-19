/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "Playlist.h"

Playlist::Playlist(const string& name)
    : name_(name)
{
}

string Playlist::getName() const
{
    return name_;
}

int Playlist::getSongCount() const
{
    return static_cast<int>(songs_.size());
}

void Playlist::addSong(Song* song)
{
    songs_.push_back(song);
}
