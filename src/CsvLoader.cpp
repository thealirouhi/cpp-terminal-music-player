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
#include <iostream>

using namespace std;

static const int EXPECTED_FIELDS = 7;

vector<Song*> CsvLoader::loadSongs(const string& filePath)
{
    vector<Song*> songs;
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filePath << endl;
        return songs;
    }

    string line;
    // Skip header line
    getline(file, line);

    while (getline(file, line)) {
        // Trim whitespace and skip empty lines
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string fields[EXPECTED_FIELDS];
        int fieldCount = 0;

        // Parse all comma-separated fields
        while (fieldCount < EXPECTED_FIELDS && getline(ss, fields[fieldCount], ',')) {
            fieldCount++;
        }

        // Skip malformed lines
        if (fieldCount < EXPECTED_FIELDS) {
            cerr << "Warning: Skipping malformed line: " << line << endl;
            continue;
        }

        try {
            // fields: 0=title, 1=artist, 2=album, 3=genre, 4=year, 5=duration, 6=filePath
            int year = stoi(fields[4]);
            int durationSec = stoi(fields[5]);

            Song* song = new Song(fields[0], fields[1], fields[2],
                                  fields[3], year, durationSec, fields[6]);
            songs.push_back(song);
        }
        catch (const invalid_argument&) {
            cerr << "Warning: Invalid number in line, skipping: "
                 << fields[0] << " - " << fields[1] << endl;
        }
        catch (const out_of_range&) {
            cerr << "Warning: Number out of range in line, skipping: "
                 << fields[0] << " - " << fields[1] << endl;
        }
    }

    file.close();
    return songs;
}
