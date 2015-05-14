#include "JZLogger.h"
#include "JZFileUtil.h"
int main(int argc,char* argv[])
{
	JZLoggerInit();
	JZSetLoggerLevel(JZ_LOG_ALL);
	JZSetLoggerOutPutStatue(1,1);
	JZSetLogFileName("testLog");
	JZWRITE_DEBUG("%s,%d","jz debug test",11);
	JZWRITE_ERROR("%s,%d","jz debug test",11);
	string curPath = JZGetCurrentWorkingPath();
	string curPath_parent = curPath + "/../";
	string realPaht = JZGetAbsolutePath(curPath_parent.c_str());
	JZWRITE_DEBUG("cur path is  %s, and the parent's absolute path is :%s ", curPath.c_str(), realPaht.c_str());
}
