/**
 * @author Andreas Habel
 *
 * @class fDebugProxy
 * @brief Main Class for handling fdebug requests
 *
 * @package fDebugProxy
 */

#ifndef FDEBUGPROXY_H_
#define FDEBUGPROXY_H_

#include "fdebugsocket.h"
#include "fdebugmessage.h"
#include "db/database.h"

using namespace jsonxx;


class fDebugProxy {
public:
   fDebugProxy();
   void run();
   void registerClient(fDebugMessage *message);
   void setClient(fDebugMessage *message);
   
private:
   fSysLog        *log;
   fDebugSocket   *socket;
   ClientDB       *db;
   
   void           handleControl(fDebugMessage *message);
   bool           sendServer(const char* str);
   bool           forwardData(fDebugMessage *message);
};

#endif /*FDEBUGPROXY_H_*/
