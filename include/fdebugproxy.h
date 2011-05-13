#ifndef FDEBUGPROXY_H_
#define FDEBUGPROXY_H_

#include "json/cJSON.h"
#include "fdebugsocket.h"

struct fDebugMessage {
   char  *origin;
   char  *type;
   cJSON *payload;
};

class fDebugProxy {
public:
   fDebugProxy();
   void run();
   void registerClient();
   void setClient(fDebugMessage message);
   
private:
   fSysLog        *log;
   fDebugSocket   *socket;
   
   void           handleControl(fDebugMessage message);
   bool           write(const char* str);
   bool           forwardData(fDebugMessage message);
   fDebugMessage  parse(char *str);
};

#endif /*FDEBUGPROXY_H_*/
