/*
 * This file is part of the MusicList2CSV library
 *
 * Copyright (c) 2022, Jakob Akkermann Petersen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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