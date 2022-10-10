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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "MusicLib.h"
#include "MusicFile.h"
#include "SaveToLog.h"

/*
MusicList2CSV:

Program 1:
	Playlist Converter (single): TXT -> CSV
	MusicList2CSV.exe 1 C:\Users\Bruger\Dropbox\Musik\Pograms\BackupLister\hoilidayAway.txt

Program 2:
	Playlist Converter (multiple): TXT -> CSV
	MusicList2CSV.exe 2 C:\Users\Bruger\Dropbox\Musik\Pograms\BackupLister

Program 3:
	Library saver: LIB -> CSV
	MusicList2CSV.exe 3 G:\MusicA
	MusicList2CSV.exe 3 D:\Jakob\Music
	*If program crashes while loading files, the file might have missing info like title, album or artist
	*If program chrases with no dots, load has failed, this might be due to illigal characters: See LOG files
	*If tag is NULL (for itunes songs):
		1. Load the song into MP3Tag and save it, as it is.
		2. Open properties of the song (Alt+Enter)
		3. Edit a property and save it
		4. Reopen the song, fix the edited property back and save again
		5. The loading might still be wiered due to illigal characters like E_bar (E with bar over) or similar, fix this in the tag and save

Program 4:
	Playlist Converter (multiple): CSV -> M3U
	MusicList2CSV.exe 4 F:\MusicB C:\Users\Bruger\Dropbox\Musik\Pograms\BackupLister 000-0000
    *SD name can be found using the Filenamager+ app for android:
    *Jakobs SD:  0000-0000
	*Astrids SD: 52BC-2106

Program 5:
    Playlist Converter (multiple): txt -> CSV -> M3U. This combines Program 2 and Program 4.
    MusicList2CSV.exe 5 F:\MusicB C:\Users\Bruger\Dropbox\Musik\Pograms\BackupLister 000-0000
    MusicList2CSV.exe 5 D:\Jakob\Music  D:\Jakob\Dropbox\Musik\Pograms\BackupLister 0000-0000
    *Jakobs SD:  0000-0000
	*Astrids SD: 52BC-2106

Program 6:
    Same as 5, but no creation/use of csv files.
    Playlist Converter (multiple): txt -> M3U.
    MusicList2CSV.exe 6 F:\MusicB C:\Users\Bruger\Dropbox\Musik\Pograms\BackupLister 000-0000
    MusicList2CSV.exe 6 D:\Jakob\Music  D:\Jakob\Dropbox\Musik\Pograms\BackupLister 0000-0000
    *Jakobs SD:  0000-0000
	*Astrids SD: 52BC-2106
*/


//*************************************
//          FUNCTIONS
//*************************************
//MAIN FOR: MAKE ONE CSV FROM MUSIC ONE LIST (from phone)
int main01(char *argv[])
{
    string FilePath(argv[2]);

    MusicLib MyLib;
    MyLib.AddListFromTxtFile(FilePath);
    MyLib.PrintListToCSV("MyTestList");
    MyLib.PrintErrors();
    return 0;
}

//MAIN FOR: MAKE CSV FROM MUSIC LISTS (MULTIPLE) (from phone)
int main02(char *argv[])
{
    string DirPath(argv[2]);

    MusicLib MyLib;
    MyLib.AddListsFromDir(DirPath, "txt");
    MyLib.PrintListsToCSVs();
    MyLib.PrintErrors();
    return 0;
}

// MAIN FOR: MAKE CSV FROM MUSIC LIBARAY:
int main03(char *argv[])
{
    string LibPath(argv[2]);

    MusicLib MyLib;
    MyLib.LoadLibFiles(LibPath);
    MyLib.PrintLibToCSV("AllMusicInLib.csv");
    MyLib.PrintErrors();    
    return 0;
}

// MAIN FOR: MAKE M3U from CSV
int main04(char *argv[])
{
    string LibPath(argv[2]);
    string ListPath(argv[3]);
    string SDName(argv[4]);

    MusicLib MyLib;

    //Adding music lib
    MyLib.LoadLibFiles(LibPath);

    //Adding music lists
    MyLib.AddListsFromDir(ListPath, "csv");

    //Save to M3U list file
    MyLib.PrintListsToM3Us("/storage/"+SDName+"/Music", "csv"); //Use .. of base is relative on main lib
    
    MyLib.PrintErrors();
    return 0;
}

