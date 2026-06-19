#ifndef SONG_H
#define SONG_H

#include <string>

class Song
{
private:
    std::string title_;
    std::string artist_;
    std::string album_;
    std::string genre_;
    int year_;
    int durationSec_;
    std::string filePath_;

public:
    Song(std::string title, std::string artist, std::string album,
         std::string genre, int year, int durationSec, std::string filePath);

    std::string getTitle() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    std::string getGenre() const;
    int getYear() const;
    int getDurationSec() const;
    std::string getFilePath() const;
};

#endif
