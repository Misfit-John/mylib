#include "JZFileUtil.h"
#include <stdlib.h>
#include <unistd.h>

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
