/**
 *
 * SQLite Database Library
 *
 *
 * @author Andreas Habel
 * @package fDebugProxy
 * @class Database
 *
 *
 * Usage:
 *
 * Database *db = new Database();
 * db->open("/tmp/test.db");
 *
 */

#ifndef PROXY_DATABASE_H_
#define PROXY_DATABASE_H_

#include <string>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

class ClientDB {
public:
   ClientDB();
   void  open(string dbFile);
   bool  addClient(string uuid, string remote, string port);

private:
   sqlite3* db;

   void  createTables();
};

#endif /*PROXY_DATABASE_H_*/
