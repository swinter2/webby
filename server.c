#include "server.h"

HttpServer *ServerInit(
	int portno,
	ConnHandler connHandler, 
	ErrorHandler errorHandler,
	ExitHandler exitHandler 
)
{
	HttpServer *server = (HttpServer*)calloc(1, sizeof(HttpServer));
	server->portno = portno;
	server->loop = 1;
	server->connHandler = connHandler;
	server->errorHandler = errorHandler;
	server->exitHandler = exitHandler;
	return server;
}

void ServerStop(HttpServer *server)
{
	fprintf(stdout, "\nShutting down...\n");
	server->loop = 0;
	close(server->sockfd);
}

void ServerStart(HttpServer *server)
{
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;

	server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server->sockfd < 0)
	{
		server->errorHandler("Error opening socket.");
	}

	int value = 1;
	setsockopt(server->sockfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(server->portno);

	if (bind(server->sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		server->errorHandler("Error on binding.");
	}
	listen(server->sockfd, 5);

	clilen = sizeof(cli_addr);
	pid_t pid;

	fprintf(stdout, "Server listening on %s:%d...\n", "127.0.0.1", server->portno);

	while(server->loop)
	{
		server->newsockfd = accept(server->sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (server->newsockfd < 0)
		{
			server->errorHandler("ERROR on accept.");
		}
		pid = fork();
		if (pid < 0)
		{
			server->errorHandler("ERROR on fork.");
		}
		if (pid == 0)
		{
			close(server->sockfd);
			server->connHandler(server->newsockfd);
			close(server->newsockfd);
			exit(0);
		}
		else
		{
			close(server->newsockfd);
		}
	}
}

