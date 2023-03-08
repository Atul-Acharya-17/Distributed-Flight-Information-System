#include <string>
#include <bits/stdc++.h>
#include <stddef.h>

template <typename POD>
class SerializablePOD
{
public:
    static size_t serialize_size(POD str)
    {
        return sizeof(POD);
    }

    static void serialize( char*& target, POD value, int start_idx )
    {
        memcpy( target + start_idx, &value, serialize_size(value) );
    }

    static void deserialize( const char* source, POD& target, int start_idx)
    {
        memcpy( &target, source + start_idx, serialize_size(target) );
    }
};

template<>
size_t SerializablePOD<char*>::serialize_size(char* str)
{
    return sizeof(size_t) + strlen(str);
}

template<>
void SerializablePOD<char*>::serialize(char*& target, char* value, int start_idx)
{
    SerializablePOD<size_t>::serialize(target, strlen(value), start_idx);
    memcpy(target + start_idx + sizeof(size_t), value, strlen(value));
}

template<>
void SerializablePOD<char*>::deserialize( const char* source, char*& target, int start_idx)
{
    size_t length;
    memcpy( &length, source + start_idx, sizeof(size_t) );
    target = new char[length + 1];
    memcpy( target, source + start_idx + sizeof(size_t), length );
    target[length] = '\0';
}