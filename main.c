#include "common.h"
#include "server.h"

int main(int argc, char** argv)
{
	startServer(8000, 
		^(int sockfd) {
			size_t len = 1024;
			char buffer[len];
			ssize_t n;
			bzero(buffer, len);

			n = read(sockfd, buffer, len-1);
			if (n < 0)
			{
				printf("Error reading from socket.");
			}

			char *response = "Hello world!";

			n = write(sockfd, response, strlen(response));

			if (n < 0)
			{
				printf("Error reading from socket.");
			}
		},
		^(char *errorMsg) {

		}
		);

	return 0;
}