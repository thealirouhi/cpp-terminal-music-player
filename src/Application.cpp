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

void Application::run()
{
    while (currentScreen_ != SCREEN_QUIT) {
        // Render current screen
        screens_[currentScreen_]->render();

        // Handle input on current screen
        screens_[currentScreen_]->handleInput();

        // Navigate based on screen and user input
        if (currentScreen_ == SCREEN_MAIN_MENU) {
            int opt = static_cast<MainMenu*>(screens_[0])
                      ->getSelectedOption();
            switch (opt) {
                case 1: currentScreen_ = SCREEN_NOW_PLAYING; break;
                case 2: currentScreen_ = SCREEN_PLAYLIST_LIST; break;
                case 3: currentScreen_ = SCREEN_PLAYLIST_VIEW; break;
                case 4: currentScreen_ = SCREEN_SETTINGS; break;
                case 0: currentScreen_ = SCREEN_QUIT; break;
            }
        } else if (currentScreen_ == SCREEN_PLAYLIST_LIST) {
            if (screens_[currentScreen_]->hasExited()) {
                // Update current playlist pointer after any selection
                if (activePlaylistIndex_ >= 0 &&
                    activePlaylistIndex_ < static_cast<int>(playlists_.size())) {
                    if (currentPlaylist_ != playlists_[activePlaylistIndex_]) {
                        currentPlaylist_ = playlists_[activePlaylistIndex_];
                        player_.setPlaylist(currentPlaylist_);
                    }
                }
                screens_[currentScreen_]->resetExit();
                currentScreen_ = SCREEN_MAIN_MENU;
            }
        } else if (currentScreen_ == SCREEN_PLAYLIST_VIEW) {
            auto* view = static_cast<PlaylistViewScreen*>(screens_[3]);
            int songIndex = view->getSelectedSongIndex();

            if (view->hasExited()) {
                view->resetExit();
                currentScreen_ = SCREEN_MAIN_MENU;
            } else if (songIndex >= 0) {
                if (currentPlaylist_ != nullptr) {
                    player_.setPlaylist(currentPlaylist_);
                    player_.playSongAt(songIndex);
                }
                currentScreen_ = SCREEN_NOW_PLAYING;
            }
        } else if (screens_[currentScreen_]->hasExited()) {
            screens_[currentScreen_]->resetExit();
            currentScreen_ = SCREEN_MAIN_MENU;
        }

        // Let the player check if current song ended
        player_.tick();
    }

    saveState();
}

void Application::saveState()
{
    // Save active playlist
    if (activePlaylistIndex_ >= 0 &&
        activePlaylistIndex_ < static_cast<int>(playlists_.size())) {
        config_.set("active_playlist",
                    playlists_[activePlaylistIndex_]->getName());
    }

    // Save playback mode
    switch (player_.getMode()) {
        case Player::NO_REPEAT:  config_.set("playback_mode", "NO_REPEAT"); break;
        case Player::REPEAT_ONE: config_.set("playback_mode", "REPEAT_ONE"); break;
        case Player::REPEAT_ALL: config_.set("playback_mode", "REPEAT_ALL"); break;
        case Player::SHUFFLE:    config_.set("playback_mode", "SHUFFLE"); break;
    }

    // Save last played song
    Song* current = player_.getCurrentSong();
    if (current != nullptr) {
        config_.set("last_song", current->getTitle() + " — " + current->getArtist());
    }

    config_.save(dataDir_ + "/settings.cfg");
}
