/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "MusicLibrary.h"
#include <algorithm>
#include <cctype>

static string toLower(const string& str)
{
    string result = str;
    for (char& c : result) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

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

vector<Song*> MusicLibrary::filterByArtist(const string& artist) const
{
    vector<Song*> result;
    string lowerArtist = toLower(artist);

    for (Song* song : songs_) {
        if (toLower(song->getArtist()) == lowerArtist) {
            result.push_back(song);
        }
    }
    return result;
}

vector<Song*> MusicLibrary::filterByAlbum(const string& album) const
{
    vector<Song*> result;
    string lowerAlbum = toLower(album);

    for (Song* song : songs_) {
        if (toLower(song->getAlbum()) == lowerAlbum) {
            result.push_back(song);
        }
    }
    return result;
}

MusicLibrary::~MusicLibrary()
{
    for (Song* song : songs_) {
        delete song;
    }
}
