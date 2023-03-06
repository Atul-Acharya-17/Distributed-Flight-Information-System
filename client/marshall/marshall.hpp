#ifndef MARSHALL_H
#define MARSHALL_H

#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>

char* marshall_int(uint32_t data) //char buffer[])
{
    uint32_t network_order = htonl(data); // convert to big-endian

    // for (int i=3; i>=0; --i)
    // {
    //     buffer[3-i] = ((network_order >>  i*8) & 0xFF);
    // }

    char *buffer = new char[4];
    
    for (int i=3; i>=0; --i)
    {
        *(buffer + 3- i) = (char)((network_order >>  i*8) & 0xFF);
    }

    return buffer;
}

char* marshall_string(std::string data)//, char buffer[])
{
    char *buffer = new char[data.size()];
    for (int i=0; i<data.size(); ++i)
    {
        *(buffer + i) = data[i];
    }

    return buffer;
}


#endif