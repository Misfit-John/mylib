#ifndef JZCMDPARAMHANDLER_H
#define JZCMDPARAMHANDLER_H

#include <string>
#include <map>
using namespace std;

class JZCmdParamHandler;
typedef void (JZCmdParamHandler::*OptHandlerPtr)();
typedef void (JZCmdParamHandler::*UnknowOptHandlerPtr)(char opt);
typedef	void (JZCmdParamHandler::*OptArgHandlerPtr)(const string&);
typedef void (JZCmdParamHandler::*NonOptHandlerPtr)(const string&);

typedef map<char, OptHandlerPtr> OptHandlerMap;
typedef map<char, OptArgHandlerPtr> OptArgHandlerMap;

class JZCmdParamHandler {
public:
	JZCmdParamHandler();
	virtual ~JZCmdParamHandler (){};

	virtual void init() = 0;
	void analyze(int argc, char *argv[]);

protected:
	bool registerUnknowOptHandler(UnknowOptHandlerPtr ptr);
	bool registerNonOptHandler(NonOptHandlerPtr ptr);
	bool registerOptHandlerPtr(char opt, OptHandlerPtr ptr);
	bool registerOptArgHandlerPtr(char opt, OptArgHandlerPtr ptr);

//	not all system can support :: arg, so this rigister is aborted
//	bool registerOptVarArgHandlerPtr(char opt, OptArgHandlerPtr ptr);
	
private:
	string mSwitchMark;
	UnknowOptHandlerPtr mUnknowOptHandler;
	NonOptHandlerPtr mNonOptHandler;
	OptArgHandlerMap mOptArgHandlerMap;
	OptHandlerMap mOptHandlerMap;
};

#endif /* end of include guard: JZCMDPARAMHANDLER_H */
