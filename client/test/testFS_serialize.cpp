// Client side implementation of UDP client-server model
#include "entities/FlightServant.hpp"


// Driver code
int main() {
	
    FlightServant fs = FlightServant("EK352", "Dubai", "Singapore", 200, 83, 336.52);

    char* buffer = fs.serialize();

    FlightServant new_fs;
    new_fs.deserialize(buffer);

    new_fs.display();
	
    return 0;
}
