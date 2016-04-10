#ifdef _LINUX_
#include <signal.h>
#include <execinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include "JZCommonDefine.h"

static FILE *outputFile = NULL;

inline void printStackTrace(int signum, FILE *out = stdout, unsigned int max_frames = 63 )
{
   fprintf(out, "stack trace:\n");
 
   // storage array for stack trace address data
   void* addrlist[max_frames+1];
 
   // retrieve current stack addresses
   uint32 addrlen = backtrace( addrlist, sizeof( addrlist ) / sizeof( void* ));
 
   if ( addrlen == 0 ) 
   {
      fprintf( out, "  \n" );
      return;
   }
 
   // create readable strings to each frame.
   char** symbollist = backtrace_symbols( addrlist, addrlen );
 
   // print the stack trace.
   for ( uint32 i = 3; i < addrlen; i++ )
      fprintf( out, "%s\n", symbollist[i]);
 
   free(symbollist);
}

void abortHandler( int signum )
{
  if (NULL == outputFile)
  {
    printStackTrace(signum,outputFile);
  }
  else
  {
    printStackTrace(signum);
    
  }
  exit( signum );
}

void setDumpFileName(const char* fileName)
{
  if (NULL == fileName)
  {
    return;
  }
  outputFile = fopen(fileName, "a+");
}

void JZInitStackTrace()
{
  //maybe we will need to add more signal here, but just ignore it now.
  signal( SIGABRT, abortHandler );
  signal( SIGSEGV, abortHandler );
  signal( SIGILL,  abortHandler );
  signal( SIGFPE,  abortHandler );
}

#endif // _LINUX_
