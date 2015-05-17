#include "JZLogger.h"
#include "JZFileUtil.h"
#include "JZMarcoFunc.h"

#include <sstream>
using namespace std;

void nullTest()
{
	char *input = NULL;
	JZIF_NULL_RETURN(input);

}

int main(int argc,char* argv[])
{
	JZLoggerInit();
	JZSetLoggerLevel(JZ_LOG_ALL);
	JZSetLoggerOutPutStatue(1,1);
	JZSetLogFileName("testLog");
	JZWRITE_DEBUG("%s,%d","jz debug test",11);
	JZWRITE_ERROR("%s,%d","jz debug test",11);
	string curPath = JZGetCurrentWorkingPath();
	string realPaht = JZTryToSearchFileUntilRoot(curPath.c_str(),"testLog");
	string dir = JZGetFileDirectory(realPaht.c_str());
	JZWRITE_DEBUG("cur path is  %s, and the testLog path is :%s ,the directory of testLog is : %s", curPath.c_str(), realPaht.c_str(), dir.c_str());

	unsigned char * input = JZGetFileData(realPaht.c_str());
	stringstream ioStream;
	string line;

	ioStream << input;
	getline(ioStream, line);
	JZWRITE_DEBUG("%s", line.c_str());
	nullTest();
}

