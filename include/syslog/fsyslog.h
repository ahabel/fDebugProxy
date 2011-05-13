#ifndef FSYSLOG_H_
#define FSYSLOG_H_

class fSysLog {
public:
	static fSysLog* getInstance();
	void   init(char *logfile);
	void   close();
	void   info(const char *message, ...);
	
private:
   fSysLog() {}
   fSysLog(fSysLog const&){};            // copy constructor is private
   fSysLog& operator=(fSysLog const&){}; // assignment operator is private
   static fSysLog* m_pInstance;
   
   
   char *logfile;
   FILE *log;
};

#endif /*FSYSLOG_H_*/
