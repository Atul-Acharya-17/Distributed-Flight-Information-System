#ifndef UTILS_H
#define UTILS_H

#include <string>

char* string_to_array(std::string s)
{
    char* buffer = new char[s.size() + 1];

    for (int i=0; i<s.size(); ++i)
    {
        *(buffer + i) = s[i];
    }
    buffer[s.size()] = '\0';

    return buffer;
}

#endif