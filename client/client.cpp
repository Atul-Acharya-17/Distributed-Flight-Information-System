// Client side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

#include<cassert>

#include "constants.hpp"
#include "proxy/proxy.hpp"

#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char message[MAXLINE];
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n;
	socklen_t len;

	uint32_t choice;

try{
    while (true)
    {	
        std::cout << "Enter Functionality\n";

		for (auto it = functionalities.begin(); it != functionalities.end(); ++it)
		{
			std::cout << it->first << ". " << it->second << '\n';
		}

		std::cin >> choice;

		Proxy p;
		p.handleInfoQuery("Atul");

        sendto(sockfd, (const char *)functionalities[choice], strlen(functionalities[choice]),
            MSG_CONFIRM, (const struct sockaddr *) &servaddr,
                sizeof(servaddr));
        std::cout<<"Hello message sent."<<std::endl;
            
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    &len);
        buffer[n] = '\0';
        std::cout<<"Server : "<<buffer<<std::endl;
    }

	close(sockfd);
}

catch(const std::exception &exec)
{
	std::cerr << "Exception " << exec.what();
}
	return 0;
}
