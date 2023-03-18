#include "FlightServant.hpp"

#include "Flight.hpp"
#include <string>
#include <iostream>

#include "../marshall/SerializablePOD.hpp"

FlightServant::FlightServant()
{
    this->flightId = "";
    this->source = "";
    this->destination = "";
    this->seatsAvailable = -1;
    this->seatsBooked = -1;
    this->price = -1;
}
FlightServant::FlightServant(char* flightId, char* source, char* destination, int seatsAvailable, int seatsBooked, float price)
{
    this->flightId = flightId;
    this->source = source;
    this->destination = destination;
    this->seatsAvailable = seatsAvailable;
    this->seatsBooked = seatsBooked;
    this->price = price;
}
char* FlightServant::getFlightID()
{
    return this->flightId;
}
void FlightServant::setFlightID(char* flightId)
{
    strcpy(this->flightId, flightId);
}
char* FlightServant::getSource()
{
    return this->source;
}
void FlightServant::setSource(char* source)
{
    strcpy(this->source, source);
}
char* FlightServant::getDestination()
{
    return this->destination;
}
void FlightServant::setDestination(char* destination)
{
    strcpy(this->destination, destination);
}
int FlightServant::getSeatsAvailable()
{
    return this->seatsAvailable;
}
void FlightServant::setSeatsAvailable(int seatsAvaiable)
{
    this->seatsAvailable = seatsAvaiable;
}
int FlightServant::getSeatsBooked()
{
    return this->seatsBooked;
}
void FlightServant::setSeatsBooked(int seatsBooked)
{
    this->seatsBooked = seatsBooked;
}
float FlightServant::getPrice()
{
    return this->price;
}
void FlightServant::setPrice(float price)
{
    this->price = price;
}

void FlightServant::display()
{
    std::cout << this->flightId << "@" << this->source << "->" << this->destination << std::endl;
    std::cout << this->seatsAvailable << "-" << this->seatsBooked << "#" << this->price << std::endl;
}

size_t FlightServant::serialization_size() const
{
    return SerializablePOD<char* >::serialization_size(flightId) +
           SerializablePOD<char* >::serialization_size(source) +
           SerializablePOD<char* >::serialization_size(destination) +
           SerializablePOD<int>::serialization_size(seatsAvailable) +
           SerializablePOD<int>::serialization_size(seatsBooked) +
           SerializablePOD<float>::serialization_size(price);
}
char* FlightServant::serialize() const
{
    int size = serialization_size();

    // Initialize output buffer for serialized string
    char* dataOut = new char[size + 1];
    dataOut[size] = '\0';

    SerializablePOD<char* >::serialize(dataOut, flightId);
    SerializablePOD<char* >::serialize(dataOut, source);
    SerializablePOD<char* >::serialize(dataOut, destination);
    SerializablePOD<int>::serialize(dataOut, seatsAvailable);
    SerializablePOD<int>::serialize(dataOut, seatsBooked);
    SerializablePOD<float>::serialize(dataOut, price);

    // Reset pointer to start of serialized string and return
    dataOut -= size;
    return dataOut;
}

void FlightServant::deserialize(char* dataIn)
{
    char* flightId;
    char* source;
    char* destination;
    int seatsAvailable;
    int seatsBooked;
    float price;

    SerializablePOD<char*>::deserialize(dataIn, flightId);
    SerializablePOD<char*>::deserialize(dataIn, source);
    SerializablePOD<char*>::deserialize(dataIn, destination);
    SerializablePOD<int>::deserialize(dataIn, seatsAvailable);
    SerializablePOD<int>::deserialize(dataIn, seatsBooked);
    SerializablePOD<float>::deserialize(dataIn, price);

    this->flightId = flightId;
    this->source = source;
    this->destination = destination;
    this->seatsAvailable = seatsAvailable;
    this->seatsBooked = seatsBooked;
    this->price = price;
}