#ifndef SERIALIZABLEPOD_H
#define SERIALIZABLEPOD_H

#include <string>
#include <bits/stdc++.h>
#include <stddef.h>

/*
    Generic class to marshall and unmarshall primitive datatypes
    Templates allowed generic marshalling and unmarshalling

    Strings were handled differently since the lenght needs to be encoded
*/

template <typename POD>
class SerializePOD
{
public:
    static inline size_t serialization_size(POD str)
    {
        return sizeof(POD);
    }

    static inline void serialize( char*& target, POD value )
    {
        memcpy( target, &value, serialization_size(value) );

        if (serialization_size(value) > 1) // Change endian if more than 1 byte
        {
            if (is_little_endian())
            {
                // Reverse ordering for little endian since we are sending to network which has big endian ordering
                for (int i = 0; i < serialization_size(value) / 2; ++i)
                {
                    char temp = *(target + i);
                    *(target + i) = *(target + serialization_size(value) - 1 - i);
                    *(target + serialization_size(value) - 1 - i) = temp;
                }
            }
        }
        target += serialization_size(value);     // Pointer moves forward
    }

    static inline void deserialize( char*& source, POD& target)
    {
        if (serialization_size(target) > 1) // Change endian if more than 1 byte
        {
            if (is_little_endian())
            {
                // Reverse ordering for little endian since we are receiving from network which has big endian ordering
                for (int i = 0; i < serialization_size(target) / 2; ++i)
                {
                    char temp = *(source + i);
                    *(source + i) = *(source + serialization_size(target) - i - 1);
                    *(source + serialization_size(target) - i - 1) = temp;
                }
            }
        }

        memcpy( &target, source, serialization_size(target) );
        source += serialization_size(target);   // Pointer moves forward
    }

    static inline bool is_little_endian()
    {
        unsigned int i = 1;
        char *c = (char*)&i;
        if (*c)
            return true;
        else
            return false;
        }
};


/*
    Function definitions for string datatype
*/
template<>
inline size_t SerializePOD<char*>::serialization_size(char* str)
{
    return sizeof(size_t) + strlen(str);
}

template<>
inline void SerializePOD<char*>::serialize(char*& target, char* value)
{
    SerializePOD<size_t>::serialize(target, strlen(value));
    memcpy(target, value, strlen(value));
    target += strlen(value);    // Pointer moves forward
}

template<>
inline void SerializePOD<char*>::deserialize( char*& source, char*& target)
{
    size_t length;
    SerializePOD<size_t>::deserialize(source, length);
    target = new char[length + 1];
    memcpy( target, source, length );
    source += length;    // Pointer moves forward
    target[length] = '\0';
}

#endif