#ifndef UTILS_H
#define UTILS_H

#include <string>

inline char* string_to_array(std::string s)
{
    char* buffer = new char[s.size() + 1];

    for (int i=0; i<s.size(); ++i)
    {
        *(buffer + i) = s[i];
    }
    buffer[s.size()] = '\0';

    return buffer;
}

struct Time
{
    int hours;
    int minutes;
    int seconds;


    Time()
    {
        this->hours = 0;
        this->minutes = 0;
        this->seconds = 0;
    }

    Time(int hours, int minutes, int seconds)
    {
        this->hours = hours;
        this->minutes = minutes;
        this->seconds = seconds;      
    }

    Time(int seconds)
    {
        this->hours = seconds / 3600;
        seconds = seconds % 3600;
        this->minutes = seconds / 60;
        this->seconds = seconds % 60;
    }

    std::string to_string()
    {
        std::string h = this->hours >= 10? std::to_string(this->hours) : "0" + std::to_string(this->hours);
        std::string m = this->minutes >= 10? std::to_string(this->minutes) : "0" + std::to_string(this->minutes);
        std::string s = this->seconds >= 10? std::to_string(this->seconds) : "0" + std::to_string(this->seconds);

       return h + ":" + m + ":" + s ;
    }
};

#endif