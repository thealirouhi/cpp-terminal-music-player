/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "Player.h"
#include <cstdlib>
#include <ctime>

Player::Player()
    : state_(STOPPED),
      mode_(NO_REPEAT),
      playlist_(nullptr),
      currentSongIndex_(-1),
      currentSong_(nullptr),
      soundLoaded_(false)
{
    srand(static_cast<unsigned>(time(nullptr)));
}

Player::~Player()
{
    clearSound();
}

// ========== Private helpers ==========

void Player::clearSound()
{
    soundLoaded_ = false;
}

void Player::startCurrentSong()
{
    if (currentSong_ == nullptr) return;
    clearSound();
    soundLoaded_ = true;
    state_ = PLAYING;
}

// ========== Playback controls ==========

void Player::play()
{
    if (playlist_ == nullptr || playlist_->getSongCount() == 0) return;

    if (state_ == STOPPED || state_ == PAUSED) {
        // If no song selected, start from the first song
        if (currentSong_ == nullptr) {
            currentSongIndex_ = 0;
            currentSong_ = playlist_->getSong(0);
        }
        startCurrentSong();
    }
}

void Player::pause()
{
    if (state_ == PLAYING) {
        state_ = PAUSED;
    }
}

void Player::resume()
{
    if (state_ == PAUSED) {
        state_ = PLAYING;
    }
}

void Player::stop()
{
    if (state_ != STOPPED) {
        state_ = STOPPED;
        clearSound();
    }
}

void Player::next()
{
    if (playlist_ == nullptr || playlist_->getSongCount() == 0) return;

    advanceToNext();

    if (currentSong_ != nullptr) {
        startCurrentSong();
    }
}

void Player::previous()
{
    if (playlist_ == nullptr || playlist_->getSongCount() == 0) return;

    advanceToPrevious();

    if (currentSong_ != nullptr) {
        startCurrentSong();
    }
}

// ========== Mode controls ==========

void Player::setMode(PlaybackMode mode)
{
    mode_ = mode;
}

// ========== Playlist management ==========

void Player::setPlaylist(Playlist* playlist)
{
    stop();
    playlist_ = playlist;
    currentSongIndex_ = -1;
    currentSong_ = nullptr;
}

Playlist* Player::getPlaylist() const
{
    return playlist_;
}

// ========== State queries ==========

Player::PlaybackState Player::getState() const
{
    return state_;
}

Player::PlaybackMode Player::getMode() const
{
    return mode_;
}

Song* Player::getCurrentSong() const
{
    return currentSong_;
}

int Player::getCurrentSongIndex() const
{
    return currentSongIndex_;
}

// ========== Navigation helpers ==========

void Player::advanceToNext()
{
    int total = playlist_->getSongCount();
    if (total == 0) {
        currentSong_ = nullptr;
        currentSongIndex_ = -1;
        state_ = STOPPED;
        return;
    }

    if (mode_ == REPEAT_ONE) {
        // Stay on the same song
        return;
    }

    int nextIndex;
    if (mode_ == SHUFFLE) {
        nextIndex = getNextShuffleIndex();
    } else {
        nextIndex = currentSongIndex_ + 1;
        if (nextIndex >= total) {
            if (mode_ == REPEAT_ALL) {
                nextIndex = 0;
            } else {
                // NO_REPEAT: stop at end
                currentSong_ = nullptr;
                currentSongIndex_ = -1;
                state_ = STOPPED;
                return;
            }
        }
    }

    currentSongIndex_ = nextIndex;
    currentSong_ = playlist_->getSong(currentSongIndex_);
}

void Player::advanceToPrevious()
{
    int total = playlist_->getSongCount();
    if (total == 0) {
        currentSong_ = nullptr;
        currentSongIndex_ = -1;
        state_ = STOPPED;
        return;
    }

    int prevIndex = currentSongIndex_ - 1;
    if (prevIndex < 0) {
        prevIndex = total - 1;
    }

    currentSongIndex_ = prevIndex;
    currentSong_ = playlist_->getSong(currentSongIndex_);
}

int Player::getNextShuffleIndex() const
{
    int total = playlist_->getSongCount();
    if (total <= 1) return 0;

    int next;
    do {
        next = rand() % total;
    } while (next == currentSongIndex_);

    return next;
}

// ========== Main loop helpers ==========

void Player::tick()
{
    // Will check if song ended via miniaudio in the next commit
}

float Player::getCursorSec() const
{
    // Will use miniaudio in the next commit
    return 0.0f;
}

void Player::seekBy(int seconds)
{
    // Will use miniaudio in the next commit
    (void)seconds;
}
