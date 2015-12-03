#include "JZFileUtil.h"
#include "JZCommonDefine.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

string JZGetCurrentWorkingPath()
{
	char buff[512] = {0};
	string ret = "";
	getcwd(buff, sizeof(buff));
	ret = buff;
	return ret;
}

string JZGetAbsolutePath(const char* toResolvePath)
{
	if(NULL == toResolvePath)
	{
		return "";
	}
	char buff[512] = {0};
	string ret = "";
	realpath(toResolvePath, buff);
	ret = buff;
	return ret;
}

string JZTryToSearchFileUntilRoot(const char* searchBeginPath, const char* fileName)
{
	if(NULL == searchBeginPath || NULL == fileName)
	{
		return "";
	}
	string initPath = JZGetAbsolutePath(searchBeginPath);
	string curPath = initPath;
	string parentPath = curPath + "/../";
	parentPath = JZGetAbsolutePath(parentPath.c_str());
	do
	{
		string filePath = curPath + "/" + fileName;
		if(0 == access(filePath.c_str(), F_OK))
		{
			return filePath;
		}
		curPath = parentPath;
		parentPath += "/../";
		parentPath = JZGetAbsolutePath(parentPath.c_str());
	}while(parentPath != curPath);
	return "";
}

string JZGetFileDirectory(const char* fileFullPath)
{
	string path(fileFullPath);
	int lastSeperator = path.find_last_of(DIR_SEPERATOR);
	if (string::npos == lastSeperator) {
		return "";
	}
	string ret = path.substr(0, lastSeperator);
	return ret;
}

unsigned char* JZGetFileData(const char* fileFullPath, uint64* buffSize)
{
	//this func only useful for linux,os x, window,ios
	//but android system will fail to read assets' file,
	//android's assets' file is zip file,that is a hard work,
	//libz is needed.
	
	FILE* filePtr = fopen(fileFullPath, "rb");
	uint64 fileSize = 0;
	if (NULL == filePtr) {
		return NULL;
	}
	fseek(filePtr, 0, SEEK_END);
	fileSize = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);
	unsigned char *ret = (unsigned char*)malloc(fileSize * sizeof(char));
	fread(ret, 1, fileSize, filePtr);
	fclose(filePtr);

	*buffSize = fileSize;
	return ret;
}

bool JZFileAccessable(const char* filePath)
{
	if(0 == access(filePath, F_OK))
	{
		return true;
	}
	else
	{
		return false;
	}

}
