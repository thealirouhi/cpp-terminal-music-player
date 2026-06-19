/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Player::Player()
    : engine_(nullptr),
      sound_(nullptr),
      state_(STOPPED),
      mode_(NO_REPEAT),
      playlist_(nullptr),
      currentSongIndex_(-1),
      currentSong_(nullptr),
      soundLoaded_(false)
{
    srand(static_cast<unsigned>(time(nullptr)));

    engine_ = new ma_engine();
    ma_result result = ma_engine_init(nullptr, engine_);
    if (result != MA_SUCCESS) {
        cerr << "Error: Failed to initialize audio engine." << endl;
    }
}

Player::~Player()
{
    clearSound();
    if (engine_ != nullptr) {
        ma_engine_uninit(engine_);
        delete engine_;
    }
}

// ========== Private helpers ==========

void Player::clearSound()
{
    if (soundLoaded_) {
        ma_sound_uninit(sound_);
        soundLoaded_ = false;
    }
}

void Player::startCurrentSong()
{
    if (currentSong_ == nullptr) return;

    clearSound();

    // Build the full path: the file paths in CSV are relative (e.g. "Musics/...")
    string filePath = "Data/" + currentSong_->getFilePath();

    ma_result result = ma_sound_init_from_file(engine_, filePath.c_str(),
                                               0, nullptr, nullptr, sound_);
    if (result != MA_SUCCESS) {
        cerr << "Error: Could not load audio file: " << filePath << endl;

        // Skip to next song
        currentSong_ = nullptr;
        currentSongIndex_ = -1;
        state_ = STOPPED;
        return;
    }

    soundLoaded_ = true;
    ma_sound_start(sound_);
    state_ = PLAYING;
}

// ========== Playback controls ==========

void Player::play()
{
    if (playlist_ == nullptr || playlist_->getSongCount() == 0) return;

    if (state_ == PAUSED) {
        resume();
        return;
    }

    if (state_ == STOPPED) {
        if (currentSong_ == nullptr) {
            currentSongIndex_ = 0;
            currentSong_ = playlist_->getSong(0);
        }
        startCurrentSong();
    }
}

void Player::pause()
{
    if (state_ == PLAYING && soundLoaded_) {
        ma_sound_stop(sound_);
        state_ = PAUSED;
    }
}

void Player::resume()
{
    if (state_ == PAUSED && soundLoaded_) {
        ma_sound_start(sound_);
        state_ = PLAYING;
    }
}

void Player::stop()
{
    if (state_ != STOPPED) {
        if (soundLoaded_) {
            ma_sound_stop(sound_);
            ma_sound_seek_to_pcm_frame(sound_, 0);
        }
        state_ = STOPPED;
    }
}

void Player::next()
{
    if (playlist_ == nullptr || playlist_->getSongCount() == 0) return;

    advanceToNext();

    if (currentSong_ != nullptr) {
        startCurrentSong();
    } else {
        state_ = STOPPED;
    }
}

void Player::previous()
{
    if (playlist_ == nullptr || playlist_->getSongCount() == 0) return;

    advanceToPrevious();

    if (currentSong_ != nullptr) {
        startCurrentSong();
    } else {
        state_ = STOPPED;
    }
}

void Player::playSongAt(int index)
{
    if (playlist_ == nullptr) return;

    stop();
    currentSongIndex_ = index;
    currentSong_ = playlist_->getSong(index);
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
    if (state_ != PLAYING) return;
    if (!soundLoaded_) return;

    if (ma_sound_at_end(sound_)) {
        next();
    }
}

float Player::getCursorSec() const
{
    if (!soundLoaded_) return 0.0f;

    ma_uint64 frames;
    ma_result result = ma_sound_get_cursor_in_pcm_frames(sound_, &frames);
    if (result != MA_SUCCESS) return 0.0f;

    ma_uint32 sampleRate = ma_engine_get_sample_rate(engine_);
    return static_cast<float>(frames) / static_cast<float>(sampleRate);
}

void Player::seekBy(int seconds)
{
    if (!soundLoaded_) return;

    ma_uint64 cursor, length;
    ma_sound_get_cursor_in_pcm_frames(sound_, &cursor);
    ma_sound_get_length_in_pcm_frames(sound_, &length);

    ma_uint32 rate = ma_engine_get_sample_rate(engine_);
    ma_int64 newFrame = static_cast<ma_int64>(cursor)
                        + static_cast<ma_int64>(seconds) * rate;

    if (newFrame < 0) newFrame = 0;
    if (static_cast<ma_uint64>(newFrame) >= length) {
        next();
        return;
    }

    ma_sound_seek_to_pcm_frame(sound_,
                               static_cast<ma_uint64>(newFrame));
}
