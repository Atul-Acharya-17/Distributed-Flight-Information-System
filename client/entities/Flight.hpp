#ifndef FLIGHT_H
#define FLIGHT_H

#include "../marshall/Serializable.hpp"

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

    virtual void display() = 0;
};

#endif