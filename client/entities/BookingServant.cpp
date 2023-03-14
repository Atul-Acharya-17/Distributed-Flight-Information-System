#include "BookingServant.hpp"
#include <string>
#include <iostream>
#include "../marshall/SerializablePOD.hpp"

BookingServant::BookingServant()
{
    this->bookingId = "";
    this->flightId = "";
    this->clientId = "";
    this->numSeatsBooked = -1;
    this->seatPrice = -1;
}
BookingServant::BookingServant(char *bookingId, char *flightId, char *clientId, int numSeatsBooked, float seatPrice)
{
    this->bookingId = bookingId;
    this->flightId = flightId;
    this->clientId = clientId;
    this->numSeatsBooked = numSeatsBooked;
    this->seatPrice = seatPrice;
}
char *BookingServant::getBookingId()
{
    return this->bookingId;
}
void BookingServant::setBookingId(char *bookingId)
{
    strcpy(this->bookingId, bookingId);
}
char *BookingServant::getFlightId()
{
    return this->flightId;
}
void BookingServant::setFlightId(char *flightId)
{
    strcpy(this->flightId, flightId);
}
char *BookingServant::getClientId()
{
    return this->clientId;
}
void BookingServant::setClientId(char *clientId)
{
    strcpy(this->clientId, clientId);
}
int BookingServant::getNumSeatsBooked()
{
    return this->numSeatsBooked;
}
void BookingServant::setNumSeatsBooked(int numSeatsBooked)
{
    this->numSeatsBooked = numSeatsBooked;
}
float BookingServant::getSeatPrice()
{
    return this->seatPrice;
}
void BookingServant::setSeatPrice(float seatPrice)
{
    this->seatPrice = seatPrice;
}

void BookingServant::display()
{
    std::cout << this->bookingId << "@" << this->flightId << "->" << this->clientId << std::endl;
    std::cout << this->numSeatsBooked << "#" << this->seatPrice << std::endl;
}

size_t BookingServant::serialization_size() const
{
    return SerializablePOD<char *>::serialization_size(bookingId) +
           SerializablePOD<char *>::serialization_size(flightId) +
           SerializablePOD<char *>::serialization_size(clientId) +
           SerializablePOD<int>::serialization_size(numSeatsBooked) +
           SerializablePOD<float>::serialization_size(seatPrice);
}
char *BookingServant::serialize() const
{
    int size = serialization_size();

    // Initialize output buffer for serialized string
    char *dataOut = new char[size + 1];
    dataOut[size] = '\0';

    SerializablePOD<char *>::serialize(dataOut, bookingId);
    SerializablePOD<char *>::serialize(dataOut, flightId);
    SerializablePOD<char *>::serialize(dataOut, clientId);
    SerializablePOD<int>::serialize(dataOut, numSeatsBooked);
    SerializablePOD<float>::serialize(dataOut, seatPrice);

    // Reset pointer to start of serialized string and return
    dataOut -= size;
    return dataOut;
}

void BookingServant::deserialize(char *dataIn)
{
    char *bookingId;
    char *flightId;
    char *clientId;
    int numSeatsBooked;
    float seatPrice;

    SerializablePOD<char *>::deserialize(dataIn, bookingId);
    SerializablePOD<char *>::deserialize(dataIn, flightId);
    SerializablePOD<char *>::deserialize(dataIn, clientId);
    SerializablePOD<int>::deserialize(dataIn, numSeatsBooked);
    SerializablePOD<float>::deserialize(dataIn, seatPrice);

    this->bookingId = bookingId;
    this->flightId = flightId;
    this->clientId = clientId;
    this->numSeatsBooked = numSeatsBooked;
    this->seatPrice = seatPrice;
}