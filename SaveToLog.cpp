#include "SaveToLog.h"

int ResetLog()
{
    fstream fs;
    fs.open(FileName, fstream::trunc);
    if (fs.is_open())
    {
        fs << "LOG BEGIN\n";
        fs.close();
        return 1;
    }
    else
    {
        std::cout << "Error opening log file: " << FileName;
    }
    return 0;
}

int AddToLog(string msg)
{
    fstream fs;
    fs.open(FileName, fstream::app);
    if(fs.is_open())
    {
        fs << msg;
        fs.close();
        return 1;
    }else
    {
        std::cout << "Error opening log file: " << FileName;
    }
    return 0;
}