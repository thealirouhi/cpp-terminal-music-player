/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "Application.h"
#include <iostream>

Application::Application()
    : currentScreen_(SCREEN_MAIN_MENU),
      activePlaylistIndex_(-1),
      currentPlaylist_(nullptr),
      filterActive_(false),
      filteredPlaylist_(nullptr),
      dataDir_("Data")
{
}

Application::~Application()
{
    saveState();

    // Delete owned screens
    for (int i = 0; i < 6; i++) {
        delete screens_[i];
    }

    // Delete owned playlists
    for (Playlist* p : playlists_) {
        delete p;
    }

    delete filteredPlaylist_;
}

bool Application::init()
{
    loadData();

    // Create all screens (pass references to shared objects)
    string lastPlayed = config_.get("last_song");
    screens_[0] = new MainMenu(renderer_, input_, lastPlayed);
    screens_[1] = new NowPlayingScreen(renderer_, input_, player_);
    screens_[2] = new PlaylistListScreen(renderer_, input_,
                                         playlists_, activePlaylistIndex_);
    screens_[3] = new PlaylistViewScreen(renderer_, input_,
                                         player_, currentPlaylist_);
    screens_[4] = new FilterScreen(renderer_, input_,
                                   library_, currentPlaylist_);
    screens_[5] = new SettingsScreen(renderer_, input_, player_);

    return true;
}

void Application::loadData()
{
    // Load CSV library
    vector<Song*> songs = csvLoader_.loadSongs(dataDir_ + "/library.csv");
    for (Song* song : songs) {
        library_.addSong(song);
    }

    // Load playlists from M3U files
    playlists_ = m3uLoader_.loadAllPlaylists(dataDir_ + "/Playlists", library_);

    // Load settings
    config_.load(dataDir_ + "/settings.cfg");

    // Restore active playlist
    string activePlaylistName = config_.get("active_playlist");
    if (!activePlaylistName.empty()) {
        for (size_t i = 0; i < playlists_.size(); i++) {
            if (playlists_[i]->getName() == activePlaylistName) {
                activePlaylistIndex_ = static_cast<int>(i);
                currentPlaylist_ = playlists_[i];
                player_.setPlaylist(currentPlaylist_);
                break;
            }
        }
    }

    // Set first playlist as default if nothing restored
    if (activePlaylistIndex_ < 0 && !playlists_.empty()) {
        activePlaylistIndex_ = 0;
        currentPlaylist_ = playlists_[0];
        player_.setPlaylist(currentPlaylist_);
    }

    // Restore playback mode
    string modeStr = config_.get("playback_mode");
    if (!modeStr.empty()) {
        if (modeStr == "NO_REPEAT")  player_.setMode(Player::NO_REPEAT);
        else if (modeStr == "REPEAT_ONE")  player_.setMode(Player::REPEAT_ONE);
        else if (modeStr == "REPEAT_ALL")  player_.setMode(Player::REPEAT_ALL);
        else if (modeStr == "SHUFFLE")     player_.setMode(Player::SHUFFLE);
    }
}
