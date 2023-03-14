#include "Flight.hpp"

#ifndef CALLBACK_H
#define CALLBACK_H

class Callback
{
    virtual void flightAdded(Flight f) = 0;
};

#endif