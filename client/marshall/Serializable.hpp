#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <stddef.h>

/* 
    Abstract Class for every object to inherit and implement abstract methods
    We make the objects responsible for marshalling and unmarshalling themselves
*/ 

class Serializable
{
public:
    virtual size_t serialization_size() const = 0;
    virtual char* serialize() const = 0;
    virtual void deserialize( char*& dataIn) = 0;
};

#endif