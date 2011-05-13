#ifndef FCONFIGSTORAGE_H_
#define FCONFIGSTORAGE_H_

#include <string>
using namespace std;

struct fConfigItem {
   string key;
   string value;
   struct fConfigItem *next;
};

class fConfigStorage {
public:
   fConfigStorage();
   
   bool     add(string name, string value);
   string   getValue(string key);
   bool     printList();
   
protected:
   fConfigItem list;
   
   bool     exists(string key);
};

#endif /*FCONFIGSTORAGE_H_*/
