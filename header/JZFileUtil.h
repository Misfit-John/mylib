#ifndef __JZ_FILE_UTIL_H__
#define __JZ_FILE_UTIL_H__

#include <string>
using namespace std;

string JZGetCurrentWorkingPath();
string JZGetAbsolutePath(const char* toResolvePath);
string JZTryToSearchFileUntilRoot(const char* searchBeginPath, const char* fileName);
string JZGetFileDirectory(const char* fileFullPath);

//please remember to release the returned ptr by yourself
unsigned char* JZGetFileData(const char* fileFullPath);
#endif //__JZ_FILE_UTIL_H__
