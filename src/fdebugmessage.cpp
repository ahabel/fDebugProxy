#include <iostream>
#include <getopt.h>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

#include <sstream>

#include "global.h"
#include "syslog/fsyslog.h"
#include "fdebugmessage.h"


fDebugMessage::fDebugMessage(char* str) {
   this->log = fSysLog::getInstance();
	this->parse(str);
}

bool fDebugMessage::parse(char* str) {
   this->origin = str;
   
   istringstream input(str);
   if (!Object::parse(input, this->object)) {
      perror("parsing json failed");
      exit(1);
   }
   
   string type = this->object.get<string>("type");
   this->log->debug("Received new message of type '%s'", type.c_str());
   
   this->type = 2;
   if (type == "REGISTER") {
      this->type = FDEBUG_REGISTER;
   } else if (type == "SETCLIENT") {
      this->type = FDEBUG_SETCLIENT;
   } else if (type == "CONTROL") {
      this->type = FDEBUG_CONTROL;
   }
   
   return true;
}




