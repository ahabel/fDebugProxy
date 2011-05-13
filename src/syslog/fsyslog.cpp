#include "string.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <ctime>
#include <sys/stat.h>
#include <stdarg.h>

#include "syslog/fsyslog.h"

fSysLog* fSysLog::m_pInstance = NULL;

fSysLog* fSysLog::getInstance() {
   if (!m_pInstance) {  // Only allow one instance of class to be generated.
      m_pInstance = new fSysLog;
   }
   return m_pInstance;
}

void fSysLog::init(char *logfile) {
   this->logfile = logfile;
   //printf("Using logfile: %s\n", this->logfile);
   
   this->log = fopen(this->logfile, "at");
   if (!this->log) {
      log = fopen(this->logfile, "wt");
   }
   
   if (!this->log) {
      perror("Cannot open logfile for writing");
      exit(0);
   }
}

void fSysLog::close() {
   fclose(this->log);
}

void fSysLog::info(const char* message, ...) {
   char *out;
   int Ret;
   va_list marker;
   va_start(marker, message);
   Ret = vasprintf(&out, message, marker);
   va_end(marker);

   time_t rawtime;
   struct tm *timeinfo;
   char buffer[80];
   
   time ( &rawtime );
   timeinfo = localtime ( &rawtime );
   
   strftime(buffer,80, "%b %d %H:%M:%S",timeinfo);
   
   char messagebuffer[strlen(out) + 50];
   sprintf(messagebuffer, "%s info %s: %s\n", buffer, getenv("TCPREMOTEIP"), out);
   fputs(messagebuffer, this->log);
   fflush(this->log);
}









