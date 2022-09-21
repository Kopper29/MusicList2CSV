#include "MusicLib.h"

#define MAX_FILE_NAME_LENGTH 1024
#define MAX_FILE_LINE_LENGTH 1024
#define MP3_Tag_Size 128

using namespace std;

MusicLib::MusicLib(){
    csvdelimiter = ";"; //Default csv delimiter
}

void MusicLib::AddError(string err)
{
    this->ErrorList.push_back(err);
}

 void MusicLib::PrintErrors()
 {
    if(this->ErrorList.size() > 0){
        cout << "!!! FOLLOWING ERRORS HAVE OCCURED: !!!" << endl;
        for(auto it = this->ErrorList.begin(); it != this->ErrorList.end(); it++){
            cout << *it << endl;
        }
    }
    else{
        cout << "NO ERRORS HAVE OCCURED" << endl;
    }
 }

void MusicLib::setCSVDelimiter(string newDelimiter)
{
    this->csvdelimiter = newDelimiter;
}

void MusicLib::AddListFromTxtFile(string FilePath){
    ifstream ListFile;
    
    //Open file
    ListFile.open(FilePath.c_str());
    if (ListFile){
        cout << "Successful open of " << FilePath << endl;
    }
    else{
        cerr << "***Aborting*** Could not open " << FilePath << endl;
        AddError(("Error 01 (in AddListFromTxtFile): Could not open: " + FilePath));
        return;
    }

    //Read file and add to lib
    string line;
    int i = 0;
    while(getline(ListFile, line))
    {
        MusicFile Mfile;
        MusicFile Mfile2;
        
        //First split: First and last of " - "
        size_t EndOfArtist = line.find(" - "); //find first
        size_t StartOfAlbum = EndOfArtist + 3;
        size_t EndOfAlbum = line.rfind(" - "); //find last
        size_t StartOfTitle = EndOfAlbum + 3;
        Mfile.set_artist(line.substr(0, EndOfArtist));
        Mfile.set_album(line.substr(StartOfAlbum, EndOfAlbum-StartOfAlbum));
        Mfile.set_title(line.substr(StartOfTitle, line.size() - StartOfTitle));
        /*
        if(Mfile.album.compare("?")){ //This char cannot be read by the MP3 reader.
            Mfile.set_album("-"); 
        }
        */
        this->MusicListFiles.push_back(Mfile);
        

        //Second split: First and second of " - "
        size_t EndOfAlbum2 = line.find(" - ",StartOfAlbum); //find first after artist
        size_t StartOfTitle2 = EndOfAlbum2 + 3;
        Mfile2.set_artist(line.substr(0, EndOfArtist));
        Mfile2.set_album(line.substr(StartOfAlbum, EndOfAlbum2-StartOfAlbum));
        Mfile2.set_title(line.substr(StartOfTitle2, line.size() - StartOfTitle2));
        this->MusicListFiles2.push_back(Mfile2);
        //cout << "added " << Mfile.title<<endl;
        i++;
    }
    cout << "Added: " << i << " songs to list." << endl;
    ListFile.close();
}

bool getline2(FILE *fp, string *sp)
{
    string s = "";
    char c = fgetc(fp);

    if(c == EOF)
    {
        *sp = s;
        return false;
    }

    while(c != '\n')
    {
        s = s + c;
        c = fgetc(fp);
        if(c == EOF)
        {
            *sp = s;
            return false;
        }
    }

    *sp = s;
    return true;
}

// void MusicLib::AddListFromCsvFile(string FilePath){
//     char ListLine[MAX_FILE_LINE_LENGTH];
//     char fileName[MAX_FILE_NAME_LENGTH + 1];
//     strcpy(fileName, FilePath.c_str());

//     FILE *fp;
//     fp = fopen(fileName, "rb");

//     //ifstream ListFile;
//     //ListFile.open(fileName);

//     //Open file
//     //if (ListFile){ cout << "Successful open of " << fileName << endl; }
//     //else{ cerr << "***Aborting*** Could not open " << fileName << endl; return; }

//     //Read file and add to lib
//     string line;
//     //getline(ListFile, line); //skip first line(only headers)
//     getline2(fp, &line);
//     while(getline2(fp, &line))// getline(ListFile, line))
//     {
//         size_t EndOfTitle = line.find(";");
//         size_t StartOfArtist = EndOfTitle + 1;
//         size_t EndOfArtist = line.find(";", StartOfArtist);
//         size_t StartOfAlbum = EndOfArtist + 1;
        
