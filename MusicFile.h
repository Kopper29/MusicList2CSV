#ifndef __MusicFile__
#define __MusicFile__

#include <string>
#include <string>
#include <iostream>
#include "SaveToLog.h"

using namespace std;

class MusicFile{
    public:
    MusicFile();
    MusicFile(string tag,
              string title,
              string artist,
              string album,
              string year,
              string comment,
              int genre,
              string path); // constructor
    //~MusicFile();           // destructor

    void set_title(string title);
    void set_artist(string artist);
    void set_album(string album);

    string tag;
    string title;
    string artist;
    string album;
    string year;
    string comment;
    int genre;
    string path;

    bool isEmpty();

    private:
    string rmIlligalChars(string s);
};

#endif
