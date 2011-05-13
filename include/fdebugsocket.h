#ifndef FDEBUGSOCKET_H_
#define FDEBUGSOCKET_H_

#include <netinet/in.h>
#include "syslog/fsyslog.h"

class fDebugSocket {
public:
	fDebugSocket();
	bool  connectClient(const char *addr, int port);
	bool  sendClient(char* data);
	char  receive();
	void  close();
private:
	fSysLog    *log;
   const char *addr;
	int         port;
	int         sock;
	sockaddr_in srv_addr;


	bool initSocket();
};

#endif /*FDEBUGSOCKET_H_*/
