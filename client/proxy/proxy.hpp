#ifndef PROXY_H
#define PROXY_H

#include <bits/stdc++.h>

class Proxy 
{   
public:
    void handleLocationQuery(std::string ip, int message_id, std::string source, std::string destination);
    void handleFlightQuery(std::string ip, int message_id, std::string flight_id);
    void handleReservation(std::string ip, int message_id, std::string flight_id, int num_seats);
    void handleMonitor(std::string ip, int message_id, std::string flight_id);
};

#endif