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
int main(int argc, char** argv) {
	
    char* server_ip = argv[1];
    char* client_ip = argv[2];

    Communication::setup(server_ip);

	uint32_t choice;
    Client c = Client(std::string(client_ip));

    try{
        while (true)
        {	
            std::cout << "Enter Functionality\n";

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
                c.queryLocation();
            }
            if (choice==2) {
                c.queryFlight();
            }

            switch(choice)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                default: break;
            }

            // Communication::send((const char *)functionalities[choice]);
            // std::cout<<"Hello message sent."<<std::endl;
                
            // char* reply = Communication::receive();
            // std::cout<<"Server : "<<reply<<std::endl;
        }

    }

    catch(const std::exception &exec)
    {
        std::cerr << "Exception " << exec.what();
    }

    Communication::terminate();
	
    return 0;
}
