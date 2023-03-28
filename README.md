### Running Client

On Mac:  
`g++ -std=c++17 -o client.o main.cpp constants.hpp marshall/* proxy/* communication/* entities/* client.hpp client.cpp `

On Linux/Ubuntu/WSL:  
`g++ -std=c++17 main.cpp constants.hpp marshall/* proxy/* communication/* entities/* client.hpp client.cpp -o client.o`

To run the executable, enter server IP address and client IP address:  
`./client.o <server_ip> <client_ip>`

### Running Server
Compile Java file  
`javac Main.java`

Execute Main class  
`java Main <server_type>`  

Options for server type:
* 0 = At least once server invocation semantics
* 1 = At most once server invocation semantics

