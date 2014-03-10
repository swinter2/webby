#include "common.h"
#include "server.h"

void handleRequest(int sockfd);
void handleError(char *errorMsg);
void exitHandler();

int main(int argc, char** argv)
{
	// ignore signals that I don't care about...
	signal(SIGCHLD, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, exitHandler);
	signal(SIGQUIT, exitHandler);
	signal(SIGTERM, exitHandler);

	HttpServer *server = ServerInit(8000, handleRequest, handleError, exitHandler);
	ServerStart(server);

	return 0;
}

void exitHandler()
{
	printf("Shutting down...\n");
	exit(0);
}

void handleRequest(int sockfd)
{
	size_t len = 1024;
	char buffer[len];
	ssize_t n;
	bzero(buffer, len);

	n = read(sockfd, buffer, len-1);
	if (n < 0)
	{
		handleError("Error reading from socket.");
	}

	char *response = "Hello world!";

	n = write(sockfd, response, strlen(response));

	if (n < 0)
	{
		handleError("Error writing to socket.");
	}
}

void handleError(char *errorMsg)
{
	printf("%s\n", errorMsg);
}