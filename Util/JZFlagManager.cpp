#include "JZFlagManager.h"

JZFlagManager::JZFlagManager()
{
	//
}

JZFlagManager::~JZFlagManager()
{
	//
}

bool JZFlagManager::setFlag(int flag, int state)
{
	if (false == canSetFlagToState(flag, state))
	{
		return false;
	}

	if (0 == state)
	{
		return resetFlag(flag);
	}
	
	if (true == isMutually(flag))
	{
		return false;
	}
	mFlagList[flag] = state;
}

bool JZFlagManager::resetFlag(int flag)
{
	if (false == canSetFlagToState(flag, 0))
	{
		return false;
	}

	mFlagList[flag] = 0;
}

bool JZFlagManager::canSetFlagToState(int flag, int state)
{
	return true;
}

void JZFlagManager::setMutuallyFlag(IntList flags)
{
	auto it = flags.begin();
	for(; it != flags.end(); it++)
	{
		mMutualFlags.insert(*it);	
	}
}

bool JZFlagManager::isMutually(int flag	)
{
	auto it = mMutualFlags.begin();
	for(; it != mMutualFlags.end(); it++)
	{
		auto flagIt = mFlagList.find(*it);
		if(mFlagList.end() == flagIt)
		{
			if (*it == flag)
			{
				//not init yet
				return false;
			}
			else
			{	
				//not init,but not to check flag
				continue;
			}
		}
		if(flagIt->second != 0)
		{
			//one of the flag in mutual list is not reset,mutually
			return true;
		}
	}
	//all check is clear, no mutual
	return false;

}



