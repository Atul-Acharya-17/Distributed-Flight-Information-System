#ifndef UNMARSHALL_H
#define UNMARSHALL_H

#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>

uint32_t unmarshall_int(unsigned char* byte_string, int start_idx) // 4 bytes = int
{

    uint32_t data = 0;

    for (int i=0; i<4; ++i)
    {
        data |= byte_string[start_idx + i] << (3-i)*8;
    }

    return ntohl(data);
}

std::string unmarshall_string(unsigned char* byte_string, int start_idx, int end_idx)
{
    std::string data;

    for (int i=start_idx; i<end_idx; ++i)
    {
        data.push_back(byte_string[i]);
    }

    return data;
}
#endif