// MAIN FOR: MAKE M3U from CSV from txt (txt->m3u)
int main05(char *argv[])
{
    string LibPath(argv[2]);
    string ListPath(argv[3]);
    string SDName(argv[4]);

    MusicLib MyLib;

    //Adding txt files
    MyLib.AddListsFromDir(ListPath, "txt");

    //Print txt to csv
    MyLib.PrintListsToCSVs();

    //Adding music lib
    MyLib.LoadLibFiles(LibPath);

    //Adding music lists
    MyLib.AddListsFromDir(ListPath, "csv");

    //Save to M3U list file
    MyLib.PrintListsToM3Us("/storage/"+SDName+"/Music", "csv"); //Use .. of base is relative on main lib
    
    MyLib.PrintErrors();
    return 0;
}

// MAIN FOR: MAKE M3U from txt (direct conversion with extra check) (txt->m3u)
int main06(char *argv[])
{
    string LibPath(argv[2]);
    string ListPath(argv[3]);
    string SDName(argv[4]);

    MusicLib MyLib;

    //Adding txt files
    //MyLib.AddListsFromDir(ListPath, "txt");

    //Print txt to csv
    //MyLib.PrintListsToCSVs();

    //Adding music lib
    MyLib.LoadLibFiles(LibPath);

    //Adding music lists
    MyLib.AddListsFromDir(ListPath, "txt");

    //Save to M3U list file
    MyLib.PrintListsToM3Us("/storage/"+SDName+"/Music", "txt"); //Use .. of base is relative on main lib
    
    MyLib.PrintErrors();
    return 0;
}

// MAIN FOR: Print props of music file
int main07(char *argv[])
{
    string FilePath(argv[2]);
    MusicLib MyLib;

    MusicFile mfile = MyLib.GetMP3Tag2(FilePath);
    MyLib.PrintContent(mfile);

    MyLib.PrintErrors();
    return 0;
}

// MAIN FOR: SAVE PLAYLIST AS MP3 FILES IN A FOLDER (txt -> folder with mp3's)
int main08(char *argv[])
{
    string LibPath(argv[2]);
    string ListPath(argv[3]);

    MusicLib MyLib;

    //Adding music lib
    MyLib.LoadLibFiles(LibPath);

    //Adding music lists
    MyLib.AddListsFromDir(ListPath, "txt");

    //Save to M3U list file
    MyLib.SaveListsAsMp3InFolder("txt");

    //MyLib.PrintListsToM3Us("/storage/"+SDName+"/Music", "txt"); //Use .. of base is relative on main lib
    
    MyLib.PrintErrors();
    return 0;
}

