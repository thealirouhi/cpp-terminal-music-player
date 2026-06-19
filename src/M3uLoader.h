/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef M3ULOADER_H
#define M3ULOADER_H

#include <string>
#include <vector>
using namespace std;

#include "Playlist.h"
#include "MusicLibrary.h"

class M3uLoader
{
public:
    /// Loads a single .m3u file and returns a Playlist.
    /// Skips paths that don't match any song in the library.
    Playlist* loadPlaylist(const string& filePath, const MusicLibrary& library);

    /// Loads all .m3u files from the given directory and returns a vector of Playlists.
    vector<Playlist*> loadAllPlaylists(const string& dirPath, const MusicLibrary& library);
};

#endif
