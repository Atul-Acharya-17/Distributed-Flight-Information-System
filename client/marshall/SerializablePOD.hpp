#include <string>
#include <bits/stdc++.h>
#include <stddef.h>

#ifndef SERIALIZABLEPOD_H
#define SERIALIZABLEPOD_H

template <typename POD>
class SerializablePOD
{
public:
    static size_t serialize_size(POD str)
    {
        return sizeof(POD);
    }

    static void serialize( char*& target, POD value )
    {
        memcpy( target, &value, serialize_size(value) );
        target += serialize_size(value);
    }

    static void deserialize( char*& source, POD& target)
    {
        memcpy( &target, source, serialize_size(target) );
        source += serialize_size(target);
    }
};

template<>
size_t SerializablePOD<char*>::serialize_size(char* str)
{
    return sizeof(size_t) + strlen(str);
}

template<>
void SerializablePOD<char*>::serialize(char*& target, char* value)
{
    SerializablePOD<size_t>::serialize(target, strlen(value));
    memcpy(target, value, strlen(value));
    target += strlen(value);
}

template<>
void SerializablePOD<char*>::deserialize( char*& source, char*& target)
{
    size_t length;
    SerializablePOD<size_t>::deserialize(source, length);
    target = new char[length + 1];
    memcpy( target, source, length );
    source += length;
    target[length] = '\0';
}

#endif