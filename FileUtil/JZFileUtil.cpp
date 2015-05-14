#include "JZFileUtil.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
	char buff[512] = {0};
	string ret = "";
	realpath(toResolvePath, buff);
	ret = buff;
	return ret;
}

string JZTryToSearchFileUntilRoot(const char* searchBeginPath, const char* fileName)
{
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
