#include <bits/stdc++.h>
#include <iostream>
#include "../entities/FlightServant.hpp"

#include "../marshall/SerializablePOD.hpp"
#include "../communication/comms.hpp"
#include "../communication/message.hpp"


void flight_info_query(std::string ip, double p=0.1)
{
    int iterations = 1000;

    std::string source = "Dubai";
    std::string destination = "Singapore";

    int request_type = 0;
    char *client_ip = string_to_array(ip);
    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + source.size() + destination.size();
    char *content_buffer = new char[content_size + 1];
    content_buffer[content_size] = '\0';
    int service_type = 1;
    SerializablePOD<int>::serialize(content_buffer, service_type);
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(source));
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(destination));
    content_buffer -= content_size; // Bring pointer back to start address
    CommunicationMessage comm_message(request_type, 1, client_ip, content_buffer, content_size);
    char *message_buffer = comm_message.serialize();

    double tot = 0;

    for (int i=0; i < iterations; ++i)
    {

        int num_calls = 0;
        Communication::send(message_buffer, comm_message.serialization_size() + 1);

        char* message;
        int n = Communication::receive(message);

        ++num_calls;

        double probability = ((double) rand() / (RAND_MAX));
        
        // Retrasmit request if no reply received
        while (n == -1 || probability < p)
        {
            //std::cout << "Timeout : Did not receive anything from server... Retransmitting Message\n";
            Communication::send(message_buffer, comm_message.serialization_size() + 1);
            n = Communication::receive(message);
            probability = ((double) rand() / (RAND_MAX));
            ++num_calls;
        }

        tot += num_calls;
    }

    std::cout << "Function Calls = " << tot / iterations << '\n';
}


// Server automatically resets the original data to redo the experiment for next iteration
void book_seats(std::string ip, double p=0.1)
{
    int iterations = 1000;

    char *client_ip = string_to_array(ip);

    std::string flight_id = "EK66";
    std::string customer_name = "Andrew Tate\n";
    int num_seats = 1;

    size_t content_size = sizeof(int) + 2 * sizeof(size_t) + flight_id.size() + customer_name.size() + sizeof(num_seats);
    char *content_buffer = new char[content_size + 1];
    content_buffer[content_size] = '\0';
    int service_type = 3;
    SerializablePOD<int>::serialize(content_buffer, service_type);
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(flight_id));
    SerializablePOD<char *>::serialize(content_buffer, string_to_array(customer_name));
    SerializablePOD<int>::serialize(content_buffer, num_seats);
    content_buffer -= content_size; // Bring pointer back to start address

    CommunicationMessage comm_message(0, 1, client_ip, content_buffer, content_size);
    char *message_buffer = comm_message.serialize();

    double tot = 0;

    double seats = 0;


    // Server automatically resets the original data to redo the experiment for next iteration
    for (int i=0; i < iterations; ++i)
    {

        int num_calls = 0;
        Communication::send(message_buffer, comm_message.serialization_size() + 1);

        char* message;
        int n = Communication::receive(message);

        ++num_calls;

        double probability = ((double) rand() / (RAND_MAX));
        
        // Retrasmit request if no reply received
        while (n == -1 || probability < p)
        {
            //std::cout << "Timeout : Did not receive anything from server... Retransmitting Message\n";
            Communication::send(message_buffer, comm_message.serialization_size() + 1);
            n = Communication::receive(message);
            probability = ((double) rand() / (RAND_MAX));
            ++num_calls;
        }

        // Marshall request contents
        size_t content_size = sizeof(int) + sizeof(size_t) + flight_id.size(); // Service type, type of length, length of string
        char *content_buffer = new char[content_size + 1];
        content_buffer[content_size] = '\0';
        int service_type = 2;
        SerializablePOD<int>::serialize(content_buffer, service_type);
        SerializablePOD<char *>::serialize(content_buffer, string_to_array(flight_id));
        content_buffer -= content_size; // Bring back pointer to start address
        CommunicationMessage comm_message(0, 2, client_ip, content_buffer, content_size);
        char *message_buffer = comm_message.serialize();
        Communication::send(message_buffer, comm_message.serialization_size() + 1);

        n = Communication::receive(message);
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
            seats += fs.getSeatsAvailable();
        }

        tot += num_calls;
    }


    std::cout << "Function Calls = " << tot / iterations << '\n';
    std::cout << "Num seats available = " << seats / iterations << '\n';
}
int main(int argc, char **argv)
{

    char *server_ip = argv[1];
    char *client_ip = argv[2];

    double p = std::stod(argv[3]);

    std::cout << "Probability: " << p << '\n';

    Communication::setup(server_ip);

    flight_info_query(client_ip, p);
    book_seats(client_ip, p);

    return 0;
}