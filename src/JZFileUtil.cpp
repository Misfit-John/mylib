#include "JZFileUtil.h"
#include "JZCommonDefine.h"
#include "JZLogger.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#ifdef _LINUX_
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h> 
#include <dirent.h>  
#endif

StringList JZGetAllFiles(const char* dir, bool deepSearch)
{
#ifdef _LINUX_
  // I didn't find any good idea to do this by std c lib. So I will have to call system api to do this now.
  DIR *dp = NULL;  
  struct dirent *entry = NULL;  
  struct stat statbuf; 
  StringList ret;

  if ((dp = opendir(dir)) == NULL) {  
    JZWRITE_DEBUG("can not open dir");
    return ret;  
  }

  chdir(dir);
  while ((entry = readdir(dp)) != NULL) {  
    lstat(entry->d_name, &statbuf);  
    if (S_ISDIR(statbuf.st_mode)) 
    {  
      if (deepSearch)
      {
        if (strcmp(entry->d_name, ".") == 0 ||   
            strcmp(entry->d_name, "..") == 0 )    
          continue;     
        StringList deepRet = JZGetAllFiles(entry->d_name, deepSearch);
        ret.insert(ret.end(), deepRet.begin(), deepRet.end());
      }
    }
    else
    {
      ret.push_back(entry->d_name);
    }
  }  
  chdir("..");
  closedir(dp);
  return ret;
#endif

}

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
