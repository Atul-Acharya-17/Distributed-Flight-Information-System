#include "comms.hpp"
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>

void Communication::setup(char *server_ip)
{
    std::cout << "Server IP: " << server_ip << '\n';
    // Creating socket file descriptor
    if ((Communication::sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&Communication::servaddr, 0, sizeof(Communication::servaddr));

    // Filling server information
    Communication::servaddr.sin_family = AF_INET;
    Communication::servaddr.sin_port = htons(PORT);
    Communication::servaddr.sin_addr.s_addr = inet_addr(server_ip);

    struct timeval timeout;
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    setsockopt(Communication::sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
}

void Communication::send(const char *message)
{
    sendto(Communication::sockfd, (const char *)message, strlen(message),
           MSG_CONFIRM, (const struct sockaddr *)&Communication::servaddr,
           sizeof(Communication::servaddr));
}

void Communication::send(const char *message, size_t message_size)
{
    sendto(Communication::sockfd, (const char *)message, message_size,
           MSG_CONFIRM, (const struct sockaddr *)&Communication::servaddr,
           sizeof(Communication::servaddr));
}

int Communication::receive(char *&buffer)
{
    buffer = new char[MAXLINE];
    len = sizeof(Communication::servaddr);
    int n = recvfrom(Communication::sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&Communication::servaddr,
                     &Communication::len);
    return n;
}

void Communication::terminate()
{
    close(Communication::sockfd);
}