#include <iostream>
#include <getopt.h>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "json/cJSON.h"
#include "syslog/fsyslog.h"
#include "fdebugproxy.h"
#include "fdebugsocket.h"
#include "db/database.h"

using namespace std;

fDebugProxy::fDebugProxy() {
   // init logging
   this->log = fSysLog::getInstance();
   this->log->init((char*)FDEBUG_LOGFILE);
   this->log->info("Processing new connection from %s (%s)", getenv("TCPREMOTEIP"), getenv("TCPREMOTEHOST"));

   // init sqlite db
   this->db = new ClientDB();
   this->db->open("/tmp/x_fdebug.db");

   this->socket = NULL;
}

void fDebugProxy::run() {
   char str[BUF_SIZE];
   
   // get socket input
   while(fgets(str, BUF_SIZE, stdin)) {
      this->log->debug("RECV: %s\n", str);

      /* remove newline, if present */
      if( str[strlen(str)-1] == '\n') {
         str[strlen(str)-1] = '\0';
      }
      
      fDebugMessage message = this->parse(str);
      
      switch(message.type) {
         case FDEBUG_REGISTER: {
            this->registerClient(message);
            this->sendServer("OK");
            this->log->debug("RETURN");
            return;
         }
         
         case FDEBUG_SETCLIENT: {
            this->setClient(message);
            this->sendServer("OK");
            this->log->debug("SETCLIENT");
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
      
      this->log->debug("SERVER: OK");
      this->sendServer("OK");
   }
}

fDebugMessage fDebugProxy::parse(char *str) {
   fDebugMessage message;
   message.origin = str;
   
   
   // Check if received message is a valid JSON structure
   cJSON *root = cJSON_Parse(str);
   if (root->type != 6) {
      // message is not an json object / 6 = CJSON_OBJECT
      //log->sendServer("ERROR: parsing json failed");
      this->log->debug("PARSE ERROR: %i", root->type);
      return message;
   }
   
   
   string type = cJSON_GetObjectItem(root, "type")->valuestring;
   message.type = 2;
   this->log->debug("message type: %s", type.c_str());
   
   if (type == "REGISTER") {
      message.type = FDEBUG_REGISTER;
   } else if (type == "SETCLIENT") {
      message.type = FDEBUG_SETCLIENT;
   } else if (type == "CONTROL") {
      message.type = FDEBUG_CONTROL;
   }
   
   cJSON *payload = cJSON_GetObjectItem(root, "payload");
   message.payload = payload;
   return message;
}

bool fDebugProxy::sendServer(const char* str) {
   fprintf(stdout, "%s\r\n", str);
   cout.flush();
   return true;
}

void fDebugProxy::handleControl(fDebugMessage message) {
   // {"type":"CONTROL","payload":{"action":"HELO","url":"\/de\/site\/index.xml","server":"bluepoints.mobile.dev"}}
   // {"type":"CONTROL","payload":{"action":"QUIT"}}

   string action = cJSON_GetObjectItem(message.payload, "action")->valuestring;
   this->log->debug("CONTROL RECV: %s\n", action.c_str());

   if (action == "HELO") {
      this->log->debug("HELO from %s", cJSON_GetObjectItem(message.payload, "server")->valuestring);
   }

   if (action == "QUIT") {
      this->forwardData(message);
      this->socket->close();
      this->sendServer("OK");
   }
}

void fDebugProxy::registerClient(fDebugMessage message) {
   //{"type":"REGISTER","payload":{"UUID":"{4abc3ebc-1bab-455e-b8b4-a5771eb60569}","PORT":5005}}
   string uuid = cJSON_GetObjectItem(message.payload, "UUID")->valuestring;
   int port = cJSON_GetObjectItem(message.payload, "PORT")->valueint;

   this->db->addClient(uuid, getenv("TCPREMOTEIP"), port);
   this->log->info("Registration with client completed (%s : %d)", uuid.c_str(), port);
}

void fDebugProxy::setClient(fDebugMessage message) {
   //{"type":"SETCLIENT","payload":{"UUID":"{4abc3ebc-1bab-455e-b8b4-a5771eb60569}"}}
   string uuid = cJSON_GetObjectItem(message.payload, "UUID")->valuestring;
   sClient client = this->db->getClient(uuid);

   this->socket = new fDebugSocket();
   this->socket->connectClient(client.remote, client.port);
   this->log->info("Connection to client established (%s)\n", client.remote);
}

bool fDebugProxy::forwardData(fDebugMessage message) {
   this->socket->sendClient(message.origin);
   this->socket->receive();
   return true;
}







