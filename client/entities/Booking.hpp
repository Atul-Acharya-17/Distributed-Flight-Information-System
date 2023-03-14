#include "../marshall/Serializable.hpp"

#ifndef BOOKING_H
#define BOOKING_H
class Booking : public Serializable {
    public:
        virtual char* getBookingId() = 0;
        void setBookingId(char* bookingId);

        virtual char* getFlightID() = 0;
        void setFlightID(char* flightID);

        virtual char* getClientId() = 0;
        void setClientId(char* clientId);

        virtual int getNumSeatsBooked() = 0;
        void setNumSeatsBooked(int seatsBooked);

        virtual float getSeatPrice() = 0;
        void setSeatPrice(float price);
};

#endif