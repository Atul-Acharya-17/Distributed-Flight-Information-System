#ifndef BOOKING_H
#define BOOKING_H

#include "../marshall/Serializable.hpp"

/* 
    Interface for a Booking object used to make reservations in flight.
    Inherits from Serializable which allows to serialize objects.
*/
class Booking : public Serializable
{
public:
    virtual char *getBookingId() = 0;
    void setBookingId(char *bookingId);

    virtual char *getFlightId() = 0;
    void setFlightId(char *flightID);

    virtual char *getClientId() = 0;
    void setClientId(char *clientId);

    virtual int getNumSeatsBooked() = 0;
    void setNumSeatsBooked(int seatsBooked);

    virtual void display() = 0;
};

#endif