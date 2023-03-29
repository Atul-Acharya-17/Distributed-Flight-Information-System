#include "Flight.hpp"
#include <iostream>
#include <string>
#include "../marshall/SerializePOD.hpp"
#include "CallbackServant.hpp"

CallbackServant::CallbackServant()
{
    this->msg = "";
}

void CallbackServant::displayUpdates()
{
    std::cout << std::left << std::setw(19) << this->msg;
}

size_t CallbackServant::serialization_size() const
{
    return SerializePOD<char *>::serialization_size(msg);
}

char *CallbackServant::serialize() const
{
    int size = serialization_size();

    // Initialize output buffer for serialized string
    char *dataOut = new char[size + 1];
    dataOut[size] = '\0';

    SerializePOD<char *>::serialize(dataOut, msg);

    // Reset pointer to start of serialized string and return
    dataOut -= size;
    return dataOut;
}

void CallbackServant::deserialize(char *&dataIn)
{
    char *msg;
    SerializePOD<char *>::deserialize(dataIn, msg);
    this->msg = msg;
}