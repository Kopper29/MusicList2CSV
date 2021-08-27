#include "MusicFile.h"

using namespace std;

MusicFile::MusicFile(){
    this->tag = "";
    this->title = "";
    this->artist = "";
    this->album = "";
    this->year = "";
    this->comment = "";
    this->genre = 0;
    this->path = "";
}    

MusicFile::MusicFile(string tag, string title, string artist, string album, string year, string comment, int genre, string path){
    this->tag = tag;
    this->title = title;
    this->artist = artist;
    this->album = album;
    this->year = year;
    this->comment = comment;
    this->genre = genre;
    this->path = path;
}
              
bool MusicFile::isEmpty()
{
    return (this->artist.empty() || this->album.empty() || this->title.empty());
}              

string MusicFile::rmIlligalChars(string s)
{
    string new_s = "";
    //char *buf;
    //buf = (char*) malloc(s.size());

    char buf[500] = {0};

    if(buf == NULL)
        cout << "ERROR NULL BUFFER POINTER" << endl;
    //cout << "size of string: "<< s.size() << endl;
    strcpy(buf, s.c_str());

    for(int i = 0; i < s.size(); i++)
    {
        if( (buf[i] >= 32) && (buf[i] <= 126) ) //legal caracters are ascii values: [32 ... 126], else it is cut out.
            new_s = new_s+buf[i];
    }

    //free(buf);
    return new_s;
}

void MusicFile::set_title(string title)
{
    this->title = rmIlligalChars(title);
}

void MusicFile::set_artist(string artist)
{
    this->artist = rmIlligalChars(artist);
}

void MusicFile::set_album(string album)
{
    this->album = rmIlligalChars(album);
}