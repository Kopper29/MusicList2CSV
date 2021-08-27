#ifndef __MusicLib__
#define __MusicLib__

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <filesystem>
#include "MusicFile.h"
#include "id3v2lib.h"
#include "SaveToLog.h"

using namespace std;

class MusicLib {
    
    public:
    MusicLib(); //Constructor
    //~MusicLib(); //Destructor
    void setCSVDelimiter(string newDelimiter); //Set Delimiter for the csv file (std. is ";")
    void LoadLibFiles(string LibPath); //Loads all MP3 Files found in the LibPath and its subdirectories
    void AddListFromTxtFile(string FilePath); //Add music list from Phone Backup txt file
    void AddListFromCsvFile(string FilePath); //Add music list from Phone Backup csv file
    void AddListsFromDir(string DirPath, string type); //Add multiple list from Phone Backup files located in same dir 

    void PrintListToCSV(string CSVFileName); //Printing the List to a CSV file
    void PrintListsToCSVs(); //Printing the List to a CSV file
    void PrintLibToCSV(string CSVFileName); //Printing the Lib to a CSV file
    void PrintListsToM3Us(string M3UBasePath); //Prints the List to a M3U file, based on the Lib paths
    void PrintListToM3U(string M3UFileName, string M3UBasePath); //Prints the List to a M3U file, based on the Lib paths
    void PrintPaths(vector<filesystem::path> v); //Prints paths of file
    void PrintContent(MusicFile mfile);
    void PrintListContent(vector<MusicFile> v);
    void PrintErrors();

    private:
    //Errors
    vector<string> ErrorList;
    void AddError(string err);

    //Data structures
    string csvdelimiter; //csv delimiter
    vector<MusicFile> MusicListFiles; //Vector of music in a list
    vector<MusicFile> MusicLibFiles; //vector of music in a lib
    vector<MusicFile> MusicMatchFiles; //Vector of music in a list
    string MusicLibDirPath; //path to lib

    vector<filesystem::path> AllDirFilePaths(std::string DirPath); //vector of all paths in lib dir
    vector<filesystem::path> MusicLibFilePaths; //vector of path to mp3 files in lib
    vector<filesystem::path> MusicListFilePaths; //vector of path to list files in lib
    vector<filesystem::path> KeepOnlyX(vector<filesystem::path> p, string X); //Removes all file paths not leading to .X files (not case sensitive)
    
    MusicFile GetMP3Tag(filesystem::path mp3FilePaths); //returns the tags (MusicFile) from the file of the file path (must be mp3!)
    MusicFile GetMP3Tag2(filesystem::path mp3FilePaths); //returns the tags (MusicFile) from the file of the file path (must be mp3!)
    vector<MusicFile> LoadMusicFiles(vector<filesystem::path> mp3FilePaths); //returns a vector of music files from a vector of mp3 paths 
    vector<MusicFile> LoadMusicFiles2(vector<filesystem::path> mp3FilePaths);
    string charArray2String(char* a, int index_start, int size); //char array to string converter
    void PrintMusicFileVectorToCSV(string CSVFileName, vector<MusicFile> mFiles); //prints a vector of MusicFiles to CSV
    string trim(const string& line); //trims a string, by removing white spaces
    string MusicLib::trim2(const string& line);
    string BackSlashSlashToSlash(string s);
    string MusicLib::convertToString(char* a, int size);
    void FindListLibMatches(string PathName);
    
};

#endif
