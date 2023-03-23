#ifndef FLIGHTSERVANT_H
#define FLIGHTSERVANT_H

#include "Flight.hpp"
#include "../marshall/SerializablePOD.hpp"

class FlightServant : public Flight
{
private:
    char* flightId;
    char* source;
    char* destination;
    int seatsAvailable;
    int seatsBooked;
    float price;
    Time departureTime;
    Time duration;

public:
    FlightServant();
    FlightServant(char* flightId, char* source, char* destination, int seatsAvailable, int seatsBooked, float price, int departureTime, int duration);
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
    Time getDepartureTime();
    void setDepartureTime(Time time);
    Time getDuration();
    void setDuration(Time time);

    void display();

    size_t serialization_size() const;
    char* serialize() const;
    void deserialize(char* &dataIn);
};

#endif