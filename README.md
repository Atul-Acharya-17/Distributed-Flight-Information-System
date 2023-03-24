### Running Client

For now type

g++ -std = c++17 -o client.o main.cpp constants.hpp marshall/* proxy/* communication/* entities/* client.hpp client.cpp 

./client.o serverip clientip

There is a dummy server to test the client

g++ server.cpp marshall/* -o server.o
./server.o