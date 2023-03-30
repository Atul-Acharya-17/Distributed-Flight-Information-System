#ifndef TRIP_SERVANT_H
#define TRIP_SERVANT_H

#include "Trip.hpp"
#include "../marshall/SerializePOD.hpp"

/* 
    Servant class for Trip interface.
    Defines state variables for class including array of flights, cities, departure time, and duration of flights in multi-city trip.
    Implements methods including getters and setters, display, and marshalling-unmarshalling.
*/
class TripServant : public Trip
{
private:
    std::vector<std::string> flights;
    std::vector<std::string> cities;
    std::vector<Time> departureTimes;
    std::vector<Time> durations;
    float cost;
    long travelTime;

public:
    TripServant();
    TripServant(std::vector<std::string>, std::vector<std::string>, std::vector<Time>, std::vector<Time>, float price, long travelTime);
    
    std::vector<std::string> getFlights();
    void setFlighs(std::vector<std::string> flightID);

    std::vector<std::string>  getCities();
    void setCities(std::vector<std::string>  cities);

    std::vector<Time> getDeparturesTimes();
    void setDeparturesTimes(std::vector<Time> departureTimes);

    std::vector<Time> getDurations();
    void setDurations(std::vector<Time> durations);
    
    float getPrice();
    void setPrice(float price);

    void display();

    size_t serialization_size() const;
    char* serialize() const;
    void deserialize(char* &dataIn);
};

#endif