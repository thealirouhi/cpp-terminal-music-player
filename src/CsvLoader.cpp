/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "CsvLoader.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<Song*> CsvLoader::loadSongs(const string& filePath)
{
    vector<Song*> songs;
    ifstream file(filePath);

    if (!file.is_open()) {
        return songs;
    }

    string line;
    // Skip header line
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string title, artist, album, genre;
        string yearStr, durationStr, filePathStr;

        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, album, ',');
        getline(ss, genre, ',');
        getline(ss, yearStr, ',');
        getline(ss, durationStr, ',');
        getline(ss, filePathStr, ',');

        int year = stoi(yearStr);
        int durationSec = stoi(durationStr);

        Song* song = new Song(title, artist, album, genre,
                              year, durationSec, filePathStr);
        songs.push_back(song);
    }

    return songs;
}
