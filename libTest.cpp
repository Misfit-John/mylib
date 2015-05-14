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
	string realPaht = JZTryToSearchFileUntilRoot(curPath.c_str(),"abd");
	JZWRITE_DEBUG("cur path is  %s, and the .vimrc path is :%s ", curPath.c_str(), realPaht.c_str());
}