//         MusicFile Mfile;
//         Mfile.set_title(line.substr(0, EndOfTitle));
//         Mfile.set_artist(line.substr(StartOfArtist, EndOfArtist-StartOfArtist));
//         Mfile.set_album(line.substr(StartOfAlbum, line.size() - StartOfAlbum));
        
//         this->MusicListFiles.push_back(Mfile);
//     }
//     fclose(fp);
//     //ListFile.close;
// }

void MusicLib::AddListFromCsvFile(string FilePath){
    ifstream ListFile;
    
    //Open file
    ListFile.open(FilePath.c_str());
    if (ListFile){
        cout << "Successful open of " << FilePath << endl;
    }
    else{
        cerr << "***Aborting*** Could not open " << FilePath << endl;
        AddError(("Error 02 (in AddListFromCsvFile): Could not open: " + FilePath));
        return;
    }

    //Read file and add to lib
    string line;
    getline(ListFile, line); //skip first line (only headers)
    int i = 0;
    while(getline(ListFile, line))
    {
        size_t EndOfTitle = line.find(";");
        size_t StartOfArtist = EndOfTitle + 1;
        size_t EndOfArtist = line.find(";", StartOfArtist);
        size_t StartOfAlbum = EndOfArtist + 1;
        
        MusicFile Mfile;
        Mfile.set_title(line.substr(0, EndOfTitle));
        Mfile.set_artist(line.substr(StartOfArtist, EndOfArtist-StartOfArtist));
        Mfile.set_album(line.substr(StartOfAlbum, line.size() - StartOfAlbum));
        
        this->MusicListFiles.push_back(Mfile);
        i++;
    }
    cout << i << " songs loaded from list" << endl;
    ListFile.close();
}


string MusicLib::stringToUpper(string s){
    transform(s.begin(), s.end(),s.begin(), ::toupper);
    return s;
}

void MusicLib::FindListLibMatches(string PathName, string type)
{
    //Add this list
    if(type.compare("txt") == 0){
        AddListFromTxtFile(PathName);
    }
    else if(type.compare("csv") == 0){  
        AddListFromCsvFile(PathName);
    }else{
        AddError(("Error 10 (in FindListLibMatches): No Match For Type = \"txt\" or \"csv\". Type was: " + type));
    }

    //For each music file in the list
    for(auto it_list = this->MusicListFiles.begin(); it_list != this->MusicListFiles.end(); it_list++)
    {
        bool matchFound = false; 
        MusicFile listfile = *it_list;
        //For each music file in the lib
        for(auto it_lib = this->MusicLibFiles.begin(); it_lib != this->MusicLibFiles.end(); it_lib++)
        {
            MusicFile libfile = *it_lib;
            //Is list file a match?
            //cout << endl << "Compare with: " << libfile.artist << "; " << libfile.title << endl;
            if( (stringToUpper(listfile.album).compare(stringToUpper(libfile.album))==0) && (stringToUpper(listfile.artist).compare(stringToUpper(libfile.artist))==0) && (stringToUpper(listfile.title).compare(stringToUpper(libfile.title))==0))
            {
                //Add libfile to match
                this->MusicMatchFiles.push_back(libfile);
                matchFound = true;
            }
        }
        if( (!matchFound) && (type.compare("txt") == 0) ){ //Match not found, and from txt file, try alternative split
            cout << endl << "No match found for: "+listfile.artist+", "+listfile.album+", "+listfile.title+". Trying other split" << endl; 
            listfile = this->MusicListFiles2.at(it_list - this->MusicListFiles.begin()); //Alt Split

            //For each music file in the lib
            for(auto it_lib = this->MusicLibFiles.begin(); it_lib != this->MusicLibFiles.end(); it_lib++)
            {
                MusicFile libfile = *it_lib;
                //Is list file a match?
                //cout << endl << "Compare with: " << libfile.artist << "; " << libfile.title << endl;
                if( (stringToUpper(listfile.album).compare(stringToUpper(libfile.album))==0) && (stringToUpper(listfile.artist).compare(stringToUpper(libfile.artist))==0) && (stringToUpper(listfile.title).compare(stringToUpper(libfile.title))==0))
                {
                    //Add libfile to match
                    this->MusicMatchFiles.push_back(libfile);
                    matchFound = true;
                    cout << "Match found with other split: "+listfile.artist+", "+listfile.album+", "+listfile.title << endl;
                }
            }
        }
        if(!matchFound){ //Match not found
            cout << " !!! MATCH NOT FOUND FOR: " + listfile.artist + ", " + listfile.album + ", " + listfile.title << " !!! " << endl << endl;
            AddError(("Error 03 (in FindListLibMatches): No Match For: " + listfile.artist + ", " + listfile.album + ", " + listfile.title ));
        }
    }
    this->MusicListFiles.clear();
    this->MusicListFiles2.clear();
}

