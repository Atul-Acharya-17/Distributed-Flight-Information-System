#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#include "client.hpp"

#include "proxy/proxy.hpp"

void check_host_name(int hostname) { //This function returns host name for local computer
   if (hostname == -1) {
      perror("gethostname");
      exit(1);
   }
}
void check_host_entry(struct hostent * hostentry) { //find host info from host name
   if (hostentry == NULL){
      perror("gethostbyname");
      exit(1);
   }
}
void IP_formatter(char *IPbuffer) { //convert IP string to dotted decimal format
   if (NULL == IPbuffer) {
      perror("inet_ntoa");
      exit(1);
   }
}

Client::Client()
{
	this->message_id = 0;

	char host[256];
	char *IP;
	struct hostent *host_entry;
	int hostname;
	hostname = gethostname(host, sizeof(host)); //find the host name
	check_host_name(hostname);
	host_entry = gethostbyname(host); //find host information
	check_host_entry(host_entry);
	IP = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0])); //Convert into IP string
	printf("Current Host Name: %s\n", host);
	printf("Host IP: %s\n", IP);
	this->ip_address = IP;
	this->host_name = host;
}


void Client::queryLocation()
{

	std::string source, destination;

	std::cout << "Enter the source location\n";
	std::cin >> source;

	std::cout << "Enter the destination location\n";
	std::cin >> destination;

	Proxy p;
	p.handleLocationQuery(this->ip_address, this->message_id, source, destination);

}

void Client::queryFlight()
{
	std::string flight_id;

	std::cout << "Enter the flight id\n";
	std::cin >> flight_id;
}

void Client::reserveSeats()
{
	std::string flight_id;
	uint32_t num_seats;

	std::cout << "Enter the flight id\n";
	std::cin >> flight_id;

	std::cout << "Enter the nummber of seats to reserve\n";
	std::cin >> num_seats;

	if (num_seats <= 0)
	{
		std::cerr << "You should book atleast 1 seat\n";
		return;
	}
}

void Client::monitorUpdates()
{

}