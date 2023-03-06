#ifndef MARSHALL_H
#define MARSHALL_H

#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>

unsigned char* marshall_int(uint32_t data) //unsigned char buffer[])
{
    uint32_t network_order = htonl(data); // convert to big-endian

    // for (int i=3; i>=0; --i)
    // {
    //     buffer[3-i] = ((network_order >>  i*8) & 0xFF);
    // }

    unsigned char *buffer = new unsigned char[4];
    
    for (int i=3; i>=0; --i)
    {
        *(buffer + 3- i) = (unsigned char)((network_order >>  i*8) & 0xFF);
    }

    return buffer;
}

unsigned char* marshall_string(std::string data)//, unsigned char buffer[])
{
    unsigned char *buffer = new unsigned char[data.size()];
    for (int i=0; i<data.size(); ++i)
    {
        *(buffer + i) = data[i];
    }

    return buffer;
}


#endif