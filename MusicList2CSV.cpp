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
	Playlist Converter (single): CSV -> TXT
	MusicList2CSV.exe 1 C:\Users\Bruger\Dropbox\Musik\Pograms\BackupLister\hoilidayAway.txt

Program 2:
	Playlist Converter (multiple): CSV -> TXT
	MusicList2CSV.exe 2 C:\Users\Bruger\Dropbox\Musik\Pograms\BackupLister

Program 3:
	Library saver: LIB -> CSV
	MusicList2CSV.exe 3 F:\MusicB

Program 4:
	Playlist Converter (multiple): CSV -> M3U
	MusicList2CSV.exe 4 F:\MusicB  C:\Users\Bruger\Dropbox\Musik\Pograms\BackupLister
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

    MusicLib MyLib;

    //Adding music lib
    MyLib.LoadLibFiles(LibPath);

    //Adding music lists
    MyLib.AddListsFromDir(ListPath, "csv");

    //Save to M3U list file
    MyLib.PrintListsToM3Us("/storage/0000-0000/Music"); //Use .. of base is relative on main lib
    
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
        cout << "Program 1:" << endl;
        cout << "\tPlaylist Converter (single): TXT -> CSV" << endl;
        cout << "\tMusicList2CSV.exe 1 C:\\Users\\Bruger\\Dropbox\\Musik\\Pograms\\BackupLister\\hoilidayAway.txt" << endl;
        cout << "Program 2:" << endl;
        cout << "\tPlaylist Converter (multiple): TXT -> CSV" << endl;
        cout << "\tMusicList2CSV.exe 2 C:\\Users\\Bruger\\Dropbox\\Musik\\Pograms\\BackupLister" << endl;
        cout << "Program 3:" << endl;
        cout << "\tLibrary saver: LIB -> CSV" << endl;
        cout << "\tMusicList2CSV.exe 3 F:\\MusicB" << endl;
        cout << "Program 4:" << endl;
        cout << "\tPlaylist Converter (multiple): CSV -> M3U" << endl;
        cout << "\tMusicList2CSV.exe 4 F:\\MusicB  C:\\Users\\Bruger\\Dropbox\\Musik\\Pograms\\BackupLister" << endl;
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
    }else{
        string errmsg = "ERROR! INVALID PROGRAM SELECTION! try help\r\n";
        cout << errmsg;
        AddToLog(errmsg);
    }

    cout << "Program Has Ended" << endl;
    AddToLog("Program Has Ended");
    return rtnval;
}
