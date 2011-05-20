#include <iostream>
#include <getopt.h>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

#include <sstream>

#include "global.h"

#include "syslog/fsyslog.h"
#include "fdebugproxy.h"
#include "fdebugsocket.h"
#include "db/database.h"


using namespace std;
using namespace jsonxx;

fDebugProxy::fDebugProxy() {
   // init logging
   this->log = fSysLog::getInstance();
   this->log->init((char*)FDEBUG_LOGFILE);
   this->log->info("Processing new connection from %s (%s)", getenv("TCPREMOTEIP"), getenv("TCPREMOTEHOST"));

   // init sqlite db
   this->db = new ClientDB();
   this->db->open(FDEBUG_CLIENTDB);

   this->socket = NULL;
}

void fDebugProxy::run() {
   char str[BUF_SIZE];
   
   // get socket input
   while(fgets(str, BUF_SIZE, stdin)) {
      /* remove newline, if present */
      if( str[strlen(str)-1] == '\n') {
         str[strlen(str)-1] = '\0';
      }
      
      fDebugMessage *message = new fDebugMessage(str);
      
      switch(message->type) {
         case FDEBUG_REGISTER: {
            this->registerClient(message);
            this->sendServer("OK");
            return;
         }
         
         case FDEBUG_SETCLIENT: {
            this->setClient(message);
            this->sendServer("OK");
            continue;
         }
         
         case FDEBUG_CONTROL: {
            this->handleControl(message);
            this->sendServer("OK");
         }
      }
      
      if (this->socket == NULL) {
         this->log->info("No proxy request or out of bounds message - dropping connection");
         exit(1);
      }
      
      if (!this->forwardData(message)) {
         // TODO: exit with code 1 here?
         this->log->debug("ERROR: cannot forward message");
         exit(1);
      }
      
      this->sendServer("OK");
   }
}

bool fDebugProxy::sendServer(const char* str) {
   this->log->debug("Sending 'OK' to origin server");
   fprintf(stdout, "%s\r\n", str);
   cout.flush();
   return true;
}

void fDebugProxy::handleControl(fDebugMessage *message) {
   // {"type":"CONTROL","payload":{"action":"HELO","url":"\/de\/site\/index.xml","server":"bluepoints.mobile.dev"}}
   // {"type":"CONTROL","payload":{"action":"QUIT"}}

   string action = message->object.get<Object>("payload").get<string>("action");
   if (action == "HELO") {
      this->log->debug("HELO from %s", message->object.get<Object>("payload").get<string>("server").c_str());
   }

   if (action == "QUIT") {
      this->forwardData(message);
      this->socket->close();
      this->sendServer("OK");
   }
}

void fDebugProxy::registerClient(fDebugMessage* message) {
   //{"type":"REGISTER","payload":{"UUID":"{4abc3ebc-1bab-455e-b8b4-a5771eb60569}","PORT":5005}}
   string uuid = message->object.get<Object>("payload").get<string>("UUID");
   int port    = (int)message->object.get<Object>("payload").get<double>("PORT");

   this->db->addClient(uuid, getenv("TCPREMOTEIP"), port);
   this->log->info("Registration with client completed (%s : %d)", uuid.c_str(), port);
}

void fDebugProxy::setClient(fDebugMessage* message) {
   //{"type":"SETCLIENT","payload":{"UUID":"{4abc3ebc-1bab-455e-b8b4-a5771eb60569}"}}
   string uuid = message->object.get<Object>("payload").get<string>("UUID");
   sClient client = this->db->getClient(uuid);

   this->socket = new fDebugSocket();
   this->socket->connectClient(client.remote, client.port);
   this->log->info("Connection to client established (%s)", client.remote);
}

bool fDebugProxy::forwardData(fDebugMessage *message) {
   this->socket->sendClient(message->origin);
   this->socket->receive();
   return true;
}







