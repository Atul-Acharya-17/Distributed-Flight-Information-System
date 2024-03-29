#ifndef BOOKINGSERVANT_H
#define BOOKINGSERVANT_H

#include "Booking.hpp"

/* 
    Servant class for Booking interface.
    Defines state variables for class including booking ID, flight ID, client ID, number seats booked.
    Implements methods including getters and setters, display, and marshalling-unmarshalling.
*/
class BookingServant : public Booking
{
private:
    char* bookingId;
    char* flightId;
    char* clientId;
    int numSeatsBooked;

public:
    BookingServant();
    BookingServant(char *bookingId, char *flightId, char *clientId, int numSeatsBooked);
    char* getBookingId();
    void setBookingId(char* bookingID);
    char* getFlightId();
    void setFlightId(char* flightID);
    char* getClientId();
    void setClientId(char* clientId);
    int getNumSeatsBooked();
    void setNumSeatsBooked(int numSeatsBooked);

    void display();

    size_t serialization_size() const;
    char* serialize() const;
    void deserialize(char* &dataIn);
};

#endif