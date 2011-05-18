#ifndef PROXY_DATABASE_H_
#define PROXY_DATABASE_H_

#include <string>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>


class Database {
public:
   Database();
   bool open(std::string db);

};

#endif /*PROXY_DATABASE_H_*/
