

#define NORMAL         "\033[0m"
#define BOLD			  "\033[1m"
#define COLOR_WARNING  "\033[0;33m" //yellow
#define COLOR_ERROR    "\033[0;31m" //red
#define COLOR_FATAL    "\033[1;31m" //red bold


//
// fDebug Config default settings
//
#define DEFAULT_PORT   		5005
#define FDEBUG_LOGFILE     "/var/log/fdebug/proxy.log"
#define FDEBUG_CLIENTDB    "/var/lib/fdebug/proxy.client.db"

#define BUF_SIZE           10000

// Enable Debug Mode
// this option should not be used in produtional environments!
#define DEBUG_MODE         false


// fDebug Message Types
#define FDEBUG_CONTROL     1
#define FDEBUG_MESSAGE     2
#define FDEBUG_WARNING     3
#define FDEBUG_ERROR       4
#define FDEBUG_FATAL       5
#define FDEBUG_VARIABLES   6
#define FDEBUG_SOURCE      7

// Proxy specific message types
#define FDEBUG_REGISTER    8
#define FDEBUG_SETCLIENT   9

