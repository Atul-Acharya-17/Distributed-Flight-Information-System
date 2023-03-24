#include <string>

#ifndef CALLBACK_H
#define CALLBACK_H

class Callback : public Serializable
{
private:
    char *msg;

public:
    virtual void displayUpdates() = 0;
};

#endif