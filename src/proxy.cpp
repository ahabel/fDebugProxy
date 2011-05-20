#include "fdebugproxy.h"

int main(int argc, char **argv) {
   fDebugProxy *proxy = new fDebugProxy();
   proxy->run();
   return 0;
}
