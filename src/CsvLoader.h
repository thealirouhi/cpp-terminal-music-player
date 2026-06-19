/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <string>
#include <vector>
#include "Song.h"

class CsvLoader
{
public:
    /// Reads library.csv from the given path and returns a vector of Song pointers.
    /// Returns an empty vector on failure (file not found, empty file, etc.).
    std::vector<Song*> loadSongs(const std::string& filePath);
};

#endif
