#include "JZLogger.h"
#include "JZFileUtil.h"
#include "JZMarcoFunc.h"
#include "JZCmdParamHandler.h"
#include <sstream>
using namespace std;

struct mapStr
{
	int a;
	int b;
	int c;
	int d;
	int e;
};
class myCmdParm :public JZCmdParamHandler{
public:
	myCmdParm (){};
	virtual ~myCmdParm (){};

	void handle_a_param()
	{
		JZWRITE_DEBUG("a param");	
	}
	void handle_b_param(const string& arg)
	{
		JZWRITE_DEBUG("b param with arg %s", arg.c_str());	
	}

	void handle_c_var_param(const string& param)
	{
		JZWRITE_DEBUG("c parm with arg %s", param.c_str());	
	}
	void handleUnknowParam(char opt)
	{
		JZWRITE_DEBUG("unknow opt %c", opt);	
	}

	void handleNonOptParam(const string& param)
	{
		JZWRITE_DEBUG("no opt param : %s" ,param.c_str());	
	}
	virtual void init()
	{
		registerUnknowOptHandler((UnknowOptHandlerPtr)&myCmdParm::handleUnknowParam);		
		registerNonOptHandler((NonOptHandlerPtr)&myCmdParm::handleNonOptParam);
		registerOptArgHandlerPtr('b',(OptArgHandlerPtr)&myCmdParm::handle_b_param);		
		registerOptHandlerPtr('a',(OptHandlerPtr)&myCmdParm::handle_a_param);		
		registerOptArgHandlerPtr('c',(OptArgHandlerPtr)&myCmdParm::handle_c_var_param);		
	}

};


int main(int argc,char* argv[])
{
	char a = 'a';
	JZLoggerInit();
	JZSetLoggerLevel(JZ_LOG_ALL);
	JZSetLoggerOutPutStatue(1,1);
	JZSetLogFileName("testLog");
	myCmdParm parm;
	parm.analyze(argc, argv);
	
	JZWRITE_DEBUG("hellon");
	string testInput = "";
	for (int i = 0; i < 10000; i++) {
		JZWRITE_DEBUG("the i is : %d", i);
		testInput += 'a';
		JZWRITE_DEBUG(testInput.c_str());
	}
	
}



