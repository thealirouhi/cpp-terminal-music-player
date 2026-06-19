#include "Song.h"

Song::Song(string title, string artist, string album,
           string genre, int year, int durationSec, string filePath)
    : title_(move(title)),
      artist_(move(artist)),
      album_(move(album)),
      genre_(move(genre)),
      year_(year),
      durationSec_(durationSec),
      filePath_(move(filePath))
{
}

string Song::getTitle() const { return title_; }
string Song::getArtist() const { return artist_; }
string Song::getAlbum() const { return album_; }
string Song::getGenre() const { return genre_; }
int Song::getYear() const { return year_; }
int Song::getDurationSec() const { return durationSec_; }
string Song::getFilePath() const { return filePath_; }

string Song::getFormattedDuration() const
{
    int mins = durationSec_ / 60;
    int secs = durationSec_ % 60;
    string result;
    if (mins < 10) result += "0";
    result += to_string(mins) + ":";
    if (secs < 10) result += "0";
    result += to_string(secs);
    return result;
}
