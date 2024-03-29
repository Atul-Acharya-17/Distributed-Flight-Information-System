// Client side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

#include <cassert>

#include "constants.hpp"
#include "proxy/proxy.hpp"

#include "communication/comms.hpp"
#include "client.hpp"

// Driver code
int main(int argc, char **argv)
{

    char *server_ip = argv[1];
    char *client_ip = argv[2];

    unsigned int i = 1;
    char *c = (char*)&i;
    if (*c)
        std::cout<<"Little endian\n";
    else
        std::cout<<"Big endian\n";

    Communication::setup(server_ip);

	uint32_t choice;
    Client client = Client(std::string(client_ip));

    try
    {
        while (true)
        {
            std::cout << "\nEnter Functionality\n";

            for (auto it = functionalities.begin(); it != functionalities.end(); ++it)
            {
                std::cout << it->first << ". " << it->second << '\n';
            }

            std::cin >> choice;

            if (functionalities.find(choice) == functionalities.end())
            {
                std::cerr << "Invalid Functionality Chosen\n\n";
                continue;
            }

            if (choice == 0)
            {
                std::cout << "Program Terminating\n";
                break;
            }

            if (choice == 1)
            {
                client.queryLocation();
            }
            if (choice == 2)
            {
                client.queryFlight();
            }
            if (choice == 3)
            {
                client.reserveSeats();
            }
            if (choice == 4)
            {
                client.cancelBooking();
            }
            if (choice == 5)
            {
                client.checkBooking();
            }
            if (choice == 6)
            {
                client.monitorUpdates();
            }
            if (choice == 7)
            {
                client.planTrip();
            }
        }
    }

    catch (const std::exception &exec)
    {
        std::cerr << "Exception " << exec.what();
    }

    Communication::terminate();

    return 0;
}
