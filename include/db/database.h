/**
 * @author     Andreas Habel
 * @package    fDebugProxy
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

#include "syslog/fsyslog.h"

using namespace std;

/**
 * @struct  sClient
 * @brief   Client property objects
 */
struct sClient {
   /**
    * @property uuid
    * Client UUID
    */
   string uuid;

   /**
    * @property remote
    * Client Remote IP address
    */
   const char* remote;

   /**
    * @property port
    * Client port
    */
   int port;
};


/**
 * @class   ClientDB
 * @brief   Database Library
 */
class ClientDB {
public:
   ClientDB();

   /**
    * Opens the connection to the sqlite database
    * If client.db file does not exist, it will be created
    *
    * @param dbFile Path to SQLite database
    */
   void     open(string dbFile);

   /**
    * Closes a opened database
    */
   void     close();

   /**
    * Add a new fDebug Client to the database
    *
    * @param uuid    Client UUID
    * @param remote  Remote IP address
    * @param port    Remote Port
    * @return true if the client was added to the DB or false in failure
    */
   bool     addClient(string uuid, string remote, int port);

   /**
    * Returns the client settings (remote address and port) for a given UUID
    *
    * @param uuid    Client UUID
    * @return new struct sClient with client settings
    * @see sClient
    */
   sClient  getClient(string uuid);

private:

   /**
    * @property db
    * Holds the sqlite3 database object
    */
   sqlite3* db;

   /**
    * @property log
    * Reference to the fSysLog instance
    */
   fSysLog* log;

   /**
    * Created the internal tables and structures used for fdebug proxy
    */
   void  createTables();
};

#endif /*PROXY_DATABASE_H_*/
