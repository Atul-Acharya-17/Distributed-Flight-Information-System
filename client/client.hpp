#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
    private:
        int client_id;
        int message_id;
        std::string host_name;
        std::string ip_address;

    public:
        Client(std::string ip);
        void queryLocation();
        void queryFlight();
        void reserveSeats();
        void cancelBooking();
        void checkBooking();
        void monitorUpdates();
        void planTrip();
};

#endif