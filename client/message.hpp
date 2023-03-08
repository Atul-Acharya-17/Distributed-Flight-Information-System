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
    CommunicationMessage(int messageType, int requestId, char* clientId, char* contents, size_t content_size) {
        this->messageType = messageType;
        this->requestId = requestId;
        this->content_size = content_size;
        this->clientId = new char[strlen(clientId)];
        this->contents = new char[strlen(contents)];
        strcpy(this->clientId, clientId);
        strcpy(this->contents, contents);
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

        std::cout << size << '\n';

        char* dataOut = new char[size + 1];

        SerializablePOD<int>::serialize(dataOut, messageType, 0);
        SerializablePOD<int>::serialize(dataOut, requestId, sizeof(int));
        SerializablePOD<char*>::serialize(dataOut, clientId, 2 * sizeof(int));
        SerializablePOD<size_t>::serialize(dataOut, content_size, 2 * sizeof(int) + strlen(clientId) + sizeof(size_t));
        memcpy(dataOut + 2 * sizeof(int) + 2 * sizeof(size_t) + strlen(clientId), contents, content_size);

        dataOut[size] = '\0';
        
        return dataOut;

    }

    void deserialize(const char* dataIn)
    {
        // dataIn = SerializablePOD<int>::deserialize(dataIn, messageType);
        // dataIn = SerializablePOD<int>::deserialize(dataIn, requestId);
        // dataIn = SerializablePOD<char*>::deserialize(dataIn, clientId);
        // dataIn = SerializablePOD<char*>::deserialize(dataIn, contents);

        int message_type;;
        int request_id;
        char* ip;
        char* contents;

        SerializablePOD<int>::deserialize(dataIn, message_type, 0);
        std::cout << "Message Type: " << message_type << '\n';
        SerializablePOD<int>::deserialize(dataIn, request_id, sizeof(int));
        std::cout << "Request ID: " << request_id << '\n';
        SerializablePOD<char*>::deserialize(dataIn, ip, 2 * sizeof(int));
        SerializablePOD<char*>::deserialize(dataIn, contents, 2 * sizeof(int) + strlen(ip));

        this->messageType = message_type;
        this->requestId = request_id;
        this->clientId = ip;
        this->contents = contents;
    }

};

#endif