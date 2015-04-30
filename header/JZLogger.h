#ifndef __logger_h__
#define __logger_h__

//use JZ as prefix

#define JZ_LOG_OFF	 0x0
#define JZ_LOG_DEBUG 0x1
#define JZ_LOG_ERROR 0x2
#define JZ_LOG_ALL (JZ_LOG_ERROR|JZ_LOG_DEBUG)

void JZLoggerInit();
void JZLoggerFin();

void JZSetLoggerLevel(int level);
void JZSetLoggerOutPutStatue(int toConsole, int toFile);
void JZsetLogFileName(const char* filename);

int JZGetDebugLevel();

//hidden function
void JZWriteLog(const char* log);

#define JZWRITE_DEBUG(format, args...) {\
		if(JZGetDebugLevel() & JZ_LOG_DEBUG)\
		{\
			char logWord[900];\
			char log[1024];\
			sprintf(logWord,format,##args);\
			sprintf(log,"[DEBUG][%s--%s][%s:%d][%s]:%s",__DATE__,__TIME__,__FILE__,__LINE__,__func__,logWord);\
			JZWriteLog(log)		\
		}		\
}

#define JZWRITE_ERROR(format, args...) {\
		if(JZGetDebugLevel() & JZ_LOG_ERROR)\
		{\
			char logWord[900];\
			char log[1024];\
			sprintf(logWord,format,##args);\
			sprintf(log,"[ERROR][%s--%s][%s:%d][%s]:%s",__DATE__,__TIME__,__FILE__,__LINE__,__func__,logWord);\
			JZWriteLog(log)		\
		}		\
}
#endif //__logger_h__
