#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>


#include "global.h"
#include "fdebugsocket.h"
#include "syslog/fsyslog.h"


fDebugSocket::fDebugSocket() {
   this->log = fSysLog::getInstance();

   if (!this->initSocket()) {
      perror("Initiating Socket to client");
      exit(1);
   }
}

bool fDebugSocket::initSocket() {
   this->sock = socket(AF_INET, SOCK_STREAM, 0);
   if (this->sock == -1) {
      perror("Creating socket");
      return false;
   }
   
   // TIME WAIT fix
   int on = 1;
   if (setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof(on)) == -1) {
      perror("Cannot set socket options");
      return false;
   }
   
   if (setsockopt(this->sock, IPPROTO_TCP, TCP_NODELAY, (const char*) &on, sizeof(on)) == -1) {
      perror("Cannot set NODELAY");
      return false;
   }
   
   return true;
}

bool fDebugSocket::connectClient(const char *addr, int port) {
   this->addr = addr;
   this->port = port;
   
   this->log->debug("Establishing connection to %s:%d", (char*)this->addr, this->port);

   sockaddr_in clientaddr;
   clientaddr.sin_family      = AF_INET;
   clientaddr.sin_addr.s_addr = inet_addr((const char *)this->addr);
   clientaddr.sin_port        = htons(this->port);
   
   if (connect(this->sock,(struct sockaddr *) &clientaddr, sizeof(struct sockaddr_in)) < 0) {
      perror("Connecting stream socket");
      exit(1);
   }
   
   return true;
}

bool fDebugSocket::sendClient(char* data) {
   data[strlen(data)] = '\n';
   
   int bytes = send(this->sock, data, strlen(data), 0);
   if (bytes == -1) {
      perror("Sending to socket failed");
      exit(1);
   }
   
   this->log->debug(">> Sending %d bytes data to client\n", bytes);
   return true;
}

char fDebugSocket::receive() {
   char buf[BUF_SIZE];
   int bytes  = recv(this->sock, buf, sizeof(buf) - 1, 0);
   if (bytes == -1) {
      perror("recv failed");
      return false;
   }
   
   if (bytes == 0) {
      return false;
   }
   
   
   char buffer[10000];
   
   buf[bytes] = '\0';
   char *x;
   x = strtok(buf, "\r\n");
   sprintf(buffer, x);

   this->log->debug("[client] Received from client: bytes rx: %d (buffer: %i): %s", bytes, strlen(buffer), buf);
   return *buf;
}

void fDebugSocket::close() {
   shutdown(this->sock, SHUT_RDWR);
}










