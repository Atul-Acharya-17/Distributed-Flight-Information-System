#include "BookingServant.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include "../marshall/SerializePOD.hpp"

BookingServant::BookingServant()
{
    this->bookingId = "";
    this->flightId = "";
    this->clientId = "";
    this->numSeatsBooked = -1;
}
BookingServant::BookingServant(char *bookingId, char *flightId, char *clientId, int numSeatsBooked)
{
    this->bookingId = bookingId;
    this->flightId = flightId;
    this->clientId = clientId;
    this->numSeatsBooked = numSeatsBooked;
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

void BookingServant::display()
{
    std::cout << std::left << std::setw(20) << "Booking ID" << ':' << '\t' << this->bookingId << '\n';
    std::cout << std::left << std::setw(20) << "Flight ID" << ':' << '\t' << this->flightId << '\n';
    std::cout << std::left << std::setw(20) << "Customer Name" << ':' << '\t' << this->clientId << '\n';
    std::cout << std::left << std::setw(20) << "Number of Seats Booked" << ':' << '\t' << this->numSeatsBooked << '\n';
}

size_t BookingServant::serialization_size() const
{
    return SerializePOD<char *>::serialization_size(bookingId) +
           SerializePOD<char *>::serialization_size(flightId) +
           SerializePOD<char *>::serialization_size(clientId) +
           SerializePOD<int>::serialization_size(numSeatsBooked);
}

char *BookingServant::serialize() const
{
    int size = serialization_size();

    // Initialize output buffer for serialized string
    char *dataOut = new char[size + 1];
    dataOut[size] = '\0';

    SerializePOD<char *>::serialize(dataOut, bookingId);
    SerializePOD<char *>::serialize(dataOut, flightId);
    SerializePOD<char *>::serialize(dataOut, clientId);
    SerializePOD<int>::serialize(dataOut, numSeatsBooked);

    // Reset pointer to start of serialized string and return
    dataOut -= size;
    return dataOut;
}

void BookingServant::deserialize(char* &dataIn)
{
    char *bookingId;
    char *flightId;
    char *clientId;
    int numSeatsBooked;

    SerializePOD<char *>::deserialize(dataIn, bookingId);
    SerializePOD<char *>::deserialize(dataIn, flightId);
    SerializePOD<char *>::deserialize(dataIn, clientId);
    SerializePOD<int>::deserialize(dataIn, numSeatsBooked);

    this->bookingId = bookingId;
    this->flightId = flightId;
    this->clientId = clientId;
    this->numSeatsBooked = numSeatsBooked;
}