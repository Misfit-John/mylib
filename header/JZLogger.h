/*********************************************************
	This logger use printf as the root printer.
    There might be some problem if the input is too long.

	You may recevie segment fault 11 if the input is too long
 	and it will be ok if you seperate the input into multiple
	line
 ********************************************************/


#ifndef __JZLOGGER_H__
#define __JZLOGGER_H__

//use JZ as prefix
#include <stdio.h>
#include <time.h>

#define JZ_LOG_OFF	 (0x0)
#define JZ_LOG_DEBUG (0x1)
#define JZ_LOG_ERROR (0x2)
#define JZ_LOG_TRACE (0x4)
#define JZ_LOG_TEST (0x8)

#define JZ_LOG_ALL (JZ_LOG_ERROR|JZ_LOG_DEBUG|JZ_LOG_TRACE|JZ_LOG_TEST)
/*********************************************************
red='\e[0;31m'
RED='\e[1;31m'
blue='\e[0;34m'
BLUE='\e[1;34m'
cyan='\e[0;36m'
CYAN='\e[1;36m'
green='\e[0;32m'
GREEN='\e[1;32m'
yellow='\e[0;33m'
YELLOW='\e[1;33m'
NC='\e[0m' 
 ********************************************************/



void JZLoggerInit();
void JZLoggerFin();

void JZSetLoggerLevel(int level);
void JZSetLoggerOutPutStatue(int toConsole, int toFile);
void JZSetLogFileName(const char* filename);

int JZGetDebugLevel();

//hidden function
void JZWriteLog(const char* log);

#ifdef DEBUG
#define JZWRITE_TEST(format, args...) {\
		if(JZGetDebugLevel() & JZ_LOG_TEST)\
		{\
			char logWord[900];\
			char log[1024];\
			time_t timep;\
			struct tm *p;\
			time(&timep);\
			p = gmtime(&timep);\
			sprintf(logWord,format,##args);\
			sprintf(log,"[TEST][%d-%d-%d,%d:%d:%d][%s:%d][%s]:\n%s\n",p->tm_year + 1900 ,p->tm_mon + 1,p->tm_mday,(p->tm_hour + 8 ) % 24,p->tm_min,p->tm_sec,__FILE__,__LINE__,__func__,logWord);\
			JZWriteLog(log);		\
		}		\
}

#define JZWRITE_DEBUG(format, args...) {\
		if(JZGetDebugLevel() & JZ_LOG_DEBUG)\
		{\
			char logWord[900];\
			char log[1024];\
			time_t timep;\
			struct tm *p;\
			time(&timep);\
			p = gmtime(&timep);\
			sprintf(logWord,format,##args);\
			sprintf(log,"\x1B[1;31m[DEBUG][%d-%d-%d,%d:%d:%d][%s:%d][%s]\x1b[0m:\n%s\n",p->tm_year + 1900 ,p->tm_mon + 1,p->tm_mday,(p->tm_hour + 8 ) % 24,p->tm_min,p->tm_sec,__FILE__,__LINE__,__func__,logWord);\
			JZWriteLog(log);		\
		}		\
}
#define JZFUNC_BEGIN_LOG() {\
		if(JZGetDebugLevel() & JZ_LOG_TRACE)\
		{\
			char log[1024];\
			time_t timep;\
			struct tm *p;\
			time(&timep);\
			p = gmtime(&timep);\
			sprintf(log,"\x1B[1;31m[TRACE][%d-%d-%d,%d:%d:%d][%s:%d][%s]\x1B[0m:BEGIN\n",p->tm_year + 1900 ,p->tm_mon + 1,p->tm_mday,(p->tm_hour + 8 ) % 24,p->tm_min,p->tm_sec,__FILE__,__LINE__,__func__);\
			JZWriteLog(log);		\
		}		\
}
#define JZFUNC_END_LOG() {\
		if(JZGetDebugLevel() & JZ_LOG_TRACE)\
		{\
			char log[1024];\
			time_t timep;\
			struct tm *p;\
			time(&timep);\
			p = gmtime(&timep);\
			sprintf(log,"[TRACE][%d-%d-%d,%d:%d:%d][%s:%d][%s]:END\n",p->tm_year + 1900 ,p->tm_mon + 1,p->tm_mday,(p->tm_hour + 8 ) % 24,p->tm_min,p->tm_sec,__FILE__,__LINE__,__func__);\
			JZWriteLog(log);		\
		}		\
}

#else	//DEBUG

#define JZWRITE_DEBUG(format, args...) {do{}while(0);}
#define JZFUNC_BEGIN_LOG() {do{}while(0);}
#define JZFUNC_END_LOG() {do{}while(0);}
#define JZWRITE_TEST(format, args...) {do{}while(0);}

#endif //DEBUG

#define JZWRITE_ERROR(format, args...) {\
		if(JZGetDebugLevel() & JZ_LOG_ERROR)\
		{\
			char logWord[900];\
			char log[1024];\
			time_t timep;\
			struct tm *p;\
			time(&timep);\
			p = gmtime(&timep);\
			sprintf(logWord,format,##args);\
			sprintf(logWord,format,##args);\
			sprintf(log,"[ERROR][%d-%d-%d,%d:%d:%d][%s:%d][%s]:\n%s\n",p->tm_year + 1900 ,p->tm_mon + 1,p->tm_mday,(p->tm_hour + 8) %24,p->tm_min,p->tm_sec,__FILE__,__LINE__,__func__,logWord);\
			JZWriteLog(log);		\
		}		\
}


#endif //__logger_h__