void MusicLib::PrintListsToM3Us(string M3UBasePath, string type)
{
    //For each list
    for(auto it_path = this->MusicListFilePaths.begin(); it_path != this->MusicListFilePaths.end(); it_path++)
    {
        //Find Listmatches:
        string PathName = (*it_path).string();
        FindListLibMatches(PathName, type);
        //PrintContent(this->MusicMatchFiles);
        
        //Print this list
        //Using only name
        //size_t ListNameBegin = PathName.find_last_of("\\")+1;
        //PrintListToM3U(PathName.substr(ListNameBegin, PathName.size()-ListNameBegin-4), M3UBasePath); //minus last 4 char ".m3u"
        
        //Using full path (save to same folder as csv)
        PrintListToM3U(PathName.substr(0, PathName.size()-4), M3UBasePath); //minus last 4 char ".m3u"
        

        //Clear this list
        this->MusicMatchFiles.clear();
        PrintListContent(this->MusicMatchFiles);
    }
}

void MusicLib::SaveListsAsMp3InFolder(string type)
{
    //For each list
    for(auto it_path = this->MusicListFilePaths.begin(); it_path != this->MusicListFilePaths.end(); it_path++)
    {
        //Find Listmatches:
        string PathName = (*it_path).string();
        FindListLibMatches(PathName, type);
        //PrintContent(this->MusicMatchFiles);
        
        //Using full path (save to a subfolder in same folder as csv)
        //Find folder name
        size_t fileNameBegin = PathName.find_last_of("\\")+1;
        string folderName = PathName.substr(fileNameBegin, PathName.size()-fileNameBegin-4);
        PathName = PathName.substr(0,fileNameBegin);

        cout<<"Path Name: "+PathName<<endl;
        cout<<"folderName: "+folderName<<endl;

        
        cout<<"Creating folder at: "+PathName+folderName+"\\"<<endl;
        filesystem::create_directory(PathName+folderName+"\\");
        SaveListedMusicFilesInFolder(PathName+folderName+"\\"); 
   
        //Clear this list
        this->MusicMatchFiles.clear();
        //PrintListContent(this->MusicMatchFiles);
    }
}


void MusicLib::AddListsFromDir(string DirPath, string type)
{
    this->MusicListFilePaths = AllDirFilePaths(DirPath);
    cout << "The Following Paths Have Been Found: " << endl;
    PrintPaths(this->MusicListFilePaths);
    cout << endl;

    this->MusicListFilePaths = KeepOnlyX(this->MusicListFilePaths, type);
    cout << "The Following List Paths Have Been Found: " << endl;
    PrintPaths(this->MusicListFilePaths);
    cout << endl;
}

void MusicLib::PrintMusicFileVectorToCSV(string CSVFileName, vector<MusicFile> mFiles)
{
    if( (CSVFileName.find(".csv") == string::npos) && (CSVFileName.find(".CSV") == string::npos))
        CSVFileName = CSVFileName + ".csv";
    
    ofstream ListFile;
    ListFile.open(CSVFileName, std::ios::trunc); //trunc to overwrite, use ::app to append

    //Open file
    if (ListFile.is_open()){
        ListFile << "Title" << this->csvdelimiter << "Artist" << this->csvdelimiter << "Album" << endl;
        for(auto it = mFiles.begin(); it != mFiles.end(); it++)
        {   
            MusicFile Mfile = *it;
            ListFile << Mfile.title << this->csvdelimiter;
            ListFile << Mfile.artist << this->csvdelimiter;
            ListFile << Mfile.album << endl;
        }
    }
    else{
        cout << "Failed to open the file: " << CSVFileName << endl;
        AddError(("Error 04 (in PrintMusicFileVectorToCSV): Could not open: " + CSVFileName));
    }
    ListFile.close();
}

