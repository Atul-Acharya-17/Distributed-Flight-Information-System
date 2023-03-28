#include <string>

#ifndef CALLBACK_H
#define CALLBACK_H
#include "../marshall/Serializable.hpp"

/* 
    Interface for a Callback object used to subscribe to updates from server.
    Inherits from Serializable which allows to serialize objects.
*/
class Callback : public Serializable
{
private:
    char *msg;

public:
    virtual void displayUpdates() = 0;
};

#endif