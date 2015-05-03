#include "JZLogger.h"

int main(int argc,char* argv[])
{
	JZLoggerInit();
	JZSetLoggerLevel(JZ_LOG_ALL);
	JZSetLoggerOutPutStatue(1,1);
	JZSetLogFileName("testLog");
	JZWRITE_DEBUG("%s,%d","jz debug test",11);
	JZWRITE_ERROR("%s,%d","jz debug test",11);
}
