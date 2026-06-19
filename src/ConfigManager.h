/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <map>
using namespace std;

class ConfigManager
{
public:
    /// Loads settings from the given file path.
    void load(const string& filePath);

    /// Saves current settings to the file.
    void save(const string& filePath) const;

    /// Returns the value for a key, or an empty string if not found.
    string get(const string& key) const;

    /// Sets a key-value pair in memory. Does NOT write to disk until save() is called.
    void set(const string& key, const string& value);

private:
    map<string, string> settings_;
};

#endif
