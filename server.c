#include "server.h"

// globals
int sockfd, newsockfd, portno;

// only keep the main loop going if this is true.
ushort loop = 1;

void stopServer()
{
	fprintf("\nShutting down...\n");
	loop = 0;
	close(sockfd);
}

void _exitHandler(int sig)
{
	stopServer();
}

void startServer(int portno, ConnHandlerBlock connHandler, ErrorBlock errorHandler)
{
	// ignore signals that I don't care about...
	signal(SIGCHLD, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, _exitHandler);
	signal(SIGQUIT, _exitHandler);
	signal(SIGTERM, _exitHandler);

	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		errorHandler("Error opening socket.");
	}

	int value = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		errorHandler("Error on binding.");
	}
	listen(sockfd, 5);

	clilen = sizeof(cli_addr);
	pid_t pid;

	fprintf(stdout, "Server listening on %s:%d...\n", "127.0.0.1", portno);

	while(loop)
	{
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0)
		{
			errorHandler("ERROR on accept.");
		}
		pid = fork();
		if (pid < 0)
		{
			errorHandler("ERROR on fork.");
		}
		if (pid == 0)
		{
			close(sockfd);
			connHandler(newsockfd);
			close(newsockfd);
			exit(0);
		}
		else
		{
			close(newsockfd);
		}
	}
}

