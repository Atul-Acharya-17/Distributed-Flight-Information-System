### Running Client

For now type

g++ main.cpp constants.hpp marshall/* proxy/* communication/* client.hpp client.cpp -o client.o

./client.o

There is a dummy server to test the client

g++ server.cpp marshall/* -o server.o
./server.o