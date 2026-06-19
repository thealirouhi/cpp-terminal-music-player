/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "PlaylistViewScreen.h"
#include <iostream>
#include <algorithm>
#include <cctype>

PlaylistViewScreen::PlaylistViewScreen(UIRenderer& renderer,
    InputHandler& input, Player& player, Playlist*& currentPlaylist)
    : renderer_(renderer), input_(input), player_(player),
      currentPlaylist_(currentPlaylist),
      exited_(false), wantsFilter_(false), searchMode_(false),
      sortField_(0), sortAscending_(true), selectedSongIndex_(-1)
{
}

void PlaylistViewScreen::render()
{
    renderer_.clearScreen();
    renderer_.printBanner();

    string title = "Browse";
    if (currentPlaylist_ != nullptr) {
        title += ": " + currentPlaylist_->getName();
        title += " (" + to_string(currentPlaylist_->getSongCount()) + " songs)";
    }
    if (sortField_ != 0) {
        title += "  Sort: ";
        switch (sortField_) {
            case 1: title += "Title"; break;
            case 2: title += "Artist"; break;
            case 3: title += "Album"; break;
            case 4: title += "Year"; break;
            case 5: title += "Duration"; break;
        }
        title += sortAscending_ ? " ↑" : " ↓";
    }
    renderer_.drawTextLine(title, true);

    renderer_.drawDivider("╠", "═", "╣", "");

    if (currentPlaylist_ == nullptr || currentPlaylist_->getSongCount() == 0) {
        renderer_.drawTextLine("Playlist is empty.");
    } else if (displayedSongs_.empty()) {
        if (!searchQuery_.empty()) {
            renderer_.drawTextLine("No results for: \"" + searchQuery_ + "\"");
        } else {
            renderer_.drawTextLine("Playlist is empty.");
        }
    } else {
        renderer_.drawTextLine("#   Title                     Artist           Dur");
        for (size_t i = 0; i < displayedSongs_.size(); i++) {
            renderer_.printSongRow(static_cast<int>(i + 1),
                                   *displayedSongs_[i]);
        }
    }

    renderer_.drawDivider("╠", "═", "╣", "");

    if (searchMode_) {
        renderer_.printPrompt("Search: ");
    } else {
        renderer_.drawTextLine("[num] play  [s] sort  [/] search  [f] filter  [0] back");
    }

    renderer_.drawBottomBorder();
}

void PlaylistViewScreen::handleInput()
{
    if (searchMode_) {
        enterSearchMode();
        return;
    }

    string key = input_.readKey();

    if (key == "/") {
        enterSearchMode();
    } else if (key == "f") {
        wantsFilter_ = true;
        return;

    } else if (key == "s") {
        enterSortMode();
    } else if (key == "0") {
        exited_ = true;
        selectedSongIndex_ = -1;
        return;
    } else {
        // Try to parse as song number
        try {
            int songNum = stoi(key);
            if (songNum >= 1 &&
                songNum <= static_cast<int>(displayedSongs_.size())) {
                selectedSongIndex_ = songNum - 1;
            } else {
                cout << "No song at this index." << endl;
            }
        } catch (...) {
            // Invalid input — ignore
        }
    }
}

int PlaylistViewScreen::getSelectedSongIndex() const
{
    return selectedSongIndex_;
}

Song* PlaylistViewScreen::getSelectedSong() const
{
    if (selectedSongIndex_ < 0 ||
        selectedSongIndex_ >= static_cast<int>(displayedSongs_.size())) {
        return nullptr;
    }
    return displayedSongs_[selectedSongIndex_];
}

void PlaylistViewScreen::refreshDisplayedSongs()
{
    if (currentPlaylist_ == nullptr) {
        displayedSongs_.clear();
        return;
    }

    displayedSongs_ = currentPlaylist_->getSongs();
    applySearch();
    applySort();
}

void PlaylistViewScreen::enterSearchMode()
{
    searchMode_ = true;
    renderer_.printPrompt("Search: ");
    searchQuery_ = input_.readLine();
    searchMode_ = false;

    if (searchQuery_.empty()) {
        searchQuery_.clear();
    }

    refreshDisplayedSongs();
}

void PlaylistViewScreen::enterSortMode()
{
    cout << "Sort by:  1.Title  2.Artist  3.Album  4.Year  5.Dur" << endl;
    cout << "Add + for descending (e.g. 4+ for Year desc)" << endl;
    cout << "Sort choice: ";

    string input = input_.readLine();
    if (input.empty()) return;

    char lastChar = input.back();
    if (lastChar == '+') {
        sortAscending_ = false;
        input.pop_back();
    } else {
        sortAscending_ = true;
    }

    try {
        int choice = stoi(input);
        if (choice >= 1 && choice <= 5) {
            sortField_ = choice;
        }
    } catch (...) {
        // Invalid input — keep current sort
    }

    applySort();
}

void PlaylistViewScreen::applySort()
{
    if (sortField_ == 0) return;

    sort(displayedSongs_.begin(), displayedSongs_.end(),
        [this](Song* a, Song* b) {
            bool cmp = false;
            switch (sortField_) {
                case 1: cmp = a->getTitle() < b->getTitle(); break;
                case 2: cmp = a->getArtist() < b->getArtist(); break;
                case 3: cmp = a->getAlbum() < b->getAlbum(); break;
                case 4: cmp = a->getYear() < b->getYear(); break;
                case 5: cmp = a->getDurationSec() < b->getDurationSec(); break;
            }
            return sortAscending_ ? cmp : !cmp;
        });
}

void PlaylistViewScreen::applySearch()
{
    if (searchQuery_.empty()) return;

    string lowerQuery = searchQuery_;
    for (char& c : lowerQuery) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

    displayedSongs_.erase(
        remove_if(displayedSongs_.begin(), displayedSongs_.end(),
            [&](Song* song) {
                string title = song->getTitle();
                string artist = song->getArtist();
                for (char& c : title) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
                for (char& c : artist) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

                return title.find(lowerQuery) == string::npos &&
                       artist.find(lowerQuery) == string::npos;
            }),
        displayedSongs_.end());
}

bool PlaylistViewScreen::hasExited() const { return exited_; }
void PlaylistViewScreen::resetExit() { exited_ = false; wantsFilter_ = false; }

bool PlaylistViewScreen::getWantsFilter() const { return wantsFilter_; }
