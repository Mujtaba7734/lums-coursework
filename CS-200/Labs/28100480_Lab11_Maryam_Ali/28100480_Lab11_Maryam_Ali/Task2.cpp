#include "Task2.h"
#include "iostream"
using namespace std;

// ========== Song Constructor ==========
Song::Song(string t, string a) 
{
    this->title = t;
    this->artist = a;
    this->next = NULL;
    this->prev = NULL;
}

// ========== Playlist Constructor ==========
Playlist::Playlist() 
{
    this->head = nullptr;
    this->cursor = nullptr;
}

// ========== insertSong ==========
void Playlist::insertSong(const string& title, const string& artist) 
{
    Song* newSong = new Song(title, artist);
    if (this->head == NULL)
    {
        this->head = newSong;
        this->head->prev = newSong;
        this->head->next = newSong;
        this->cursor = newSong;
    }
    else
    {
        Song *temp = head->prev;
        temp->next = newSong;
        newSong->prev = temp;
        newSong->next = head; 
        this->head->prev = newSong;
    }
}

// ========== playCurrent ==========
string Playlist::playCurrent() 
{
    if (this->head == nullptr)
    {
        return "Playlist is empty.";
    }
    return "Now playing: " + cursor->title + " by " + cursor->artist;
}

// ========== playNext ==========
string Playlist::playNext() 
{
    if (this->head == nullptr)
    {
        return "Playlist is empty.";
    }
    this->cursor = this->cursor->next;
    return "Now playing: " + cursor->title + " by " + cursor->artist;
}

// ========== playPrev ==========
string Playlist::playPrev() 
{
    if (!this->cursor)
    {
        return "Playlist is empty.";
    }
    
    this->cursor = this->cursor->prev;
    return "Now playing: " + cursor->title + " by " + cursor->artist;
}

// ========== deleteSong ==========
bool Playlist::deleteSong(const string& title) 
{
    std::cout << title << endl;
    if (head == nullptr)
    {
        return false;
    }

    if (this->head->title == title)
    {
        if (this->head->next == nullptr)
        {
            delete this->head;
            this->head = nullptr;
            this->cursor = nullptr;
            return true;
        }
        
        Song *prev = this->head->prev;
        prev->next = head->next;

        if (cursor == head)
        {
            this->cursor = head->next;
        }

        delete this->head;
        this->head = prev->next;
        return true;
    }
    
    Song *temp = this->head->next;
    while (temp != this->head)
    {
        if (temp->title == title)
        {
            Song *prev = temp->prev;
            prev->next = temp->next;

            if (cursor == temp)
            {
                cursor = temp->next;
            }

            delete temp;;
            return true;
        }
        temp = temp->next;
    }
    return false;


}

// ========== searchSong ==========
string Playlist::searchSong(const string& title) const 
{
    if (head == nullptr)
    {
        return "Playlist is empty.";
    }
    if (this->head->title == title)
    {
        return "Found: " + head->title +  " by " + head->artist;
    }

    Song *temp = this->head->next;
    while (temp != this->head)
    {
        if (temp->title == title)
        {
            return "Found: " + temp->title +  " by " + temp->artist;
        }
        temp = temp->next;
    }    

    return "Song not found";
}

// ========== getPlaylistSize ==========
int Playlist::getPlaylistSize() const 
{
    
    if (head == NULL)
    {   
        return 0;
    }

    if (this->head->next == NULL)
    {
        return 1;
    }

    int count = 1;
    Song *temp = this->head->next;

    while (temp != this->head)
    {
        count++;
        temp = temp->next;
    }    
    return count;
}

// ========== clearPlaylist ==========
void Playlist::clearPlaylist() 
{
    if (head == nullptr)
    {
        return;
    }
    
    if (this->head->next == nullptr)
    {
        delete this->head;
        this->head = nullptr;
        this->cursor = nullptr;
        return;
    }
    Song *temp = this->head->next;
    while (temp != this->head)
    {
        delete this->head;
        this->head = temp;
    }    

    this->head = nullptr;
    this->cursor = nullptr;
}

// ========== Playlist Destructor ==========
Playlist::~Playlist() 
{
    clearPlaylist();
}