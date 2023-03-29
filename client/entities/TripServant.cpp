#include "TripServant.hpp"

#include "Trip.hpp"
#include <string>
#include <iostream>
#include <iomanip>

#include "../marshall/SerializePOD.hpp"


TripServant::TripServant()
{

}

TripServant::TripServant(std::vector<std::string> flights, std::vector<std::string>cities, std::vector<Time> departureTimes, std::vector<Time> durations, float cost, long travelTime)
{
    this->flights = flights;
    this->cities = cities;
    this->cost = cost;
    this->departureTimes = departureTimes;
    this->durations = durations;
    this->travelTime = travelTime;
}
    
std::vector<std::string> TripServant::getFlights()
{
    return this->flights;
}
    
void TripServant::setFlighs(std::vector<std::string> flightIDs)
{
    this->flights = flightIDs;
}

std::vector<std::string>  TripServant::getCities()
{
    return this->cities;
}
    
void TripServant::setCities(std::vector<std::string> cities)
{
    this->cities = cities;
}

std::vector<Time> TripServant::getDeparturesTimes()
{
    return this->departureTimes;
}
    
void TripServant::setDeparturesTimes(std::vector<Time> departureTimes)
{
    this->departureTimes = departureTimes;
}
   
std::vector<Time> TripServant::getDurations()
{
    return this->durations;
}

void TripServant::setDurations(std::vector<Time> durations)
{
    this->durations = durations;
}
    
float TripServant::getPrice()
{
    return this->cost;
}

void TripServant::setPrice(float cost)
{
    this->cost = cost;
}

void TripServant::display()
{
    if ( this->flights.size() ==0 ) return;

    Time travelTime(this->travelTime);

    std::cout << "Price: " << this->cost << "$" << " , Travel Time: "  << travelTime.to_string("%H:%M:%S hrs")<<'\n';

    std::cout << this->cities[0];

    for(int i=0; i<this->flights.size(); ++i)
    {
        std::cout << "(" + this->departureTimes[i].to_string("%H:%M:%S") << ")" << " ---" << this->flights[i]<<"(" << this->durations[i].to_string("%H:%M hrs") << ")" << "---> " << this->cities[i+1];

        if (i==this->flights.size()-1) std::cout << "(" << this->departureTimes[i+1].to_string("%H:%M:%S") << ")\n";
    }

}

size_t TripServant::serialization_size() const
{
    return 1;
}

char* TripServant::serialize() const
{
    return new char[1];
}

void TripServant::deserialize(char* &dataIn)
{
    int num_flights;

    SerializePOD<int>::deserialize(dataIn, num_flights);

    this->flights.clear();
    this->cities.clear();
    this->departureTimes.clear();
    this->durations.clear();

    for (int i=0; i<num_flights; ++i)
    {
        char* flight_id;
        SerializePOD<char*>::deserialize(dataIn, flight_id);
        this->flights.push_back(flight_id);
    }

    for (int i=0; i<num_flights+1; ++i) // 1 more city (destination)
    {
        char* city;
        SerializePOD<char*>::deserialize(dataIn, city);
        this->cities.push_back(city);
    }

    for (int i=0; i<num_flights+1; ++i) // 1 more time (arrival time)
    {
        int time_in_seconds;
        SerializePOD<int>::deserialize(dataIn, time_in_seconds);
        this->departureTimes.push_back(Time(time_in_seconds));
    }

    for (int i=0; i<num_flights; ++i) // 1 more time (arrival time)
    {
        int time_in_seconds;
        SerializePOD<int>::deserialize(dataIn, time_in_seconds);
        this->durations.push_back(Time(time_in_seconds));
    }

    SerializePOD<float>::deserialize(dataIn, this->cost);

    SerializePOD<long>::deserialize(dataIn, this->travelTime);
}

