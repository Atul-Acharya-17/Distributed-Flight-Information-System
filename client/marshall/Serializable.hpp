#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <stddef.h>

class Serializable
{
public:
    virtual size_t serialization_size() const = 0;
    virtual char* serialize() const = 0;
    virtual void deserialize( char*& dataIn) = 0;
};

#endif