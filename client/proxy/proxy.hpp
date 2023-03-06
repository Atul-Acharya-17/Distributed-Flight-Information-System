#ifndef PROXY_H
#define PROXY_H

#include <bits/stdc++.h>

class Proxy 
{   
public:
    void handleLocationQuery(std::string ip, uint32_t message_id, std::string source, std::string destination);
    void handleFlightQuery(std::string ip, uint32_t message_id, std::string flight_id);
    void handleReservation(std::string ip, uint32_t message_id, std::string flight_id, uint32_t num_seats);
    void handleMonitor(std::string ip, uint32_t message_id, std::string flight_id);
};

#endif