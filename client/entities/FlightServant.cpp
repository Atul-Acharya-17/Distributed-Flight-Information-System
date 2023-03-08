#include "FlightServant.hpp"
#include <string>
#include "../marshall/SerializablePOD.hpp"

char* FlightServant::getFlightID() {
    return this->flightId;
}
void FlightServant::setFlightID(char* flightId) {
    strcpy(this->flightId, flightId);
}
char* FlightServant::getSource() {
    return this->source;
}
void FlightServant::setSource(char* source) {
    strcpy(this->source, source);
}
char* FlightServant::getDestination() {
    return this->destination;
}
void FlightServant::setDestination(char* destination) {
    strcpy(this->destination, destination);
}
int FlightServant::getSeatsAvailable() {
    return this->seatsAvailable;
}
void FlightServant::setSeatsAvailable(int seatsAvaiable) {
    this->seatsAvailable = seatsAvaiable;
}
int FlightServant::getSeatsBooked() {
    return this->seatsBooked;
}
void FlightServant::setSeatsBooked(int seatsBooked) {
    this->seatsBooked = seatsBooked;
}
float FlightServant::getPrice() {
    return this->price;
}
void FlightServant::setPrice(float price) {
    this->price = price;
}

void FlightServant::serialize(char* dataOut)
{
    dataOut = SerializablePOD<char*>::serialize(dataOut, flightId);
    dataOut = SerializablePOD<char*>::serialize(dataOut, source);
    dataOut = SerializablePOD<char*>::serialize(dataOut, destination);
    dataOut = SerializablePOD<int>::serialize(dataOut, seatsAvailable);
    dataOut = SerializablePOD<int>::serialize(dataOut, seatsBooked);
    dataOut = SerializablePOD<float>::serialize(dataOut, price);
}

void FlightServant::deserialize(const char* dataIn)
{
    dataIn = SerializablePOD<char*>::deserialize(dataIn, flightId);
    dataIn = SerializablePOD<char*>::deserialize(dataIn, source);
    dataIn = SerializablePOD<char*>::deserialize(dataIn, destination);
    dataIn = SerializablePOD<int>::deserialize(dataIn, seatsAvailable);
    dataIn = SerializablePOD<int>::deserialize(dataIn, seatsBooked);
    dataIn = SerializablePOD<float>::deserialize(dataIn, price);
}