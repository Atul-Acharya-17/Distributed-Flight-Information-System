#ifndef TRIP_H
#define TRIP_H

#include <ctime>
#include <vector>
#include <string>

#include "../marshall/Serializable.hpp"
#include "../utils/utils.hpp"

class Trip : public Serializable 
{
public:
    virtual std::vector<std::string> getFlights() = 0;
    void setFlighs(std::vector<std::string> flightID);

    virtual std::vector<std::string>  getCities() = 0;
    void setCource(std::vector<std::string>  citie);

    virtual std::vector<Time> getDeparturesTimes() = 0;
    void setDeparturesTimes(std::vector<Time> departureTimes);

    virtual std::vector<Time> getDurations() = 0;
    void setDurations(std::vector<Time> durations);
    
    virtual float getPrice() = 0;
    void setPrice(float price);

    virtual void display() = 0;
};

#endif