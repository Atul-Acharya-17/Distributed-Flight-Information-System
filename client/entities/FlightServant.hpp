#include "Flight.hpp"

class FlightServant : public Flight
{
private:
    char* flightId;
    char* source;
    char* destination;
    int seatsAvailable;
    int seatsBooked;
    float price;

public:
    FlightServant(char *flightId, char *source, char *destination, int seatsAvailable, int seatsBooked, float price);
    char* getFlightID();
    void setFlightID(char* flightID);
    char* getSource();
    void setSource(char* source);
    char* getDestination();
    void setDestination(char* destination);
    int getSeatsAvailable();
    void setSeatsAvailable(int seatsAvailable);
    int getSeatsBooked();
    void setSeatsBooked(int seatsBooked);
    float getPrice();
    void setPrice(float price);

    void serialize(char* dataOut);
    void deserialize(const char* dataIn);
};