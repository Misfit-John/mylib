#ifndef __JZ_COMMON_DEFINE_H__
#define __JZ_COMMON_DEFINE_H__

#include <string>
#include <map>
#include <vector>
#include <set>

typedef int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned char uchar;
typedef char int8;
typedef unsigned long long uint64;
typedef long long int64;
typedef short int16;

typedef std::vector<std::string> StringList;
typedef std::vector<int> IntList;
typedef std::set<std::string> StringSet;
typedef std::set<int> IntSet;

//marco define begins here
//
#ifdef _LINUX_
	#define DIR_SEPERATOR "/"
#elif defined(_WIN_)
	#define DIR_SEPERATOR "\"	
#endif

#endif //__JZ_COMMON_DEFINE_H__
