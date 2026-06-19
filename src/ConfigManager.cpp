/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "ConfigManager.h"
#include <fstream>
#include <iostream>

void ConfigManager::load(const string& filePath)
{
    ifstream file(filePath);
    if (!file.is_open()) {
        // File doesn't exist yet — that's fine, start with empty settings.
        return;
    }

    settings_.clear();

    string line;
    while (getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t eqPos = line.find('=');
        if (eqPos == string::npos) {
            continue;
        }

        string key = line.substr(0, eqPos);
        string value = line.substr(eqPos + 1);

        // Trim leading/trailing whitespace from key and value
        size_t first = key.find_first_not_of(" \t");
        size_t last = key.find_last_not_of(" \t");
        if (first != string::npos) key = key.substr(first, last - first + 1);
        else key.clear();

        first = value.find_first_not_of(" \t");
        last = value.find_last_not_of(" \t");
        if (first != string::npos) value = value.substr(first, last - first + 1);
        else value.clear();

        if (!key.empty()) {
            settings_[key] = value;
        }
    }

    file.close();
}

string ConfigManager::get(const string& key) const
{
    auto it = settings_.find(key);
    if (it != settings_.end()) {
        return it->second;
    }
    return "";
}

void ConfigManager::set(const string& key, const string& value)
{
    settings_[key] = value;
}

void ConfigManager::save(const string& filePath) const
{
    ofstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Could not write to settings file: " << filePath << endl;
        return;
    }

    for (const auto& pair : settings_) {
        file << pair.first << "=" << pair.second << "\n";
    }

    file.close();
}