void MusicLib::PrintListToCSV(string CSVFileName)
{
    PrintMusicFileVectorToCSV(CSVFileName, this->MusicListFiles);
}

void MusicLib::PrintListsToCSVs(){
    for(auto it = this->MusicListFilePaths.begin(); it != this->MusicListFilePaths.end(); it++)
    {
        //Add this list
        string PathName = (*it).string();
        AddListFromTxtFile(PathName);

        //Print this list
            //ONLY NAME
        //size_t ListNameBegin = PathName.find_last_of("\\")+1;
        //PrintListToCSV(PathName.substr(ListNameBegin, PathName.size()-ListNameBegin-4)); //minus last 4 char ".txt"
            //FULL PATH
        PrintListToCSV(PathName.substr(0, PathName.size()-4)); //minus last 4 char ".txt"

        //Clear this list
        this->MusicListFiles.clear();
    }
}

void MusicLib::PrintLibToCSV(string CSVFileName)
{
    PrintMusicFileVectorToCSV(CSVFileName, this->MusicLibFiles);
}

void MusicLib::PrintListToM3U(string M3UFileName, string M3UBasePath){
    if( (M3UFileName.find(".m3u") == string::npos) || (M3UFileName.find(".M3U") == string::npos))
        M3UFileName = M3UFileName + ".m3u";
    
    ofstream ListFile;
    ListFile.open(M3UFileName, std::ios::trunc); //trunc to overwrite, use ::app to append

    //Open file
    if (ListFile.is_open()){
        cout << "Successfull open of file: " << M3UFileName << endl;
        ListFile << "#EXTM3U" << endl;
        //PrintListContent(this->MusicMatchFiles);
        int i = 0;
        for(auto it = this->MusicMatchFiles.begin(); it != this->MusicMatchFiles.end(); it++)
        {
            //Add tag
            MusicFile Mfile = *it;
            ListFile << "#EXTINF:0,";

            //Add filename
            size_t filenameBegin = Mfile.path.find_last_of("\\")+2;
            string filename = Mfile.path.substr(filenameBegin, Mfile.path.size()-filenameBegin);
            ListFile << filename << endl;

            //Add relative path
            string relativePath = Mfile.path.substr(MusicLibDirPath.size(), Mfile.path.size()-MusicLibDirPath.size());
            relativePath = BackSlashSlashToSlash(relativePath);
            ListFile << M3UBasePath << relativePath << endl << endl;
            i++;
        }
        cout << i << " songs added" << endl;
        ListFile.close();
    }
    else{
        cout << "Failed to open the file: " << M3UFileName << endl;
        AddError(("Error 05 (in PrintListToM3U): Could not open: " + M3UFileName));     
    }
}

void MusicLib::SaveListedMusicFilesInFolder(string folderName){
    cout << "Copying listed files (total: " <<  this->MusicMatchFiles.size() << ")..." << endl;
    int i = 0;
    int j = 0;
    for(auto it = this->MusicMatchFiles.begin(); it != this->MusicMatchFiles.end(); it++)
    {
        //Add tag
        MusicFile Mfile = *it;

        size_t fileNameBegin = Mfile.path.find_last_of("\\")+1;
        string fileName = Mfile.path.substr(fileNameBegin, Mfile.path.size()-fileNameBegin);
        
        //cout << "Copying: " + Mfile.path << endl;
        if(!filesystem::copy_file(Mfile.path, folderName+fileName, filesystem::copy_options::overwrite_existing)){
            cout << "Failed to copy file: " << Mfile.path << endl;
            AddError(("Failed to copy file: " + Mfile.path));
            j++;  
        }
        i++;
    }
    cout << i << " songs copied/added" << endl;
    cout << j << " songs not copied/failed" << endl << endl;
}

void MusicLib::PrintPaths(vector<filesystem::path> v){
    for(auto it = v.begin(); it != v.end(); it++)
	{
        std::cout << *it << std::endl;
	}
}

