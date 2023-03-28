#ifndef PROXY_H
#define PROXY_H
#include <bits/stdc++.h>
#include <iostream>
#include <string>

/* 
    Client proxy class used to handle requests for each of the services.
    Each member function marshalls arguments, generates request message, sends to server (using Communication module),  
    waits for server reply, and unmarshalls reply message.
*/
class Proxy 
{
public:
    static void handleLocationQuery(std::string ip, int request_id, std::string source, std::string destination);
    static void handleFlightQuery(std::string ip, int request_id, std::string flight_id);
    static void handleReservation(std::string ip, int request_id, std::string flight_id, std::string customer_name, int num_seats);
    static void handleCancelReservation(std::string ip, int request_id, std::string booking_id);
    static void handleCheckReservation(std::string ip, int request_id, std::string booking_id);
    static void handleMonitor(std::string ip, int request_id, std::string flight_id, int monitoringDuration);
    static void handlePlanTrip(std::string ip, int request_id, std::string source, std::string destination);
};

#endif