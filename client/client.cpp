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

	Proxy proxy;
	proxy.handleLocationQuery(this->ip_address, this->request_id, source, destination);

}

void Client::queryFlight()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string flight_id;

	std::cout << "Enter the flight id\n";
	std::getline(std::cin, flight_id);

	Proxy proxy;
	proxy.handleFlightQuery(this->ip_address, this->request_id, flight_id);
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

	std::cout << "Enter the nummber of seats to reserve\n";
	std::cin >> num_seats;

	if (num_seats <= 0)
	{
		std::cerr << "You should book atleast 1 seat\n";
		return;
	}

	Proxy proxy;
	proxy.handleReservation(this->ip_address, this->request_id, flight_id, customer_name, num_seats);
}

void Client::cancelBooking()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string booking_id;

	std::cout << "Enter the booking id\n";
	std::getline(std::cin, booking_id);

	Proxy proxy;
	proxy.handleCancelReservation(this->ip_address, this->request_id, booking_id);
}

void Client::checkBooking()
{
	// Flush the buffer before taking next input
	std::cin.ignore(256, '\n');
	this->request_id++;

	std::string booking_id;

	std::cout << "Enter the booking id\n";
	std::getline(std::cin, booking_id);

	Proxy proxy;
	proxy.handleCheckReservation(this->ip_address, this->request_id, booking_id);
}

void Client::monitorUpdates()
{

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

	Proxy proxy;
	proxy.handlePlanTrip(this->ip_address, this->request_id, source, destination);
}