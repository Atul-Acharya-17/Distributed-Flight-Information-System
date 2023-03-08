#include "marshall/Serializable.hpp"
#include "marshall/SerializablePOD.hpp"
# include<string>

class CommunicationMessage : public Serializable  {
    private:
        int messageType;
        int requestId;
        char* clientId;
        char* contents;

    public:
    CommunicationMessage(int messageType, int requestId, char* clientId, char* contents) {
        this->messageType = messageType;
        this->requestId = requestId;
        strcpy(this->clientId, clientId);
        strcpy(this->contents, contents);
    }

    size_t serialize_size() const
    {
        return SerializablePOD<int>::serialize_size(messageType) +
               SerializablePOD<int>::serialize_size(requestId) +
               SerializablePOD<char*>::serialize_size(clientId) +
               SerializablePOD<char*>::serialize_size(contents);
    }

    void serialize(char* dataOut) const
    {
        dataOut = SerializablePOD<int>::serialize(dataOut, messageType);
        dataOut = SerializablePOD<int>::serialize(dataOut, requestId);
        dataOut = SerializablePOD<char*>::serialize(dataOut, clientId);
        dataOut = SerializablePOD<char*>::serialize(dataOut, contents);
    }
    void deserialize(const char* dataIn)
    {
        dataIn = SerializablePOD<int>::deserialize(dataIn, messageType);
        dataIn = SerializablePOD<int>::deserialize(dataIn, requestId);
        dataIn = SerializablePOD<char*>::deserialize(dataIn, clientId);
        dataIn = SerializablePOD<char*>::deserialize(dataIn, contents);
    }

};