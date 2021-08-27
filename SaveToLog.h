#ifndef __SaveToLog__
#define __SaveToLog__

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define FileName "LOG.txt"

//Truncates the log file
int ResetLog();

//Append string to logfile
int AddToLog(string msg);


#endif