#include <string>

#ifndef PROXY_H
#define PROXY_H

class Proxy 
{   
public:
    void handleLocationQuery(std::string ip, int request_id, std::string source, std::string destination);
    void handleFlightQuery(std::string ip, int request_id, std::string flight_id);
    void handleReservation(std::string ip, int request_id, std::string flight_id, std::string customer_name, int num_seats);
    void handleCancelReservation(std::string ip, int request_id, std::string booking_id);
    void handleCheckReservation(std::string ip, int request_id, std::string booking_id);
    void handleMonitor(std::string ip, int request_id, std::string flight_id);
    void handlePlanTrip(std::string ip, int request_id, std::string source, std::string destination);
};

#endif