#ifndef MESSAGE_H
#define MESSAGE_H

#include "marshall/Serializable.hpp"
#include "marshall/SerializablePOD.hpp"
#include <string>

class CommunicationMessage : public Serializable  {
    private:
        int messageType;
        int requestId;
        char* clientId;
        char* contents;
        size_t content_size;

    public:
    CommunicationMessage(){}
    
    CommunicationMessage(int messageType, int requestId, char* clientId, char* contents, size_t content_size) {
        this->messageType = messageType;
        this->requestId = requestId;
        this->content_size = content_size;
        this->clientId = clientId;
        this->contents = contents;
    }

    size_t serialize_size() const
    {
        return SerializablePOD<int>::serialize_size(messageType) +
               SerializablePOD<int>::serialize_size(requestId) +
               SerializablePOD<char*>::serialize_size(clientId) +
               this->content_size + sizeof(size_t);
    }

    char* serialize() const
    {
        int size = serialize_size();

        char* dataOut = new char[size + 1];
        dataOut[size] = '\0';

        SerializablePOD<int>::serialize(dataOut, messageType);
        SerializablePOD<int>::serialize(dataOut, requestId);
        SerializablePOD<char*>::serialize(dataOut, clientId);
        SerializablePOD<size_t>::serialize(dataOut, content_size);
        
        memcpy(dataOut, contents, content_size);
        dataOut += content_size;
        
        dataOut -= size;

        return dataOut;

    }

    void deserialize(char* dataIn)
    {
        // dataIn = SerializablePOD<int>::deserialize(dataIn, messageType);
        // dataIn = SerializablePOD<int>::deserialize(dataIn, requestId);
        // dataIn = SerializablePOD<char*>::deserialize(dataIn, clientId);
        // dataIn = SerializablePOD<char*>::deserialize(dataIn, contents);

        int message_type;;
        int request_id;
        char* ip;
        char* contents;

        SerializablePOD<int>::deserialize(dataIn, message_type);
        std::cout << "Message Type: " << message_type << '\n';
        SerializablePOD<int>::deserialize(dataIn, request_id);
        std::cout << "Request ID: " << request_id << '\n';
        SerializablePOD<char*>::deserialize(dataIn, ip);
        std::cout << "IP: " << ip <<'\n';
        SerializablePOD<char*>::deserialize(dataIn, contents);

        this->messageType = message_type;
        this->requestId = request_id;
        this->clientId = ip;
        this->contents = contents;

        int service_id;
	    char* location;

        SerializablePOD<int>::deserialize(contents, service_id);
        std::cout << "Service ID: " << service_id <<'\n';
        SerializablePOD<char*>::deserialize(contents, location);

        std::cout <<"Location: " << location << '\n';        
    }

};

#endif