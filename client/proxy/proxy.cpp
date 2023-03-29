#include "proxy.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <ctime>

#include "../utils/utils.hpp"

#include <bits/stdc++.h>
#include "../communication/message.hpp"

#include "../communication/comms.hpp"
#include "../entities/FlightServant.hpp"
#include "../entities/BookingServant.hpp"
#include "../entities/TripServant.hpp"
#include "../entities/CallbackServant.hpp"

#include "../marshall/SerializablePOD.hpp"

void Proxy::handleFlightQuery(std::string ip, int request_id, std::string flight_id)
{
    int request_type = 0;
    char *client_ip = string_to_array(ip);

    // Marshall request contents
    size_t content_size = sizeof(int) + sizeof(size_t) + flight_id.size(); // Service type, type of length, length of string

    char *content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 2;

    SerializablePOD<int>::serialize(content_buffer, service_type);

    SerializablePOD<char *>::serialize(content_buffer, string_to_array(flight_id));

    content_buffer -= content_size; // Bring back pointer to start address

    CommunicationMessage comm_message(request_type, request_id, client_ip, content_buffer, content_size);
    char *message_buffer = comm_message.serialize();

    Communication::send(message_buffer, comm_message.serialization_size() + 1);

    char *message;
    int n = Communication::receive(message);
    
    double probability = ((double) rand() / (RAND_MAX));  // Probability to drop reply for simulation purposes
    
    // Retrasmit request if no reply received
    while (n == -1 || probability < 0.1)
    {
        std::cout << "Timeout : Did not receive anything from server... Retransmitting Message\n";
        Communication::send(message_buffer, comm_message.serialization_size() + 1);
        n = Communication::receive(message);
        probability = ((double)rand() / (RAND_MAX));
    }
    
    // Unmarshall reply
 
    short status;
    SerializablePOD<short>::deserialize(message, status);

    long reply_size;
    SerializablePOD<long>::deserialize(message, reply_size);

    if (status == 1)
    {
        char *error_message;
        SerializablePOD<char *>::deserialize(message, error_message);
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

// Proxy handler for querying flight locations
void Proxy::handleLocationQuery(std::string ip, int request_id, std::string source, std::string destination)
{
    int request_type = 0;
    char *client_ip = string_to_array(ip);

    // Marshall request contents

    // Service type, type of length * 2, length of source, length of destination
    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + source.size() + destination.size();

    char *content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 1;

    SerializablePOD<int>::serialize(content_buffer, service_type);
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(source));
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(destination));

    content_buffer -= content_size; // Bring pointer back to start address

    CommunicationMessage comm_message(request_type, request_id, client_ip, content_buffer, content_size);
    char *message_buffer = comm_message.serialize();

    Communication::send(message_buffer, comm_message.serialization_size() + 1);

    char* message;
    int n = Communication::receive(message);

    double probability = ((double) rand() / (RAND_MAX));
    
    // Retrasmit request if no reply received
    while (n == -1 || probability < 0.1)
    {
        std::cout << "Timeout : Did not receive anything from server... Retransmitting Message\n";
        Communication::send(message_buffer, comm_message.serialization_size() + 1);
        n = Communication::receive(message);
        probability = ((double) rand() / (RAND_MAX));
    }
    
    // Unmarshall reply
    short status;
    SerializablePOD<short>::deserialize(message, status);

    long reply_size;
    SerializablePOD<long>::deserialize(message, reply_size);

    if (status == 1)
    {
        char *error_message;
        SerializablePOD<char *>::deserialize(message, error_message);
        std::cout << error_message << '\n';
        return;
    }

    else
    {
        int num_flights;
        SerializablePOD<int>::deserialize(message, num_flights);

        std::cout << "Num Flights: " << num_flights << '\n';

        for (int i = 0; i < num_flights; ++i)
        {
            char *flight_id;
            SerializablePOD<char *>::deserialize(message, flight_id);
            std::cout << flight_id << '\n';
        }
        std::cout << '\n';
    }
}

