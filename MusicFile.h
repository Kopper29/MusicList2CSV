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
