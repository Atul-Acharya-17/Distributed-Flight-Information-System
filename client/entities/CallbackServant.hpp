#ifndef CALLBACKSERVANT_H
#define CALLBACKSERVANT_H

#include "Flight.hpp"
#include <iostream>
#include <string>
#include "../marshall/Serializable.hpp"
#include "Callback.hpp"

class CallbackServant : public Callback
{
private:
    char *msg;

public:
    CallbackServant();
    CallbackServant(char *msg);
    char *getMsg();
    void setMsg(char *msg);
    // char *getFlightId();
    // void setFlightId(char *flightID);
    // char *getClientId();
    // void setClientId(char *clientId);
    // int getmonitorDuration();
    // void setmonitorDuration(int monitorDuration);

    void displayUpdates();

    size_t serialization_size() const;
    char *serialize() const;
    void deserialize(char *&dataIn);
};

#endif