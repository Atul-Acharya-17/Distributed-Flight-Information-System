#ifndef CLIENT_H
#define CLIENT_H

#include <string>

/* 
    Client class used to interact with the user.
    Defines client state variables including client ID, request ID, and IP address and host name.
    Each member function inputs arguments for a service, and invokes respective proxy function.
*/
class Client
{
    private:
        int client_id;
        int request_id;
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