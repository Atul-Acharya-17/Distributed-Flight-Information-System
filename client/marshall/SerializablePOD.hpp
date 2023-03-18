#include <string>
#include <bits/stdc++.h>
#include <stddef.h>

#ifndef SERIALIZABLEPOD_H
#define SERIALIZABLEPOD_H

template <typename POD>
class SerializablePOD
{
public:
    static inline size_t serialization_size(POD str)
    {
        return sizeof(POD);
    }

    static inline void serialize( char*& target, POD value )
    {
        memcpy( target, &value, serialization_size(value) );
        target += serialization_size(value);
    }

    static inline void deserialize( char*& source, POD& target)
    {
        memcpy( &target, source, serialization_size(target) );
        source += serialization_size(target);
    }
};

template<>
inline size_t SerializablePOD<char*>::serialization_size(char* str)
{
    return sizeof(size_t) + strlen(str);
}

template<>
inline void SerializablePOD<char*>::serialize(char*& target, char* value)
{
    SerializablePOD<size_t>::serialize(target, strlen(value));
    memcpy(target, value, strlen(value));
    target += strlen(value);
}

template<>
inline void SerializablePOD<char*>::deserialize( char*& source, char*& target)
{
    size_t length;
    SerializablePOD<size_t>::deserialize(source, length);
    target = new char[length + 1];
    memcpy( target, source, length );
    source += length;
    target[length] = '\0';
}

#endif