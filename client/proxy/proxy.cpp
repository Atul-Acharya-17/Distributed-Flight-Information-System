#include "proxy.hpp"
#include <bits/stdc++.h>
#include <iostream>

#include "../utils/utils.hpp"

#include <bits/stdc++.h>
#include "../message.hpp"

#include "../communication/comms.hpp"
#include "../entities/FlightServant.hpp"
#include "../entities/BookingServant.hpp"
#include "../entities/TripServant.hpp"

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


void Proxy::handlePlanTrip(std::string ip, int message_id, std::string source, std::string destination)
{

    int request_type = 0;
    char* client_ip = string_to_array(ip);

    // Service type, type of length x 2, length of source, length of destination
    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + source.size() + destination.size();

    char* content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 6;

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
        int num_trips;
        SerializablePOD<int>::deserialize(message, num_trips);

        std::cout << "Num Trips: " << num_trips << '\n';

        for (int t=0; t<num_trips; ++t)
        {

            TripServant ts;
            ts.deserialize(message);
            ts.display();
            std::cout << '\n';
        }

    }

}


void Proxy::handleReservation(std::string ip, int message_id, std::string flight_id, std::string customer_name, int num_seats)
{
    int request_type = 0;
    char* client_ip = string_to_array(ip);

    // Service type, 2 * type of length, length of flight_id, length of customer_name, num_seats
    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + flight_id.size() + customer_name.size() + sizeof(num_seats);

    char* content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 3;

    SerializablePOD<int>::serialize(content_buffer, service_type);

    SerializablePOD<char*>::serialize(content_buffer, string_to_array(flight_id));
    SerializablePOD<char*>::serialize(content_buffer, string_to_array(customer_name));
    SerializablePOD<int>::serialize(content_buffer, num_seats);

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
        BookingServant bs = BookingServant();
        bs.deserialize(message);
        bs.display();
        std::cout << '\n';
    }
}

void Proxy::handleCancelReservation(std::string ip, int message_id, std::string booking_id)
{
    int request_type = 0;
    char* client_ip = string_to_array(ip);

    // Service type, type of length, length of booking_id
    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + booking_id.size();

    char* content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 4;

    SerializablePOD<int>::serialize(content_buffer, service_type);

    SerializablePOD<char*>::serialize(content_buffer, string_to_array(booking_id));

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
        char* confirmation_message;
        SerializablePOD<char*>::deserialize(message, confirmation_message);
        std::cout << confirmation_message << '\n';
        return;
    }

}
void Proxy::handleCheckReservation(std::string ip, int message_id, std::string booking_id)
{
    int request_type = 0;
    char* client_ip = string_to_array(ip);

    // Service type, type of length, length of booking_id
    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + booking_id.size();

    char* content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 5;

    SerializablePOD<int>::serialize(content_buffer, service_type);

    SerializablePOD<char*>::serialize(content_buffer, string_to_array(booking_id));

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
        BookingServant bs = BookingServant();
        bs.deserialize(message);
        bs.display();
        std::cout << '\n';
    }
}