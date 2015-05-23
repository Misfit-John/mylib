#include "JZCmdParamHandler.h"
#include "JZLogger.h"
#include "JZMarcoFunc.h"
#include <stdio.h>
#include <unistd.h>

JZCmdParamHandler::JZCmdParamHandler()
{
	mUnknowOptHandler = NULL;
	mNonOptHandler = NULL;
	mSwitchMark = "";
}

bool JZCmdParamHandler::registerUnknowOptHandler(UnknowOptHandlerPtr ptr)
{
	mUnknowOptHandler = ptr;
	JZIF_NULL_RETURN(ptr, false);
	return true;
}

bool JZCmdParamHandler::registerNonOptHandler(NonOptHandlerPtr ptr)
{
	mNonOptHandler = ptr;
	JZIF_NULL_RETURN(ptr, false);
	return true;
}

bool JZCmdParamHandler::registerOptHandlerPtr(char opt, OptHandlerPtr ptr)
{
	JZIF_NULL_RETURN(ptr, false);
	mOptHandlerMap[opt] = ptr;
	mSwitchMark += opt;
	return true;
}

bool JZCmdParamHandler:: registerOptArgHandlerPtr(char opt, OptArgHandlerPtr ptr)
{
	JZIF_NULL_RETURN(ptr, false);
	mOptArgHandlerMap[opt] = ptr;
	mSwitchMark += opt;
	mSwitchMark += ":";
	return true;
}
/*
bool JZCmdParamHandler::registerOptVarArgHandlerPtr(char opt, OptArgHandlerPtr ptr)
{
	JZIF_NULL_RETURN(ptr, false);
	mOptArgHandlerMap[opt] = ptr;
	mSwitchMark += opt;
	mSwitchMark += "::";
	return true;
}
*/
void JZCmdParamHandler::analyze(int argc, char *argv[])
{
	init();
	char opt;
	int offset= 0;
	while(offset < argc)
	{
		while((opt = getopt(argc - offset ,argv + offset , mSwitchMark.c_str())) != -1)
		{
			switch(opt)
			{
				case '?':
				{
					(this->*mUnknowOptHandler)(optopt);
					break;	
				}	
				default:
				{
					do
					{
						auto optIt = mOptHandlerMap.find(opt);
						if (mOptHandlerMap.end() != optIt && optIt->second != NULL) {
							(this->*optIt->second)();
							break;
						}
						auto optArgIt = mOptArgHandlerMap.find(opt);
						if (mOptArgHandlerMap.end() != optArgIt && optArgIt->second != NULL) {
							(this->*optArgIt->second)(optarg);
							break;
						}
					}while(0);
					//unreach able
					break;
				}
			}
		};
		if (optind + offset < argc) {
			if(NULL != mNonOptHandler)
			{
				(this->*mNonOptHandler)(argv[offset + optind ]);	
			}
		}
		offset += optind;
	}
}