vector<filesystem::path> MusicLib::KeepOnlyX(vector<filesystem::path> p, string X)
{
    //sorts a vector<filesystem::path>, such that noly paths leading to mp3 files are returned
    vector<filesystem::path> v;
    for(auto it = p.begin(); it != p.end(); it++)
	{
        string path = (*it).string();
        string type = path.substr(path.find_last_of(".") + 1); //Find file extension
        std::transform(type.begin(), type.end(), type.begin(), ::toupper); //Converts file extension to upper case.
        std::transform(X.begin(), X.end(), X.begin(), ::toupper); //Converts wanted file extension to upper case.
        if( (type == X) )
            v.push_back(*it);
	}

    return v;
}

string MusicLib::charArray2String(char* a, int index_start, int size)
{
    string s = ""; 
    for (int i = index_start; i < (index_start + size); i++) { 
        s = s + a[i]; 
    } 
    return s; 
}

string MusicLib::trim(const string& line)
{
    const char* WhiteSpace = " \t\v\r\n";
    std::size_t start = line.find_first_not_of(WhiteSpace);
    std::size_t end = line.find_last_not_of(WhiteSpace);
    return start == end ? std::string() : line.substr(start, end - start + 1);
}

string MusicLib::trim2(const string& line)
{
    const char* WhiteSpace = " ";
    std::size_t start = line.find_first_not_of(WhiteSpace);
    std::size_t end = line.find_last_not_of(WhiteSpace);
    return start == end ? std::string() : line.substr(start, end - start + 1);
}

string MusicLib::BackSlashSlashToSlash(string s)
{
    size_t pos = s.find("\\", 0);
    while (pos != string::npos)
    {
        s.replace(pos, 1, "/");
        pos = s.find("\\", 0);
    }
    return s;
}

MusicFile MusicLib::GetMP3Tag(filesystem::path mp3FilePaths)
{
    MusicFile mFile;
    char fileName[MAX_FILE_NAME_LENGTH + 1];
    ifstream mp3File;
    char buffer[MP3_Tag_Size + 1];

    string path = mp3FilePaths.string();
    strcpy(fileName, path.c_str());

    mp3File.open(fileName);
    buffer[MP3_Tag_Size] = '\0'; //just a precaution

    //Open file
    if (mp3File){
        cout << "Successful open of " << fileName << endl;
    }else{
        cerr << "***Aborting*** Could not open " << fileName << endl;
        AddError(("Error 06 (in GetMP3Tag): ***Aborting*** Could not open " + string(fileName) ));
        return mFile;
    }

    //Move file pointer to 128 bytes off the end of the file.
    mp3File.seekg(-(MP3_Tag_Size), ios::end);
    if (mp3File.fail()){
        cerr << "Could not seek, Aborting " << endl;
        AddError(("Error 07 (in GetMP3Tag): Could not seek, Aborting"));    
        return mFile;
    }

    //Get the data
    char tagbuffer[MP3_Tag_Size] = {0};
    mp3File.read(tagbuffer, MP3_Tag_Size);
    if (mp3File.fail()){
        cerr << "Could not read after seeking, Aborting " << endl;
        AddError(("Error 08 (in GetMP3Tag): Could not read after seeking, Aborting"));
        return mFile;
    }
    mp3File.close();

    mFile.tag = trim(charArray2String(tagbuffer, 0, 3));
    mFile.title = trim(charArray2String(tagbuffer, 3, 30));
    mFile.artist = trim(charArray2String(tagbuffer, 33, 30));
    mFile.album = trim(charArray2String(tagbuffer, 63, 30));
    mFile.year = trim(charArray2String(tagbuffer, 93, 30));
    mFile.comment = trim(charArray2String(tagbuffer, 123, 4));
    mFile.genre = (int)tagbuffer[127];
    mFile.path = path;

    return mFile;
}

vector<MusicFile> MusicLib::LoadMusicFiles(vector<filesystem::path> mp3FilePaths)
{
    vector<MusicFile> mFiles;
    for(auto it = mp3FilePaths.begin(); it != mp3FilePaths.end(); it++)
    {
        mFiles.push_back(GetMP3Tag(*it));     
    }
    return mFiles;
}

