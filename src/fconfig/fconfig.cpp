#include "string.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <ctime>
#include <sys/stat.h>
#include <stdarg.h>
#include "fconfig/fconfig.h"
#include "fconfig/storage.fconfig.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


fConfig* fConfig::m_pInstance = NULL;

fConfig* fConfig::getInstance() {
   if (!m_pInstance) {
      m_pInstance = new fConfig;
   }
   return m_pInstance;
}

bool fConfig::loadFile(char *filename) {
   ifstream in(filename);
   if (!in.is_open()) {
      perror("Cannot open configuration file");
      exit(0);
   }
   
   string line;
   this->config = new fConfigStorage;
   
   while(getline(in, line)) {
      string::size_type i = line.find_first_not_of(" \t\n\v");
      
      if (i != string::npos && line[i] == '#') {
         continue;
      }
      
      if (line.length() == 0) {
         continue;
      }
      //printf("line: [%s]\n", line.c_str());
      
      string::size_type x = line.find_first_of("=");
      if (x == string::npos) {
         printf("Syntax error\n");
         exit(0);
      }
      
      string key   = line.substr(0,x);
      string value = line.substr(x+1, line.length());
      key   = this->trim(key);
      value = this->trim(value);
      
      this->config->add(key, value);
      //printf("[%s] -> [%s]\n", key.c_str(), value.c_str());
   }
   
   this->config->printList();
   
   
   /*
   FILE *fh = fopen(filename, "r");
   if (!fh) {
      perror("Cannot open configuration file");
      exit(0);
   }
   
   char line[1024];
   while(fgets(line, sizeof line, fh) != NULL) {
      if (strspn(line, " \t\n\v") > 0) {
         continue;
      }
      
      if (line[0] == '#') {
         continue;
      }
      
      if (line[strlen(line)-1] == '\n') {
         line[strlen(line)-1] = '\0';
      }
      
      printf("line [%s]\n", line);
      
      if (find(
   }*/
   
   printf("Loaded configuration: %s\n", filename);
   return true;
}

string fConfig::trim(string str) {
   str = str.erase(0, str.find_first_not_of(" "));
   str = str.erase(str.find_last_not_of(" ")+1);
   return str;
}















