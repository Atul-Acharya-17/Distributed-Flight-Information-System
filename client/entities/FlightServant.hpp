#include "Flight.hpp"
#include "../marshall/SerializablePOD.hpp"

#ifndef FLIGHTSERVANT_H
#define FLIGHTSERVANT_H

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
    FlightServant();
    FlightServant(char* flightId, char* source, char* destination, int seatsAvailable, int seatsBooked, float price);
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

    void display();

    size_t serialization_size() const;
    char* serialize() const;
    void deserialize(char* dataIn);
};

#endif