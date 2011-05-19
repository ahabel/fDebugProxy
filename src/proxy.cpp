#include <iostream>
#include <getopt.h>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "syslog/fsyslog.h"
#include "fdebugproxy.h"
#include "json/cJSON.h"

#include "db/database.h"

using namespace std;

int main(int argc, char **argv) {
   /*fprintf(stdout, "starting...\n");

   ClientDB *db = new ClientDB();
   db->open("/tmp/x_fdebug.db");

   //db->addClient("foo", "x", "1002");

   sClient client = db->getClient("lol-foo");

   return 0;*/
   fDebugProxy *proxy = new fDebugProxy();
   proxy->run();
   
   return 0;
}

