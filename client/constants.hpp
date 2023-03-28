#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>

std::map<int, char*> functionalities = {
    {1, "Query Flights"},
    {2, "Query Flight Information"},
    {3, "Make Booking"},
    {4, "Cancel Booking"},
    {5, "Check Booking"},
    {6, "Monitor Updates"},
    {7, "Plan Trip"},
    {0, "Terminate"}
};


#endif