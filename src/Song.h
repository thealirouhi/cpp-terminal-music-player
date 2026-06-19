#ifndef SONG_H
#define SONG_H

#include <string>
using namespace std;

class Song
{
private:
    string title;
    string artist;
    string album;
    string genre;
    int year;
    int durationSec;
    string filePath;

public:
    Song(string title, string artist, string album,
         string genre, int year, int durationSec, string filePath);

    string getTitle() const;
    string getArtist() const;
    string getAlbum() const;
    string getGenre() const;
    int getYear() const;
    int getDurationSec() const;
    string getFilePath() const;

    string getFormattedDuration() const;
};

#endif
