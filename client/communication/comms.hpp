#ifndef COMMS_H
#define COMMS_H

#define PORT	 8080
#define MAXLINE 100000

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class Communication
{

    private:
        inline static int n;
        inline static int sockfd;
    	inline static socklen_t len;
        inline static char buffer[MAXLINE];
        inline static struct sockaddr_in	 servaddr;

    public:

        static void setup();
        static void send(const char* message);
        static char* receive();
        static void terminate();
    
};

#endif