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

using namespace std;

fDebugProxy::fDebugProxy() {
   // init logging
   this->log = fSysLog::getInstance();
   this->log->init((char*)FDEBUG_LOGFILE);
   this->log->info("Processing new connection from %s (%s)", getenv("TCPREMOTEIP"), getenv("TCPREMOTEHOST"));
   this->socket = NULL;
}

void fDebugProxy::run() {
   char str[BUF_SIZE];
   int i;
   
   // get socket input
   while(fgets(str, BUF_SIZE, stdin)) {
      /* remove newline, if present */
      if( str[strlen(str)-1] == '\n') {
         str[strlen(str)-1] = '\0';
      }
      
      //char buf[strlen(str)+100];
      //sprintf(buf, "<<<< in <<<< -- size:%i -- [%s]", strlen(str), str);
      //this->log->info(buf);
      
      fDebugMessage message = this->parse(str);
      
      // REGISTER
      if (strcmp(message.type, "REGISTER") == 0) {
         this->registerClient();
         this->write("OK");
         return;
      }
      
      // SETCLIENT
      if (strcmp(message.type, "SETCLIENT") == 0) {
         this->setClient(message);
         this->write("OK");
         continue;
      }
      
      // CONTROL
      if (strcmp(message.type, "CONTROL") == 0) {
         this->handleControl(message);
         this->write("OK");
      }
      
      if (this->socket == NULL) {
         this->log->info("No proxy request or out of bounds message - dropping connection");
         exit(1);
      }
      
      if (!this->forwardData(message)) {
         // TODO: should be exit with code 1 here?
         exit(1);
      }
      
      this->write("OK");
   }
}

fDebugMessage fDebugProxy::parse(char *str) {
   fDebugMessage message;
   
   cJSON *root = cJSON_Parse(str);
   if (root->type != 6) {
      // message is not an json object / 6 = CJSON_OBJECT
      //log->write("ERROR: parsing json failed");
      return message;
   }
   
   char *type = cJSON_GetObjectItem(root, "type")->valuestring;
   cJSON *payload = cJSON_GetObjectItem(root, "payload");
   
   
   // client register:
   //    {"type":"REGISTER","payload":{"UUID":"{4abc3ebc-1bab-455e-b8b4-a5771eb60569}","PORT":5005}}
   
   // server -> proxy connect
   //     {"type":"SETCLIENT","payload":{"UUID":"{4abc3ebc-1bab-455e-b8b4-a5771eb60569}"}}
   
   message.origin  = str;
   message.type    = type;
   message.payload = payload;
   
   return message;
}

bool fDebugProxy::write(const char* str) {
   fprintf(stdout, "%s\r\n", str);
   cout.flush();
   
   //char buf[80];
   //sprintf(buf, ">> [%s]\n", str);
   //this->log->info(buf);
   return true;
}

void fDebugProxy::handleControl(fDebugMessage message) {
   // {"type":"CONTROL","payload":{"action":"HELO","url":"\/de\/site\/index.xml","server":"bluepoints.mobile.dev"}}
   // {"type":"CONTROL","payload":{"action":"QUIT"}}

   string action = cJSON_GetObjectItem(message.payload, "action")->valuestring;
   if (action == "HELO") {
      this->log->info("HELO from %s", cJSON_GetObjectItem(message.payload, "server")->valuestring);
   }

   if (action == "QUIT") {
      this->forwardData(message);
      this->socket->close();
      this->write("OK");
   }
}

void fDebugProxy::registerClient() {
   this->log->info("Registration with client completed");
}

void fDebugProxy::setClient(fDebugMessage message) {
   this->socket = new fDebugSocket();
   this->socket->connectClient("127.0.0.1", 5005);
}

bool fDebugProxy::forwardData(fDebugMessage message) {
   this->socket->sendClient(message.origin);
   this->socket->receive();
   return true;
}







