/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "UIRenderer.h"
#include "InputHandler.h"
#include "MusicLibrary.h"
#include "CsvLoader.h"
#include "M3uLoader.h"
#include "Player.h"
#include "ConfigManager.h"
#include "Screen.h"
#include "MainMenu.h"
#include "NowPlayingScreen.h"
#include "PlaylistListScreen.h"
#include "PlaylistViewScreen.h"
#include "FilterScreen.h"
#include "SettingsScreen.h"
#include <vector>
#include <string>
using namespace std;

class Application
{
public:
    enum ScreenId {
        SCREEN_MAIN_MENU,
        SCREEN_NOW_PLAYING,
        SCREEN_PLAYLIST_LIST,
        SCREEN_PLAYLIST_VIEW,
        SCREEN_FILTER,
        SCREEN_SETTINGS,
        SCREEN_QUIT
    };

    Application();
    ~Application();

    /// Initializes all subsystems and loads data.
    bool init();

    /// Runs the main loop until the user quits.
    void run();

private:
    // Owned components
    UIRenderer renderer_;
    InputHandler input_;
    MusicLibrary library_;
    CsvLoader csvLoader_;
    M3uLoader m3uLoader_;
    Player player_;
    ConfigManager config_;

    // Owned playlists (M3uLoader creates them on heap)
    vector<Playlist*> playlists_;

    // Owned screens
    Screen* screens_[6];
    ScreenId currentScreen_;

    // Active playlist
    int activePlaylistIndex_;
    Playlist* currentPlaylist_;

    // Filter state
    bool filterActive_;
    Playlist* filteredPlaylist_;

    // Data paths
    string dataDir_;

    // Internal methods
    void loadData();
    void saveState();
};

#endif
