/**
 * @author Andreas Habel
 * $Id: fdebugmessage.h,v 1.8 2011/01/15 01:17:44 virus-d Exp $
 *
 * @class fDebugMessage
 * @brief Message container object
 *
 * @package fDebug
 */

#ifndef FDEBUGMESSAGE_H_
#define FDEBUGMESSAGE_H_

#include "json/jsonxx.h"

using namespace std;
using namespace jsonxx;

class fDebugMessage {

public:
	fDebugMessage(char* str);
	
	char*   origin;
	int     type;
	Object  object;
	
private:
   bool parse(char* str);
   fSysLog *log;
};

#endif /*FDEBUGMESSAGE_H_*/
