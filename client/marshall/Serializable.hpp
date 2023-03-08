#include <stddef.h>

class Serializable
{
public:
    virtual size_t serialize_size() const = 0;
    virtual char* serialize() const = 0;
    virtual void deserialize(const char* dataIn) = 0;
};