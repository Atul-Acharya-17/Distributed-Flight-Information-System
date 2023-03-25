#include "client.hpp"

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
#include <string>
#include "proxy/proxy.hpp"
#include <string>

// void check_host_name(int hostname) { //This function returns host name for local computer
//    if (hostname == -1) {
//       perror("gethostname");
//       exit(1);
//    }
// }
// void check_host_entry(struct hostent * hostentry) { //find host info from host name
//    if (hostentry == NULL){
//       perror("gethostbyname");
//       exit(1);
//    }
// }
// void IP_formatter(char *IPbuffer) { //convert IP string to dotted decimal format
//    if (NULL == IPbuffer) {
//       perror("inet_ntoa");
//       exit(1);
//    }
// }

Client::Client(std::string ip)
{
	this->request_id = 0;
	this->ip_address = ip;
}

void Client::queryLocation()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string source, destination;

	std::cout << "Enter the source location\n";
	std::getline(std::cin, source);

	std::cout << "Enter the destination location\n";
	std::getline(std::cin, destination);

	Proxy p;
	p.handleLocationQuery(this->ip_address, this->request_id, source, destination);
}

void Client::queryFlight()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string flight_id;

	std::cout << "Enter the flight id\n";
	std::getline(std::cin, flight_id);

	Proxy p;
	p.handleFlightQuery(this->ip_address, this->request_id, flight_id);
}

void Client::reserveSeats()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string flight_id;
	std::string customer_name;
	uint32_t num_seats;

	std::cout << "Enter the flight id\n";
	std::getline(std::cin, flight_id);

	std::cout << "Enter customer full name\n";
	std::getline(std::cin, customer_name);

	std::cout << "Enter the number of seats to reserve\n";
	std::cin >> num_seats;

	if (num_seats <= 0)
	{
		std::cerr << "You should book atleast 1 seat\n";
		return;
	}

	Proxy p;
	p.handleReservation(this->ip_address, this->request_id, flight_id, customer_name, num_seats);
}

void Client::cancelBooking()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string booking_id;

	std::cout << "Enter the booking id\n";
	std::getline(std::cin, booking_id);

	Proxy p;
	p.handleCancelReservation(this->ip_address, this->request_id, booking_id);
}

void Client::checkBooking()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string booking_id;

	std::cout << "Enter the booking id\n";
	std::getline(std::cin, booking_id);

	Proxy p;
	p.handleCheckReservation(this->ip_address, this->request_id, booking_id);
}

void Client::monitorUpdates()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string flight_id;
	std::uint32_t monitoringDuration; // in terms of minutes

	std::cout << "Enter the Flight ID for monitoring seat updates\n";
	std::getline(std::cin, flight_id);
	std::cout << "For how many second(s) would you like to monitor this flight?\n";
	std::cin >> monitoringDuration;
	std::cout << "You are now monitoring seat avail updates for flight " << flight_id << std::endl;

	Proxy p;
	p.handleMonitor(this->ip_address, this->request_id, flight_id, monitoringDuration);
}

void Client::planTrip()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string source, destination;
	std::cout << "Enter the source location\n";
	std::getline(std::cin, source);

	std::cout << "Enter the destination location\n";
	std::getline(std::cin, destination);

	Proxy p;
	p.handlePlanTrip(this->ip_address, this->request_id, source, destination);
}