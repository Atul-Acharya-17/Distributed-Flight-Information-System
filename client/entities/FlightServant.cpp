#include "FlightServant.hpp"

#include "Flight.hpp"
#include <string>
#include <iostream>
#include <iomanip>

FlightServant::FlightServant()
{
    this->flightId = "";
    this->source = "";
    this->destination = "";
    this->seatsAvailable = -1;
    this->seatsBooked = -1;
    this->price = -1;
    this->departureTime = Time(0);
    this->duration = Time(0);
}
FlightServant::FlightServant(char* flightId, char* source, char* destination, int seatsAvailable, int seatsBooked, float price, int departureTime, int duration)
{
    this->flightId = flightId;
    this->source = source;
    this->destination = destination;
    this->seatsAvailable = seatsAvailable;
    this->seatsBooked = seatsBooked;
    this->price = price;
    this->departureTime = Time(departureTime);
    this->duration = Time(duration);
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
Time FlightServant::getDepartureTime()
{
    return this->departureTime;
}
void FlightServant::setDepartureTime(Time time)
{
    this->departureTime = time;
}
Time FlightServant::getDuration()
{
    return this->duration;
}
void FlightServant::setDuration(Time time)
{
    this->duration = time;
}

void FlightServant::display()
{
    std::cout << std::left << std::setw(19) << "Flight Number" << ':' << '\t' << this->flightId << '\n';
    std::cout << std::left << std::setw(19) << "Source" << ':' << '\t' << this->source << '\n';
    std::cout << std::left << std::setw(19) << "Destination" << ':' << '\t' << this->destination << '\n';
    std::cout << std::left << std::setw(19) << "Departure Time" << ':' << '\t' << this->departureTime.to_string("%H:%M:%S") << '\n';
    std::cout << std::left << std::setw(19) << "Duration" << ':' << '\t' << this->duration.to_string("%H:%M hrs") << '\n';
    std::cout << std::left << std::setw(19) << "Available Seats" << ':' << '\t' << this->seatsAvailable << '\n';
    std::cout << std::left << std::setw(19) << "Booked Seats" << ':' << '\t' << this->seatsBooked << '\n';
    std::cout << std::left << std::setw(19) << "Price" << ':' << '\t' << this->price << "$" << '\n';

    // std::cout << this->flightId << "@" << this->source << "->" << this->destination << std::endl;
    // std::cout << this->seatsAvailable << "-" << this->seatsBooked << "#" << this->price << std::endl;
}

size_t FlightServant::serialization_size() const
{
    return SerializePOD<char* >::serialization_size(flightId) +
           SerializePOD<char* >::serialization_size(source) +
           SerializePOD<char* >::serialization_size(destination) +
           SerializePOD<int>::serialization_size(seatsAvailable) +
           SerializePOD<int>::serialization_size(seatsBooked) +
           SerializePOD<float>::serialization_size(price);
}
char* FlightServant::serialize() const
{
    int size = serialization_size();

    // Initialize output buffer for serialized string
    char* dataOut = new char[size + 1];
    dataOut[size] = '\0';

    SerializePOD<char* >::serialize(dataOut, flightId);
    SerializePOD<char* >::serialize(dataOut, source);
    SerializePOD<char* >::serialize(dataOut, destination);
    SerializePOD<int>::serialize(dataOut, seatsAvailable);
    SerializePOD<int>::serialize(dataOut, seatsBooked);
    SerializePOD<float>::serialize(dataOut, price);
    SerializePOD<int>::serialize(dataOut, departureTime.toSecondOfDay());
    SerializePOD<int>::serialize(dataOut, duration.toSecondOfDay());

    // Reset pointer to start of serialized string and return
    dataOut -= size;
    return dataOut;
}

void FlightServant::deserialize(char* &dataIn)
{
    char* flightId;
    char* source;
    char* destination;
    int seatsAvailable;
    int seatsBooked;
    float price;
    int int_departureTime;
    int int_duration;

    SerializePOD<char*>::deserialize(dataIn, flightId);
    SerializePOD<char*>::deserialize(dataIn, source);
    SerializePOD<char*>::deserialize(dataIn, destination);
    SerializePOD<int>::deserialize(dataIn, seatsAvailable);
    SerializePOD<int>::deserialize(dataIn, seatsBooked);
    SerializePOD<float>::deserialize(dataIn, price);
    SerializePOD<int>::deserialize(dataIn, int_departureTime);
    SerializePOD<int>::deserialize(dataIn, int_duration);

    this->flightId = flightId;
    this->source = source;
    this->destination = destination;
    this->seatsAvailable = seatsAvailable;
    this->seatsBooked = seatsBooked;
    this->price = price;
    this->departureTime = Time(int_departureTime);
    this->duration = Time(int_duration);
}