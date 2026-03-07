#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
using namespace std;

class Song {
public:
    string title;
    string artist;
    Song* next;
    Song* prev;

    Song(string title, string artist);
};

class Playlist {
private:
    Song* head;
    Song* cursor;

public:
    Playlist();
    ~Playlist();
    void insertSong(const string& title, const string& artist);
    string playCurrent();
    string playNext();
    string playPrev();
    bool deleteSong(const string& title);
    string searchSong(const string& title) const;
    int getPlaylistSize() const;
    void clearPlaylist();
};

#endif
