#ifndef FDEBUGPROXY_H_
#define FDEBUGPROXY_H_

#include "json/cJSON.h"
#include "fdebugsocket.h"
#include "db/database.h"


//
// fDebug Message
//
struct fDebugMessage {
   char  *origin;
   int   type;
   cJSON *payload;
};



class fDebugProxy {
public:
   fDebugProxy();
   void run();
   void registerClient(fDebugMessage message);
   void setClient(fDebugMessage message);
   
private:
   fSysLog        *log;
   fDebugSocket   *socket;
   ClientDB       *db;
   
   void           handleControl(fDebugMessage message);
   bool           sendServer(const char* str);
   bool           forwardData(fDebugMessage message);
   fDebugMessage  parse(char *str);
};

#endif /*FDEBUGPROXY_H_*/
