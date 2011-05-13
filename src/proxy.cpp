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
   fDebugProxy *proxy = new fDebugProxy();
   proxy->run();
   
   return 0;
}

