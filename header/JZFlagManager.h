#ifndef JZFLAGMANAGER_H
#define JZFLAGMANAGER_H

#include "JZCommonDefine.h"
#include <map>
using namespace std;

class JZFlagManager {
public:
	JZFlagManager ();
	virtual ~JZFlagManager ();

	//if can not set to that flag, return false
	bool setFlag(int flag, int state = 1);

	//resetFlag(flag) == setFlag(flag, 0)
	bool resetFlag(int flag);

	int getFlagState(int flag);

	//return true by default,
	//if you need to check it,
	//just over write it
	virtual bool canSetFlagToState(int flag, int state);

	//only one of these flags can be set to nonzero
	void setMutuallyFlag(IntList flags);

private:
	bool isMutually(int flag);
	IntSet mMutualFlags;
	map<int,int> mFlagList;	
};

#endif /* end of include guard: JZFLAGMANAGER_H */
