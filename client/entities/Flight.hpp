#ifndef FLIGHT_H
#define FLIGHT_H

#include "../marshall/Serializable.hpp"
#include "../utils/utils.hpp"

/* 
    Interface for a Flight object containing information related to a flight.
    Inherits from Serializable which allows to serialize objects.
*/
class Flight : public Serializable 
{
public:
    virtual char* getFlightID() = 0;
    void setFlightID(char* flightID);

    virtual char* getSource() = 0;
    void setSource(char* source);

    virtual char* getDestination() = 0;
    void setDestination(char* destination);

    virtual int getSeatsAvailable() = 0;
    void setSeatsAvailable(int seatsAvailable);

    virtual int getSeatsBooked() = 0;
    void setSeatsBooked(int seatsBooked);
    
    virtual float getPrice() = 0;
    void setPrice(float price);

    virtual Time getDepartureTime() = 0;
    void setDepartureTime(Time time);

    virtual Time getDuration() = 0;
    void setDuration(Time time);

    virtual void display() = 0;
};

#endif