/**
 * @author Andreas Habel
 *
 * @class fSysLog
 * @brief Logging Library
 *
 * @package fDebugProxy
 */

#ifndef FSYSLOG_H_
#define FSYSLOG_H_

#include <string>

using namespace std;

class fSysLog {
public:
	static fSysLog* getInstance();
	void   init(char *logfile);
	void   close();

	void   info(const char *message, ...);
	void   debug(const char *message, ...);
	void   error(const char *message, ...);

private:
	static fSysLog *instance;
   fSysLog() {}

   char *logfile;
   FILE *log;

   void  writeLog(string type, char* message);
};

#endif /*FSYSLOG_H_*/
