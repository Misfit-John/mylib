#ifndef __JZLOGGER_H__
#define __JZLOGGER_H__

//use JZ as prefix
#include <stdio.h>
#include <time.h>

#define JZ_LOG_OFF	 0x0
#define JZ_LOG_DEBUG 0x1
#define JZ_LOG_ERROR 0x2
#define JZ_LOG_ALL (JZ_LOG_ERROR|JZ_LOG_DEBUG)


void JZLoggerInit();
void JZLoggerFin();

void JZSetLoggerLevel(int level);
void JZSetLoggerOutPutStatue(int toConsole, int toFile);
void JZSetLogFileName(const char* filename);

int JZGetDebugLevel();

//hidden function
void JZWriteLog(const char* log);

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
			sprintf(log,"[DEBUG][%d-%d-%d,%d:%d:%d][%s:%d][%s]:%s\n",p->tm_year + 1900 ,p->tm_mon + 1,p->tm_mday,(p->tm_hour + 8 ) % 24,p->tm_min,p->tm_sec,__FILE__,__LINE__,__func__,logWord);\
			JZWriteLog(log);		\
		}		\
}

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
			sprintf(log,"[ERROR][%d-%d-%d,%d:%d:%d][%s:%d][%s]:%s\n",p->tm_year + 1900 ,p->tm_mon + 1,p->tm_mday,(p->tm_hour + 8) %24,p->tm_min,p->tm_sec,__FILE__,__LINE__,__func__,logWord);\
			JZWriteLog(log);		\
		}		\
}
#endif //__logger_h__
