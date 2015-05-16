#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_

#ifdef _MSC_VER
#define cdf_snprintf _snprintf
#else
#define cdf_snprintf snprintf
#endif

#include "JZCommonDefine.h"
using namespace std;

namespace StringUtil
{
extern int16  str2int16(string str);

extern int32  str2int32(string str);

extern int64  str2int64(string str);

extern uint64 str2uint64(string str);

extern string tostr(int16 v);

extern string tostr(int32 v);

extern string tostr(int64 v);

extern string tostr(uint16 v);

extern string tostr(uint32 v);

extern string tostr(uint64 v);

extern string tostr(float v);

extern string tostr(double v);

extern string str2hex(const char* str , int len);

extern string filterString(const char* str ,const char* filter);

extern void   trimString(string & str, string val);

extern bool   splitString(const string& str, const string& delim, vector<string>& result);

extern bool   splitString(const string& str, const string& delim, set<string>& result);

extern string joinString(const std::vector<std::string>& values, const std::string& delimiter);

extern void   replaceString(string& str, string srcStr, string destStr);

extern string toUpperString(string s);

extern string toLowerString(string s);

extern string removeWhitespace(const std::string& s);

extern string encodeXmlText(const char * pstr);

extern string encodeUrl(string s);

extern bool   isAlpha(char c);

extern bool   isDigit(char c);

extern void parseIPAddr(string ipAddr, string & ip, uint32 & port);
}
#endif  //_STRING_UTIL_H_

