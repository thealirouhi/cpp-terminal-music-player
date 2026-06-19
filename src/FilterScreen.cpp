/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "FilterScreen.h"
#include <iostream>
#include <algorithm>

FilterScreen::FilterScreen(UIRenderer& renderer, InputHandler& input,
                           MusicLibrary& library, Playlist*& currentPlaylist)
    : renderer_(renderer), input_(input), library_(library),
      currentPlaylist_(currentPlaylist),
      exited_(false), filterType_(0), filterApplied_(false)
{
}

void FilterScreen::render()
{
    renderer_.clearScreen();
    renderer_.printBanner();

    string title = "Filter songs";
    if (currentPlaylist_ != nullptr) {
        title += " in: " + currentPlaylist_->getName();
    }
    renderer_.drawTextLine(title, true);
    renderer_.drawDivider("╠", "═", "╣", "");

    if (filterType_ == 0) {
        renderer_.drawLabelLine("Filter by", "");
        renderer_.drawTextLine("1.  Artist");
        renderer_.drawTextLine("2.  Album");
        renderer_.drawDivider("╠", "═", "╣", "");
        renderer_.drawTextLine("0.  Back");
    } else {
        string typeLabel = (filterType_ == 1) ? "Artists" : "Albums";
        renderer_.drawTextLine(typeLabel + " in " + currentPlaylist_->getName());

        for (size_t i = 0; i < filterValues_.size(); i++) {
            string line = to_string(i + 1) + ".  " + filterValues_[i];
            renderer_.drawTextLine(line);
        }

        renderer_.drawDivider("╠", "═", "╣", "");
        renderer_.drawTextLine("0.  Back");
    }

    renderer_.drawBottomBorder();
    renderer_.printPrompt("Choice: ");
}

void FilterScreen::handleInput()
{
    if (filterType_ == 0) {
        int choice = input_.readInt(0, 2);

        if (choice == 1) {
            filterType_ = 1;
            collectUniqueArtists();
        } else if (choice == 2) {
            filterType_ = 2;
            collectUniqueAlbums();
        } else {
            exited_ = true;
        }
        return;
    }

    int choice = input_.readInt(0,
        static_cast<int>(filterValues_.size()));

    if (choice == 0) {
        filterType_ = 0;
        filterApplied_ = false;
        exited_ = true;
        return;
    }

    int index = choice - 1;
    if (index >= 0 && index < static_cast<int>(filterValues_.size())) {
        selectedFilter_ = filterValues_[index];

        if (filterType_ == 1) {
            applyArtistFilter(selectedFilter_);
        } else {
            applyAlbumFilter(selectedFilter_);
        }
        filterApplied_ = true;
    }
}

void FilterScreen::collectUniqueArtists()
{
    filterValues_.clear();
    if (currentPlaylist_ == nullptr) return;

    for (Song* song : currentPlaylist_->getSongs()) {
        const string& artist = song->getArtist();
        if (find(filterValues_.begin(), filterValues_.end(), artist)
            == filterValues_.end()) {
            filterValues_.push_back(artist);
        }
    }
}

void FilterScreen::collectUniqueAlbums()
{
    filterValues_.clear();
    if (currentPlaylist_ == nullptr) return;

    for (Song* song : currentPlaylist_->getSongs()) {
        const string& album = song->getAlbum();
        if (find(filterValues_.begin(), filterValues_.end(), album)
            == filterValues_.end()) {
            filterValues_.push_back(album);
        }
    }
}

void FilterScreen::applyArtistFilter(const string& artist)
{
    filteredSongs_ = library_.filterByArtist(artist);
}

void FilterScreen::applyAlbumFilter(const string& album)
{
    filteredSongs_ = library_.filterByAlbum(album);
}

const vector<Song*>& FilterScreen::getFilteredSongs() const
{
    return filteredSongs_;
}

Playlist* FilterScreen::getFilteredPlaylist() const
{
    if (!filterApplied_ || filteredSongs_.empty()) {
        return nullptr;
    }

    return nullptr;  // The Application will handle this
}

bool FilterScreen::hasExited() const { return exited_; }
void FilterScreen::resetExit() { exited_ = false; }
