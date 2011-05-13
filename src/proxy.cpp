#include <iostream>
#include <getopt.h>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "syslog/fsyslog.h"
#include "fconfig/fconfig.h"
#include "fdebugproxy.h"
#include "json/cJSON.h"

using namespace std;

int main(int argc, char **argv) {

   fConfig *config = fConfig::getInstance();
   config->loadFile("/etc/fdebug-proxy/proxy.conf");

   printf("Bye\n");
   return 0;
   /*fDebugProxy *proxy = new fDebugProxy();
   proxy->run();
   
   return 0;*/
   // init fdebug config
   /*fDebugConfig *config = fDebugConfig::getInstance();
   config->init(argc, argv);
   
   // init logging
   fSysLog *log = fSysLog::getInstance();
   log->init((char*)FDEBUG_LOGFILE);
   
   char buf[80];
   sprintf(buf, "Processing new connection from %s (%s)", getenv("TCPREMOTEIP"), getenv("TCPREMOTEHOST"));
   log->info(buf);
   
   
   char str[80];
   int i;
   
   while(fgets(str, 1024, stdin)) {
      // remove newline, if present
      i = strlen(str)-1;
      if( str[ i ] == '\n') {
         str[i] = '\0';
      }
      char buf[255];
      sprintf(buf, "in: %s", str);
      log->info(buf);
      
      
      cJSON *root = cJSON_Parse(str);
      if (root->type != 6) {
         // message is not an json object / 6 = CJSON_OBJECT
         //log->write("ERROR: parsing json failed");
         continue;
      }
      
      char *type = cJSON_GetObjectItem(root, "type")->valuestring;
      cJSON *payload = cJSON_GetObjectItem(root, "payload");
      
      
      // client register:
      //    {"type":"REGISTER","payload":{"UUID":"{4abc3ebc-1bab-455e-b8b4-a5771eb60569}","PORT":5005}}
      
      // server -> proxy connect
      //     {"type":"SETCLIENT","payload":{"UUID":"{4abc3ebc-1bab-455e-b8b4-a5771eb60569}"}}
      
      
      // fdebug client register
      if (strcmp(type, "REGISTER") == 0) {
         registerClient();
         send("OK");
         exit(0);
      } else if (strcmp(type, "SETCLIENT") == 0) {
         //TODO: set_client
      } else {
         // fdebug messages
         log->info("forwarding message...");
      }
      
      send("OK");
   }
   
   return 0;*/
}