// Proxy handler to handle trip planning
void Proxy::handlePlanTrip(std::string ip, int request_id, std::string source, std::string destination)
{

    int request_type = 0;
    char *client_ip = string_to_array(ip);

    // Marshall request contents

    // Service type, type of length * 2, length of source, length of destination
    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + source.size() + destination.size();

    char *content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 7;

    SerializablePOD<int>::serialize(content_buffer, service_type);
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(source));
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(destination));

    content_buffer -= content_size; // Bring pointer back to start address

    CommunicationMessage comm_message(request_type, request_id, client_ip, content_buffer, content_size);
    char *message_buffer = comm_message.serialize();

    Communication::send(message_buffer, comm_message.serialization_size() + 1);

    char* message;
    int n = Communication::receive(message);

    double probability = ((double) rand() / (RAND_MAX));
    
    // Retrasmit request if no reply received
    while (n == -1 || probability < 0.1)
    {
        std::cout << "Timeout : Did not receive anything from server... Retransmitting Message\n";
        Communication::send(message_buffer, comm_message.serialization_size() + 1);
        n = Communication::receive(message);
        probability = ((double) rand() / (RAND_MAX));
    }
    
    // Unmarshall reply

    short status;
    SerializablePOD<short>::deserialize(message, status);

    long reply_size;
    SerializablePOD<long>::deserialize(message, reply_size);

    if (status == 1)
    {
        char *error_message;
        SerializablePOD<char *>::deserialize(message, error_message);
        std::cout << error_message << '\n';
        return;
    }

    else
    {
        int num_trips;
        SerializablePOD<int>::deserialize(message, num_trips);

        std::cout << "Num Trips: " << num_trips << '\n';

        for (int t = 0; t < num_trips; ++t)
        {
            TripServant ts;
            ts.deserialize(message);
            ts.display();
            std::cout << '\n';
        }
    }
}

