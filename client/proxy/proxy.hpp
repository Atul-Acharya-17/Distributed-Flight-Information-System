#ifndef PROXY_H
#define PROXY_H

#include <bits/stdc++.h>

class Proxy 
{   
public:
    void handleFlightQuery(uint32_t start, uint32_t end);
    void handleInfoQuery(std::string flight_number);
    void handleReservation();
    void handleMonitor();
};

#endif