//*************************************
//          MAIN
//*************************************
int main(int argc, char *argv[])
{
    cout << "Program Has Started" << endl;
    string program = argv[1];
    int rtnval = 0;

    ResetLog();

    if(program.compare("help") == 0){
        cout << endl << "MusicList2CSV:" << endl;
        cout << "General Format Description:" << endl;
        cout << "MusicList2CSV.exe <Program No.> <Path 1> ... <Path n>" << endl << endl;
        cout << "If the fields are empty -> use mp3tag to save the music file, and use properies to edit, save, reedit and save." << endl << endl;
        
        cout << "Program 1:" << endl;
        cout << "\tPlaylist Converter (single): TXT -> CSV" << endl;
        cout << "\t<Program No.> = 1, <Path 1> = fulle path of .txt playlist. Example:" << endl;
        cout << "\tMusicList2CSV.exe 1 C:\\Users\\Bruger\\Dropbox\\Musik\\Pograms\\BackupLister\\hoilidayAway.txt" << endl << endl;

        cout << "Program 2:" << endl;
        cout << "\tPlaylist Converter (multiple): TXT -> CSV" << endl;
        cout << "\t<Program No.> = 2, <Path 1> = Directory path of .txt playlists (multiple). Example:" << endl;
        cout << "\tMusicList2CSV.exe 2 C:\\Users\\Bruger\\Dropbox\\Musik\\Pograms\\BackupLister" << endl << endl;
        
        cout << "Program 3:" << endl;
        cout << "\tLibrary saver: LIB -> CSV" << endl;
        cout << "\t<Program No.> = 3, <Path 1> = Base Directory path of music libaray. Example:" << endl;
        cout << "\tMusicList2CSV.exe 3 F:\\MusicB" << endl << endl;
        
        cout << "Program 4:" << endl;
        cout << "\tPlaylist Converter (multiple): CSV -> M3U" << endl;
        cout << "\t<Program No.> = 4, <Path 1> = Base Directory path of music libaray, <Path 2> = Directory path of .csv playlists (multiple), <Path 3> = Name of the SD card. Example:" << endl;
        cout << "\tMusicList2CSV.exe 4 F:\\MusicB C:\\Users\\Bruger\\Dropbox\\Musik\\Pograms\\BackupLister 0000-0000" << endl << endl;
        
        cout << "Program 5:" << endl;
        cout << "\tPlaylist Converter (multiple): txt -> CSV -> M3U" << endl;
        cout << "\t<Program No.> = 5, <Path 1> = Base Directory path of music libaray, <Path 2> = Directory path of .txt playlists (multiple) that will be converted into .csv, <Path 3> = Name of the SD card. Example:" << endl;
        cout << "\tMusicList2CSV.exe 5 F:\\MusicB C:\\Users\\Bruger\\Dropbox\\Musik\\Pograms\\BackupLister 0000-0000" << endl << endl;

        cout << "Program 6:" << endl;
        cout << "\tPlaylist Converter (multiple, Direct with extra checks): txt -> M3U" << endl;
        cout << "\t<Program No.> = 6, <Path 1> = Base Directory path of music libaray, <Path 2> = Directory path of .txt playlists (multiple) that will be converted into .csv, <Path 3> = Name of the SD card. Example:" << endl;
        cout << "\tMusicList2CSV.exe 6 F:\\MusicB C:\\Users\\Bruger\\Dropbox\\Musik\\Pograms\\BackupLister 0000-0000" << endl << endl;

        cout << "Program 7:" << endl;
        cout << "\tPrint Properties of single music file: txt -> CSV -> M3U" << endl;
        cout << "\t<Program No.> = 7, <Path 1> = Path to music file. Example:" << endl;
        cout << "\tMusicList2CSV.exe 7 D:\\Jakob\\Music\\Doja Cat\\Kiss Me More (feat. SZA) - Single\\01 Kiss Me More (feat. SZA).mp3" << endl << endl;

        cout << "Program 8:" << endl;
        cout << "\tSave Playlist files in a folder: txt -> mp3's in a folder" << endl;
        cout << "\t<Program No.> = 8, <Path 1> = Base Directory path of music libaray, <Path 2> = Directory path of .txt playlists (multiple). Example:" << endl;
        cout << "\tMusicList2CSV.exe 8 D:\\Jakob\\Music D:\\Jakob\\Documents\\PlaylistTestFolder" << endl << endl;

        
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
    }else if(program.compare("1") == 0){
        rtnval = main01(argv);
    }else if(program.compare("2") == 0){
        rtnval = main02(argv);
    }else if(program.compare("3") == 0){
        rtnval = main03(argv);     
    }else if(program.compare("4") == 0){
        rtnval = main04(argv);  
    }else if(program.compare("5") == 0){
        rtnval = main05(argv);  
    }else if(program.compare("6") == 0){
        rtnval = main06(argv);  
    }else if(program.compare("7") == 0){
        rtnval = main07(argv);  
    }else if(program.compare("8") == 0){
        rtnval = main08(argv);  
    }else{
        string errmsg = "ERROR! INVALID PROGRAM SELECTION! try help\r\n";
        cout << errmsg;
        AddToLog(errmsg);
    }

    cout << "Program Has Ended" << endl;
    AddToLog("Program Has Ended");
    return rtnval;
}