// Proxy handler to reserve seats in a flight
void Proxy::handleReservation(std::string ip, int request_id, std::string flight_id, std::string customer_name, int num_seats)
{
    int request_type = 0;
    char *client_ip = string_to_array(ip);

    // Marshall request contents

    // Service type, 2 * type of length, length of flight_id, length of customer_name, num_seats
    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + flight_id.size() + customer_name.size() + sizeof(num_seats);

    char *content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 3;

    SerializablePOD<int>::serialize(content_buffer, service_type);

    SerializablePOD<char *>::serialize(content_buffer, string_to_array(flight_id));
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(customer_name));
    SerializablePOD<int>::serialize(content_buffer, num_seats);

    content_buffer -= content_size; // Bring pointer back to start address

    CommunicationMessage comm_message(request_type, request_id, client_ip, content_buffer, content_size);
    char *message_buffer = comm_message.serialize();

    Communication::send(message_buffer, comm_message.serialization_size() + 1);

    char* message;
    int n = Communication::receive(message);

    double probability = ((double) rand() / (RAND_MAX));
    
    // Retrasmit request if no reply received
    while (n == -1 || probability < 0.1)
    {
        std::cout << "Timeout : Did not receive anything from server... Retransmitting Message\n";
        Communication::send(message_buffer, comm_message.serialization_size() + 1);
        n = Communication::receive(message);
        probability = ((double) rand() / (RAND_MAX));
    }

    // Unmarshall reply
    
    short status;
    SerializablePOD<short>::deserialize(message, status);

    long reply_size;
    SerializablePOD<long>::deserialize(message, reply_size);

    if (status == 1)
    {
        char *error_message;
        SerializablePOD<char *>::deserialize(message, error_message);
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


// Proxy handler to cancel reservation of seats
void Proxy::handleCancelReservation(std::string ip, int request_id, std::string booking_id)
{
    int request_type = 0;
    char *client_ip = string_to_array(ip);

    // Marshall request contents

    // Service type, type of length, length of booking_id
    size_t content_size = sizeof(int) + sizeof(size_t) + booking_id.size();

    char *content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 4;

    SerializablePOD<int>::serialize(content_buffer, service_type);

    SerializablePOD<char *>::serialize(content_buffer, string_to_array(booking_id));

    content_buffer -= content_size;

    CommunicationMessage comm_message(request_type, request_id, client_ip, content_buffer, content_size);
    char *message_buffer = comm_message.serialize();

    Communication::send(message_buffer, comm_message.serialization_size() + 1);

    char* message;
    int n = Communication::receive(message);

    double probability = ((double) rand() / (RAND_MAX));
    
    // Retrasmit request if no reply received
    while (n == -1 || probability < 0.1)
    {
        std::cout << "Timeout : Did not receive anything from server... Retransmitting Message\n";
        Communication::send(message_buffer, comm_message.serialization_size() + 1);
        n = Communication::receive(message);
        probability = ((double) rand() / (RAND_MAX));
    }
    
    // Unmarshall reply
    short status;
    SerializablePOD<short>::deserialize(message, status);

    long reply_size;
    SerializablePOD<long>::deserialize(message, reply_size);

    if (status == 1)
    {
        char *error_message;
        SerializablePOD<char *>::deserialize(message, error_message);
        std::cout << error_message << '\n';
        return;
    }
    else
    {
        char *confirmation_message;
        SerializablePOD<char *>::deserialize(message, confirmation_message);
        std::cout << confirmation_message << '\n';
        return;
    }
}

// Proxy handler to check if reservation exists
void Proxy::handleCheckReservation(std::string ip, int request_id, std::string booking_id)
{
    int request_type = 0;
    char *client_ip = string_to_array(ip);

    // Marshall request contents

    // Service type, type of length, length of booking_id
    size_t content_size = sizeof(int) + sizeof(size_t) + booking_id.size();

    char *content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';

    int service_type = 5;

    SerializablePOD<int>::serialize(content_buffer, service_type);

    SerializablePOD<char *>::serialize(content_buffer, string_to_array(booking_id));

    content_buffer -= content_size; // Bring pointer back to start address

    CommunicationMessage comm_message(request_type, request_id, client_ip, content_buffer, content_size);
    char *message_buffer = comm_message.serialize();

    Communication::send(message_buffer, comm_message.serialization_size() + 1);

    char* message;
    int n = Communication::receive(message);

    double probability = ((double) rand() / (RAND_MAX));
    
    // Retrasmit request if no reply received
    while (n == -1 || probability < 0.1)
    {
        std::cout << "Timeout : Did not receive anything from server... Retransmitting Message\n";
        Communication::send(message_buffer, comm_message.serialization_size() + 1);
        n = Communication::receive(message);
        probability = ((double) rand() / (RAND_MAX));
    }
    
    // Umarshall reply
    short status;
    SerializablePOD<short>::deserialize(message, status);

    long reply_size;
    SerializablePOD<long>::deserialize(message, reply_size);

    if (status == 1)
    {
        char *error_message;
        SerializablePOD<char *>::deserialize(message, error_message);
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

void Proxy::handleMonitor(std::string ip, int request_id, std::string flight_id, int monitoringDuration)
{
    int request_type = 0;
    char *client_ip = string_to_array(ip);

    // Service type, type of length, length of booking_id, monitoringDuration
    size_t content_size = sizeof(int) + sizeof(size_t) + flight_id.size() + sizeof(monitoringDuration);

    char *content_buffer = new char[content_size + 1];

    content_buffer[content_size] = '\0';
    int service_type = 6;

    SerializablePOD<int>::serialize(content_buffer, service_type);
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(flight_id));
    SerializablePOD<int>::serialize(content_buffer, monitoringDuration);

    content_buffer -= content_size;

    CommunicationMessage comm_message(request_type, request_id, client_ip, content_buffer, content_size);
    char *message_buffer = comm_message.serialize();

    Communication::send(message_buffer, comm_message.serialization_size() + 1);
    char *ACKmessage;
    int n = Communication::receive(ACKmessage);
    while (n == -1)
    {
        std::cout << "Timeout : Did not receive anything from server... Retransmitting Message\n";
        Communication::send(message_buffer, comm_message.serialization_size() + 1);
        n = Communication::receive(ACKmessage);
    }
    short status;
    SerializablePOD<short>::deserialize(ACKmessage, status);

    long reply_size;
    SerializablePOD<long>::deserialize(ACKmessage, reply_size);

    if (status == 1)
    {
        char *error_message;
        SerializablePOD<char *>::deserialize(ACKmessage, error_message);
        std::cout << error_message << '\n';
        return;
    }
    else
    {
        char* success_message;
        SerializablePOD<char*>::deserialize(ACKmessage, success_message);
    }

    // Timer starts only after subscription is ACK
    time_t startMonitoring, currTime;
    time(&startMonitoring);

    while (difftime(time(&currTime), startMonitoring) <= monitoringDuration)
    {
        char *message;
        int n = Communication::receive(message);
        if (n==-1) continue;

        short status;
        SerializablePOD<short>::deserialize(message, status);

        long reply_size;
        SerializablePOD<long>::deserialize(message, reply_size);

        if (status == 1)
        {
            char *error_message;
            SerializablePOD<char *>::deserialize(message, error_message);
            std::cout << error_message << '\n';
            return;
        }
        else
        {
            CallbackServant cs = CallbackServant();
            cs.deserialize(message);
            cs.displayUpdates();
            std::cout << '\n';
        }
    }
    if (difftime(time(&currTime), startMonitoring) > monitoringDuration)
    {
        std::cout << "Thank you for monitoring flights \n";
        return;
    }
}