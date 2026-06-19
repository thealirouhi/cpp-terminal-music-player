/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "M3uLoader.h"
#include <fstream>
#include <iostream>

using namespace std;

Playlist* M3uLoader::loadPlaylist(const string& filePath,
                                  const MusicLibrary& library)
{
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open playlist file: " << filePath << endl;
        return nullptr;
    }

    // Extract playlist name from file name (remove path and extension)
    size_t slashPos = filePath.find_last_of("/\\");
    string fileName = (slashPos != string::npos)
                      ? filePath.substr(slashPos + 1)
                      : filePath;
    size_t dotPos = fileName.find_last_of('.');
    string playlistName = (dotPos != string::npos)
                          ? fileName.substr(0, dotPos)
                          : fileName;

    Playlist* playlist = new Playlist(playlistName);
    string line;

    while (getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Match the line to a song in the library
        const vector<Song*>& allSongs = library.getAllSongs();
        for (Song* song : allSongs) {
            if (song->getFilePath() == line) {
                playlist->addSong(song);
                break;
            }
        }
    }

    file.close();
    return playlist;
}
