#include "Song.h"

Song::Song(string title, string artist, string album,
           string genre, int year, int durationSec, string filePath)
    : title(move(title)),
      artist(move(artist)),
      album(move(album)),
      genre(move(genre)),
      year(year),
      durationSec(durationSec),
      filePath(move(filePath))
{
}

string Song::getTitle() const { return title; }
string Song::getArtist() const { return artist; }
string Song::getAlbum() const { return album; }
string Song::getGenre() const { return genre; }
int Song::getYear() const { return year; }
int Song::getDurationSec() const { return durationSec; }
string Song::getFilePath() const { return filePath; }

string Song::getFormattedDuration() const
{
    int mins = durationSec / 60;
    int secs = durationSec % 60;
    string result;
    if (mins < 10) result += "0";
    result += to_string(mins) + ":";
    if (secs < 10) result += "0";
    result += to_string(secs);
    return result;
}
