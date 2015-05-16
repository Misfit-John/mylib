#include "JZLogger.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

FILE* mJZLoggerFILEPtr;
char* mJZLoggerFilePath;
int mJZLogLevel;
int mJZLogIsToConsel;
int mJZLogIsToFile;

void JZLoggerInit()
{
	mJZLogLevel 		= JZ_LOG_OFF;
	mJZLoggerFilePath 	= NULL;
	mJZLoggerFILEPtr	= NULL;
	mJZLogIsToFile 		= 0;
	mJZLogIsToConsel 	= 0;
}

void JZLoggerFin()
{
	if(NULL != mJZLoggerFILEPtr)
	{
		fclose(mJZLoggerFILEPtr);
		mJZLoggerFILEPtr = NULL;
	}	
	if(NULL != mJZLoggerFilePath)
	{
		free(mJZLoggerFilePath);
		mJZLoggerFilePath = NULL;
	}
}
int JZGetDebugLevel()
{
	return mJZLogLevel;
}

void JZSetLoggerLevel(int level)
{
	mJZLogLevel = level;	
}

void JZSetLoggerOutPutStatue(int toConsole, int toFile)
{
	mJZLogIsToConsel = toConsole;
	mJZLogIsToFile 	= toFile;	
}

void JZSetLogFileName(const char* filename)
{
	if (NULL == filename) {
		return;
	}
	int fileNameLen = strlen(filename);
	mJZLoggerFilePath = (char*)malloc(fileNameLen * sizeof(char));
	strncpy(mJZLoggerFilePath, filename, fileNameLen);

	mJZLoggerFILEPtr = fopen(filename, "ab");
}

void JZWriteLog(const char* log)
{
	if (NULL == log) {
		return;
	}
	if(1 == mJZLogIsToConsel)
	{
		fprintf(stdout,"%s", log);
	}
	
	if(1 == mJZLogIsToFile && NULL != mJZLoggerFILEPtr)
	{
		fprintf(mJZLoggerFILEPtr,"%s", log);
	}	
}
