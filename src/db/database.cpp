#include <string>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

#include "db/database.h"

#include "syslog/fsyslog.h"

using namespace std;

ClientDB::ClientDB() {
   this->log = fSysLog::getInstance();
}

void ClientDB::open(string dbFile) {
   int rc;
   rc = sqlite3_open(dbFile.c_str(), &this->db);
   if (rc) {
      this->log->error("Cannot open database '%s': %s\n", dbFile.c_str(), sqlite3_errmsg(db));
      sqlite3_close(this->db);
      exit(1);
   }

   this->createTables();
}

bool ClientDB::addClient(string uuid, string remote, int port) {
   sqlite3_stmt* stmt;
   const char* tail;
   const char* query;

   query = "replace into clients (uuid,remote,port) values (?,?,?)";
   sqlite3_prepare(this->db, query, strlen(query), &stmt, &tail);
   sqlite3_bind_text(stmt, 1, uuid.c_str(), -1, SQLITE_STATIC);
   sqlite3_bind_text(stmt, 2, remote.c_str(), -1, SQLITE_STATIC);
   sqlite3_bind_int(stmt, 3, port);

   int rc = sqlite3_step(stmt);
   if (rc != SQLITE_DONE) {
      this->log->error("SQLite Query failed (Error %d): %s\n", rc, sqlite3_errmsg(this->db));
      return false;
   }

   return true;
}

sClient ClientDB::getClient(string uuid) {
   sqlite3_stmt* stmt;
   const char* tail;
   const char* query;

   query = "select remote,port from clients where uuid=?";
   sqlite3_prepare(this->db, query, strlen(query), &stmt, &tail);
   sqlite3_bind_text(stmt, 1, uuid.c_str(), -1, SQLITE_STATIC);
   sqlite3_step(stmt);

   sClient client;
   if (sqlite3_data_count(stmt) > 0) {
      client.uuid   = uuid;
      client.remote = (const char*) sqlite3_column_text(stmt, 0);
      client.port   = sqlite3_column_int(stmt, 1);
   }

   return client;
}

void ClientDB::createTables() {
   char* db_err;
   sqlite3_stmt* stmt;
   const char* tail;
   const char* query;
   int rc;

   query = "CREATE TABLE IF NOT EXISTS clients (uuid TEXT, remote TEXT, port TEXT, PRIMARY KEY ( uuid ))";
   rc = sqlite3_prepare(this->db, query, strlen(query), &stmt, &tail);
   if (rc != SQLITE_OK) {
      this->log->error("Error preparing SQL: %s\n", sqlite3_errmsg(this->db));
   }

   rc = sqlite3_exec(this->db, query, NULL, 0, &db_err);
}

void ClientDB::close() {
   sqlite3_close(this->db);
}










