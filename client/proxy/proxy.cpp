#include "proxy.hpp"
#include <bits/stdc++.h>
#include <iostream>

#include "../utils/utils.hpp"

#include <bits/stdc++.h>
#include "../message.hpp"

#include "../communication/comms.hpp"
#include "../entities/FlightServant.hpp"

#include "../marshall/SerializablePOD.hpp"

void Proxy::handleFlightQuery(std::string ip, int message_id, std::string flight_id)
{
    int request_type = 0;
    char* client_ip = string_to_array(ip);

    size_t content_size = sizeof(int) + sizeof(size_t) + flight_id.size(); // Service type, type of length, length of string

    char* content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 2;

    SerializablePOD<int>::serialize(content_buffer, service_type);

    SerializablePOD<char*>::serialize(content_buffer, string_to_array(flight_id));

    content_buffer -= content_size;

    CommunicationMessage comm_message(request_type, message_id, client_ip, content_buffer, content_size);
    char* message_buffer = comm_message.serialize();

    Communication::send(message_buffer, comm_message.serialization_size() + 1);

    char* message = Communication::receive();
    
    short status;
    SerializablePOD<short>::deserialize(message, status);
    
    long reply_size;
    SerializablePOD<long>::deserialize(message, reply_size);


    if (status == 1)
    {
        char* error_message;
        SerializablePOD<char*>::deserialize(message, error_message);
        std::cout << error_message << '\n';
        return;
    }

    else 
    {
        FlightServant fs = FlightServant();
        fs.deserialize(message);
        fs.display();
        std::cout << '\n';
    }

}


void Proxy::handleLocationQuery(std::string ip, int message_id, std::string source, std::string destination)
{

    int request_type = 0;
    char* client_ip = string_to_array(ip);

    // Service type, type of length x 2, length of source, length of destination
    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + source.size() + destination.size();

    char* content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 1;

    SerializablePOD<int>::serialize(content_buffer, service_type);
    SerializablePOD<char*>::serialize(content_buffer, string_to_array(source));
    SerializablePOD<char*>::serialize(content_buffer, string_to_array(destination));

    content_buffer -= content_size;

    CommunicationMessage comm_message(request_type, message_id, client_ip, content_buffer, content_size);
    char* message_buffer = comm_message.serialize();

    Communication::send(message_buffer, comm_message.serialization_size() + 1);

    char* message = Communication::receive();
    
    short status;
    SerializablePOD<short>::deserialize(message, status);
    
    long reply_size;
    SerializablePOD<long>::deserialize(message, reply_size);


    if (status == 1)
    {
        char* error_message;
        SerializablePOD<char*>::deserialize(message, error_message);
        std::cout << error_message << '\n';
        return;
    }

    else 
    {
        int num_flights;
        SerializablePOD<int>::deserialize(message, num_flights);

        std::cout << "Num Flights: " << num_flights << '\n';

        for (int i=0; i<num_flights; ++i)
        {
            char* flight_id;
            SerializablePOD<char*>::deserialize(message, flight_id);
            std::cout << flight_id << '\n';
        }
        std::cout << '\n';
    }



}


void Proxy::handleReservation(std::string ip, int message_id, std::string flight_id, int num_seats)
{
    // char* message_type_buff = marshall_int(0);
    // char* client_ip_size = marshall_int(ip.size());
    // char* client_ip = marshall_string(ip);
    // char* message_id_buff = marshall_int(message_id);
    // char* service_id_buff = marshall_int(1);
    // char* flight_id_buff = marshall_string(flight_id);
    // char* flight_id_size_buff = marshall_int(flight_id.size());
    // char* num_seats_buff = marshall_int(num_seats);

    // char* byte_string = new char[sizeof(uint32_t) * 6 + ip.size() + flight_id.size() + 1];
    
    // uint32_t size = 0;

    // memcpy(byte_string, message_type_buff, sizeof(uint32_t));
    // size += sizeof(uint32_t);

    // memcpy(byte_string + size, client_ip_size, sizeof(uint32_t));
    // size += sizeof(uint32_t);

    // memcpy(byte_string + size, client_ip, ip.size());
    // size += ip.size();

    // memcpy(byte_string + size, service_id_buff, sizeof(uint32_t));
    // size += sizeof(uint32_t);

    // memcpy(byte_string + size, flight_id_size_buff, sizeof(uint32_t));
    // size += sizeof(uint32_t);

    // memcpy(byte_string + size, flight_id_buff, flight_id.size());
    // size += flight_id.size();

    // memcpy(byte_string + size, num_seats_buff, sizeof(uint32_t));
    // size += sizeof(uint32_t);

    // byte_string[size] = '\0';
}