#ifndef MESSAGE_H
#define MESSAGE_H

#include "../marshall/Serialization.hpp"
#include "../marshall/SerializePOD.hpp"
#include <string>
#include <iostream>

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

    size_t serialization_size() const
    {
        return SerializePOD<int>::serialization_size(messageType) +
               SerializePOD<int>::serialization_size(requestId) +
               SerializePOD<char*>::serialization_size(clientId) +
               this->content_size + sizeof(size_t);
    }

    char* serialize() const
    {
        int size = serialization_size();

        // Initialize output buffer for serialized string

        char* dataOut = new char[size + 1];
        dataOut[size] = '\0';

        SerializePOD<int>::serialize(dataOut, messageType);
        SerializePOD<int>::serialize(dataOut, requestId);
        SerializePOD<char*>::serialize(dataOut, clientId);
        SerializePOD<size_t>::serialize(dataOut, content_size);
        
        memcpy(dataOut, contents, content_size);
        
        // Reset pointer to start of serialized string and return
        dataOut += content_size;
        dataOut -= size;
        return dataOut;

    }

    void deserialize(char* &dataIn)
    {
        int message_type;;
        int request_id;
        char* ip;
        char* contents;

        SerializePOD<int>::deserialize(dataIn, message_type);
        SerializePOD<int>::deserialize(dataIn, request_id);
        SerializePOD<char*>::deserialize(dataIn, ip);
        SerializePOD<char*>::deserialize(dataIn, contents);

        this->messageType = message_type;
        this->requestId = request_id;
        this->clientId = ip;
        this->contents = contents;

        int service_id;
	    char* location;

        SerializePOD<int>::deserialize(contents, service_id);
        SerializePOD<char*>::deserialize(contents, location);       
    }

};

#endif