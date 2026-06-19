#include "Song.h"

Song::Song(std::string title, std::string artist, std::string album,
           std::string genre, int year, int durationSec, std::string filePath)
    : title_(std::move(title)),
      artist_(std::move(artist)),
      album_(std::move(album)),
      genre_(std::move(genre)),
      year_(year),
      durationSec_(durationSec),
      filePath_(std::move(filePath))
{
}

std::string Song::getTitle() const { return title_; }
std::string Song::getArtist() const { return artist_; }
std::string Song::getAlbum() const { return album_; }
std::string Song::getGenre() const { return genre_; }
int Song::getYear() const { return year_; }
int Song::getDurationSec() const { return durationSec_; }
std::string Song::getFilePath() const { return filePath_; }

std::string Song::getFormattedDuration() const
{
    int mins = durationSec_ / 60;
    int secs = durationSec_ % 60;
    std::string result;
    if (mins < 10) result += "0";
    result += std::to_string(mins) + ":";
    if (secs < 10) result += "0";
    result += std::to_string(secs);
    return result;
}
