#include "Trip.hpp"
#include "../marshall/SerializablePOD.hpp"

#ifndef TRIP_SERVANT_H
#define TRIP_SERVANT_H

class TripServant : public Trip
{
private:
    std::vector<std::string> flights;
    std::vector<std::string> cities;
    std::vector<Time> departureTimes;
    std::vector<Time> durations;
    float cost;

public:
    TripServant();
    TripServant(std::vector<std::string>, std::vector<std::string>, std::vector<Time>, std::vector<Time>, float price);
    
    std::vector<std::string> getFlights();
    void setFlighs(std::vector<std::string> flightID);

    std::vector<std::string>  getCities();
    void setCource(std::vector<std::string>  citie);

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