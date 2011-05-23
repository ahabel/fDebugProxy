#include "string.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <ctime>
#include <sys/stat.h>
#include <stdarg.h>

#include "global.h"
#include "syslog/fsyslog.h"

fSysLog* fSysLog::instance = NULL;
fSysLog* fSysLog::getInstance() {
   if (!instance) {
      instance = new fSysLog;
   }
   return instance;
}

void fSysLog::init(char *logfile) {
   this->logfile = logfile;
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
   this->writeLog("info", out);
}

void fSysLog::error(const char* message, ...) {
   char *out;
   int Ret;
   va_list marker;
   va_start(marker, message);
   Ret = vasprintf(&out, message, marker);
   va_end(marker);
   this->writeLog("error", out);
}

void fSysLog::debug(const char* message, ...) {
   if (!DEBUG_MODE) {
      return;
   }

   char *out;
   int Ret;
   va_list marker;
   va_start(marker, message);
   Ret = vasprintf(&out, message, marker);
   va_end(marker);
   this->writeLog("debug", out);
}

void fSysLog::writeLog(string type, char* message) {
   time_t rawtime;
   struct tm *timeinfo;
   char buffer[80];
   
   time ( &rawtime );
   timeinfo = localtime ( &rawtime );
   
   strftime(buffer,80, "%b %d %H:%M:%S",timeinfo);
   
   char messagebuffer[strlen(message) + 50];
   sprintf(messagebuffer, "%s %s %s: %s\n", buffer, type.c_str(), getenv("TCPREMOTEIP"), message);
   fputs(messagebuffer, this->log);
   fflush(this->log);
}









