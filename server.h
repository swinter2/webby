#ifndef __server
#define __server
		
#include "common.h"
// #include <socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

typedef void (^ConnHandlerBlock)(int newsockfd);
typedef void (^ExitBlock)(int sig);
typedef void (^ErrorBlock)(char *errorMsg);

void startServer();
void stopServer();

#endif

