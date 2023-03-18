
// #include <string>
// #include <bits/stdc++.h>
// #include <stddef.h>

// #include "SerializablePOD.hpp"

// namespace SerializablePOD
// {
//     template <typename POD>
//     size_t serialization_size(POD str)
//     {
//         return sizeof(POD);
//     }

//     template <typename POD>
//     void serialize( char*& target, POD value )
//     {
//         memcpy( target, &value, serialization_size(value) );
//         target += serialization_size(value);
//     }

//     template <typename POD>
//     void deserialize( char*& source, POD& target)
//     {
//         memcpy( &target, source, serialization_size(target) );
//         source += serialization_size(target);
//     }

//     template<>
//     size_t serialization_size(char* str)
//     {
//         return sizeof(size_t) + strlen(str);
//     }

//     template<>
//     void serialize(char*& target, char* value)
//     {
//         SerializablePOD::serialize(target, strlen(value));
//         memcpy(target, value, strlen(value));
//         target += strlen(value);
//     }

//     template<>
//     void deserialize( char*& source, char*& target)
//     {
//         size_t length;
//         SerializablePOD::deserialize(source, length);
//         target = new char[length + 1];
//         memcpy( target, source, length );
//         source += length;
//         target[length] = '\0';
//     }
// };