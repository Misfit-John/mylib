#ifndef __JZ_FILE_UTIL_H__
#define __JZ_FILE_UTIL_H__

#include <string>
using namespace std;

string JZGetCurrentWorkingPath();
string JZGetAbsolutePath(const char* toResolvePath);
string JZTryToSearchFileUntilRoot(const char* searchBeginPath, const char* fileName);

#endif //__JZ_FILE_UTIL_H__
