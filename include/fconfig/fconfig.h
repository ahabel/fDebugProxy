#ifndef FCONFIG_H_
#define FCONFIG_H_

#include "fconfig/storage.fconfig.h"
using namespace std;

class fConfig {
public:
	static fConfig* getInstance();
	bool   loadFile(char *filename);

protected:
	fConfig() {}
	fConfig(fConfig const&){};            // copy constructor is private
	fConfig& operator=(fConfig const&){}; // assignment operator is private
	static fConfig* m_pInstance;
	
	fConfigStorage *config;
	
	string trim(string str);
	
	
};

#endif /*FCONFIG_H_*/
