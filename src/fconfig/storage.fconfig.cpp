#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>

#include "global.h"
#include "fconfig/storage.fconfig.h"

fConfigStorage::fConfigStorage() {
}

bool fConfigStorage::add(string key, string value) {
   printf("registered key [%s] -> [%s]\n", key.c_str(), value.c_str());
   
   if (this->list.next == NULL)  {
      printf("NULL1\n");
      fConfigItem item;
      item.key   = key;
      item.value = value;
      item.next  = NULL;
      
      this->list = item;
   }
   
   if (this->list.next == NULL)  {
         printf("NULL\n");
   }
   return true;
}

bool fConfigStorage::printList() {
   printf("\nprint:\n");
   fConfigItem item;
   
   item = this->list;
   while(item.next != NULL) {
      fConfigItem item = this->list;
      printf(" --key: %s\n", item.key.c_str());
   }
   
   printf("\n");
   return true;
}





