/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

#include "Song.h"
#include "Playlist.h"

struct ma_engine;
struct ma_sound;

class Player
{
public:
    enum PlaybackState {
        STOPPED,
        PLAYING,
        PAUSED
    };

    enum PlaybackMode {
        NO_REPEAT,
        REPEAT_ONE,
        REPEAT_ALL,
        SHUFFLE
    };

    Player();
    ~Player();

    // --- Playback controls ---
    void play();
    void pause();
    void resume();
    void stop();
    void next();
    void previous();

    // --- Playlist management ---
    void setPlaylist(Playlist* playlist);
    Playlist* getPlaylist() const;

    // --- State queries ---
    PlaybackState getState() const;
    PlaybackMode getMode() const;
    Song* getCurrentSong() const;
    int getCurrentSongIndex() const;

    // --- Mode controls ---
    void setMode(PlaybackMode mode);

    // --- Main loop helpers ---
    /// Called every iteration of the main loop.
    /// Checks if the current song has ended and auto-advances.
    void tick();

    /// Returns the current playback position in seconds.
    float getCursorSec() const;

    /// Seeks forward (+) or backward (-) by the given seconds.
    void seekBy(int seconds);

private:
    ma_engine* engine_;
    ma_sound* sound_;

    PlaybackState state_;
    PlaybackMode mode_;
    Playlist* playlist_;
    int currentSongIndex_;
    Song* currentSong_;
    bool soundLoaded_;

    void startCurrentSong();
    void clearSound();
    void advanceToNext();
    void advanceToPrevious();
    int getNextShuffleIndex() const;
};

#endif
