// Server side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "marshall/SerializablePOD.hpp"

#define PORT	 8080
#define MAXLINE 1024


void un_marshall(char* buffer)
{

	int message_type;;
	int request_id;
	char* ip;
	char* contents;

	SerializablePOD<int>::deserialize(buffer, message_type, 0);
	std::cout << "Message Type: " << message_type << '\n';
	SerializablePOD<int>::deserialize(buffer, request_id, sizeof(int));
	std::cout << "Request ID: " << request_id << '\n';
	SerializablePOD<char*>::deserialize(buffer, ip, 2 * sizeof(int));
	std::cout << "IP: " << ip << '\n';
	SerializablePOD<char*>::deserialize(buffer, contents, 2 * sizeof(int) + sizeof(size_t) + strlen(ip));
	
	std::cout<< message_type << " " << request_id <<  " " << ip <<'\n';

}

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	const char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	socklen_t len;
    int n;

    while (true)
    {
        len = sizeof(cliaddr); //len is value/result

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                    &len);

		std::cout << n << '\n';
        buffer[n] = '\0';
        // printf("Client : %s\n", buffer);
		un_marshall(buffer);
        sendto(sockfd, (const char *)hello, strlen(hello),
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                len);
        std::cout<<"Hello message sent."<<std::endl;
    }    
    return 0;
}