vector<filesystem::path> MusicLib::AllDirFilePaths(std::string DirPath)
{
    //Returns a vector containing all files and subdirectory files in the directory specified by DirPath
    //To only return files in the directory (non-subdirectory) use: filesystem::directory_iterator
    vector<filesystem::path> v;
    try
    {
        for (const auto & entry : filesystem::recursive_directory_iterator(DirPath))
        {
            if (entry.path().wstring().find(L"\u202E") != std::string::npos)
                continue;
            v.push_back(entry.path());
        }
    }
    catch (exception& e)
    {
        cout << e.what() << '\n';
    }

    return v;
}

void MusicLib::LoadLibFiles(string LibPath)
{
    //Store path to main lib:
    this->MusicLibDirPath = LibPath;
    cout << "Started Loading Lib: " << this->MusicLibDirPath << endl;

    //Get Path To all Files In the Dir
    this->MusicLibFilePaths = AllDirFilePaths(LibPath);
    //cout << "Following Files are in dir and subdir:" << endl;
    //PrintPaths(this->MusicLibFilePaths);

    //Remove NON-MP3 Files
    this->MusicLibFilePaths = KeepOnlyX(this->MusicLibFilePaths, "mp3");
    //cout << endl << "Following MP3 Files are in dir and subdir:" << endl;
    //PrintPaths(this->MusicLibFilePaths);

    //Load Music Files
    this->MusicLibFiles = LoadMusicFiles2(this->MusicLibFilePaths);
    //PrintContent(this->MusicLibFiles);
    cout << "Loading Lib Finished. No. of files loaded: " << this->MusicLibFiles.size() << endl;
}

void MusicLib::PrintContent(MusicFile mfile)
{
    cout << "Artist: " << mfile.artist << endl;
    cout << "Album: " << mfile.album << endl;
    cout << "Title: " << mfile.title << endl;
    cout << "Year: " << mfile.year << endl;
    cout << "Path: " << mfile.path << endl << endl;
}

void MusicLib::PrintListContent(vector<MusicFile> v)
{
    cout << "CONTENT OF LIST/LIB: " << endl;
    for(auto it = v.begin(); it != v.end(); it++)
    {
        MusicFile mfile = *it;
        PrintContent(*it);
    }
}

MusicFile MusicLib::GetMP3Tag2(filesystem::path mp3FilePaths)
{
    MusicFile mfile;
    char fileName[MAX_FILE_NAME_LENGTH + 1];
    string path = mp3FilePaths.string();
    strcpy(fileName, path.c_str());
    int errFlag = 0;

    ID3v2_tag* tag = load_tag(fileName, &errFlag);
    if(tag == NULL)
    {
        cout << "Error 09 (" << errFlag << ") (in GetMP3Tag2): tag is NULL -> for: " << path << endl;
        AddError("Error 09 (" + to_string(errFlag) + ") (in GetMP3Tag2): tag is NULL -> for: " + path);
        tag = new_tag();
        return mfile;
    }

    ID3v2_frame* frame_title = tag_get_title(tag);
    mfile.set_title(trim(convertToString(frame_title->data+1, frame_title->size-1)));

    ID3v2_frame* frame_artist = tag_get_artist(tag);
    mfile.set_artist(trim(convertToString(frame_artist->data+1, frame_artist->size-1)));

    ID3v2_frame* frame_album = tag_get_album(tag);
    mfile.set_album(trim(convertToString(frame_album->data+1, frame_album->size-1)));

    //genre not used, skip to ease
    //ID3v2_frame* frame = tag_get_genre(tag);
    //mfile.genre = convertToString(frame->data, frame->size);

    //year not used, but can give errors!
    // ID3v2_frame* frame_year = tag_get_year(tag);
    // mfile.year = trim(convertToString(frame_year->data, frame_year->size));
    
    mfile.path = path;

    return mfile;     
}

vector<MusicFile> MusicLib::LoadMusicFiles2(vector<filesystem::path> mp3FilePaths)
{
    vector<MusicFile> mFiles;
    int i = 0;
    try{
        for(auto it = mp3FilePaths.begin(); it != mp3FilePaths.end(); it++)
        {
            filesystem::path s(*it);
            //cout << i << " : " << s << endl;
            cout << ".";
            mFiles.push_back(GetMP3Tag2(*it));
            i++;     
        }
    }catch(exception& e){
        cout << e.what() << '\n';
    }
    cout << endl << "No of songs in lib: " << i << endl;
    return mFiles;
}

string MusicLib::convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

