#ifndef CALLBACKSERVANT_H
#define CALLBACKSERVANT_H

#include "Flight.hpp"
#include <iostream>
#include <string>
#include "../marshall/Serializable.hpp"
#include "Callback.hpp"

/* 
    Servant class for Callback interface.
    Defines state variable for class including callback message.
    Implements methods including getter and setter, display updates, and marshalling-unmarshalling.
*/
class CallbackServant : public Callback
{
private:
    char *msg;

public:
    CallbackServant();
    CallbackServant(char *msg);
    char *getMsg();
    void setMsg(char *msg);

    void displayUpdates();

    size_t serialization_size() const;
    char *serialize() const;
    void deserialize(char *&dataIn);
};

#endif