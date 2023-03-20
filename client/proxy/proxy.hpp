#include <string>

#ifndef PROXY_H
#define PROXY_H

class Proxy 
{   
public:
    void handleLocationQuery(std::string ip, int message_id, std::string source, std::string destination);
    void handleFlightQuery(std::string ip, int message_id, std::string flight_id);
    void handleReservation(std::string ip, int message_id, std::string flight_id, std::string customer_name, int num_seats);
    void handleCancelReservation(std::string ip, int message_id, std::string booking_id);
    void handleCheckReservation(std::string ip, int message_id, std::string booking_id);
    void handleMonitor(std::string ip, int message_id, std::string flight_id);
};

#endif