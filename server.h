#ifndef __server
#define __server
		
#include "common.h"
// #include <socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

typedef void (*ConnHandler)(int newsockfd);
typedef void (*ExitHandler)();
typedef void (*LogHandler)(char *errorMsg);
typedef void (*ErrorHandler)(char *errorMsg);

typedef struct {
	int sockfd;
	int newsockfd;
	int portno;
	unsigned short loop;
	// LogHandler logHandler;
	ConnHandler connHandler;
	ErrorHandler errorHandler;
	ExitHandler exitHandler;
} HttpServer;

HttpServer *ServerInit(
	int portno,
	ConnHandler connHandler, 
	ErrorHandler errorHandler,
	ExitHandler exitHandler 
	);
void ServerStart(HttpServer *server);
void ServerStop(HttpServer *server);

#endif

