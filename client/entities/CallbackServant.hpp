#include "Flight.hpp"
#include <iostream>

#ifndef CALLBACKSERVANT_H
#define CALLBACKSERVANT_H

class Callback
{
    void flightAdded(Flight f)
    {
        std::cout << "New flight added:" << std::endl;
        f.display();
    }
};

#endif