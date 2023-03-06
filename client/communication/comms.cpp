#include "comms.hpp"
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>

void Communication::setup()
{
    	// Creating socket file descriptor
	if ( (Communication::sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&Communication::servaddr, 0, sizeof(Communication::servaddr));
	
	// Filling server information
	Communication::servaddr.sin_family = AF_INET;
	Communication::servaddr.sin_port = htons(PORT);
	Communication::servaddr.sin_addr.s_addr = INADDR_ANY;
}

void Communication::send(const char* message)
{
    sendto(Communication::sockfd, (const char *)message, strlen(message),
            MSG_CONFIRM, (const struct sockaddr *) &Communication::servaddr,
                sizeof(Communication::servaddr));
}

char* Communication::receive()
{
    int n = recvfrom(Communication::sockfd, (char *)Communication::buffer, MAXLINE,
                    MSG_WAITALL, (struct sockaddr *) &Communication::servaddr,
                    &Communication::len);
    Communication::buffer[n] = '\0';

    return (char*) Communication::buffer;
}

void Communication::terminate()
{
    close(Communication::sockfd);
}