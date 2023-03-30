### Running Client
Change to client directory:  
```bash
cd client
```

On Mac:  
```bash
g++ -std=c++17 -o client.o main.cpp constants.hpp marshall/* proxy/* communication/* entities/* client.hpp client.cpp
```

On Linux/Ubuntu/WSL:  
```bash
g++ -std=c++17 main.cpp constants.hpp marshall/* proxy/* communication/* entities/* client.hpp client.cpp -o client.o
```

To run the executable, enter server IP address and client IP address:  
```bash
./client.o <server_ip> <client_ip>
```

### Running Server
Change to server directory:  
```bash
cd server/
```

Compile Java file  
```bash
javac Main.java
```

Execute Main class  
```bash
java Main <server_type>
``` 

Options for server type:
* 0 = At least once server invocation semantics
* 1 = At most once server invocation semantics

### Running Experiments
Run the server as per instructions mentioned above. Remember to reset the flight data after calling `QueryFlight` to reset the number of available seats before the next iteration.

The client for the experiment can be executed using:
```bash
cd client

g++ -std=c++17 exp/*.cpp constants.hpp marshall/* proxy/* communication/* entities/* client.hpp client.cpp -o exp.o

./exp.o <server_ip> <client_ip> <probability>
```
