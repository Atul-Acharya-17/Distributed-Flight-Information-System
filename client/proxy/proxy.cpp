#include "proxy.hpp"
#include <iostream>

#include "../marshall/marshall.hpp"
#include "../marshall/unmarshall.hpp"

#include <bits/stdc++.h>


void Proxy::handleFlightQuery(std::string ip, uint32_t message_id, std::string flight_id)
{
    char* message_type_buff = marshall_int(0);
    char* client_ip_size = marshall_int(ip.size());
    char* client_ip = marshall_string(ip);
    char* message_id_buff = marshall_int(message_id);
    char* flight_id_buff = marshall_string(flight_id);
    char* service_id_buff = marshall_int(1);
    char* flight_id_size_buff = marshall_int(flight_id.size());

    char* byte_string = new char[sizeof(uint32_t) * 5 + ip.size() + flight_id.size() + 1];

    uint32_t size = 0;

    memcpy(byte_string, message_type_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, client_ip_size, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, client_ip, ip.size());
    size += ip.size();

    memcpy(byte_string + size, service_id_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, flight_id_size_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, flight_id_buff, flight_id.size());
    size += flight_id.size();

    byte_string[size] = '\0';

    uint32_t mt = unmarshall_int(byte_string, 0);
    uint32_t ip_size = unmarshall_int(byte_string, sizeof(uint32_t));
    std::string i = unmarshall_string(byte_string, 2*sizeof(uint32_t), 2*sizeof(uint32_t) + ip_size);

    std::cout << mt << " " << i << '\n';

}


void Proxy::handleLocationQuery(std::string ip, uint32_t message_id, std::string source, std::string destination)
{
    char* message_type_buff = marshall_int(0);
    char* client_ip_size = marshall_int(ip.size());
    char* client_ip = marshall_string(ip);
    char* message_id_buff = marshall_int(message_id);
    char* service_id_buff = marshall_int(2);
    
    char* source_size_buff = marshall_int(source.size());
    char* destination_size_buff = marshall_int(destination.size());

    char* src = marshall_string(source);
    char* dest = marshall_string(destination); 

    char* byte_string = new char[sizeof(uint32_t) * 5 + ip.size() + source.size() + destination.size() + 1];


    uint32_t size = 0;

    memcpy(byte_string, message_type_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, client_ip_size, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, client_ip, ip.size());
    size += ip.size();

    memcpy(byte_string + size, service_id_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, source_size_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, src, source.size());
    size += source.size();

    memcpy(byte_string + size, destination_size_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, dest, destination.size());
    size += destination.size();

    byte_string[size] = '\0';

    size = 0;
    uint32_t mt = unmarshall_int(byte_string, size);
    size += sizeof(uint32_t);

    uint32_t cips = unmarshall_int(byte_string, size);
    size += sizeof(uint32_t);

    std::string i = unmarshall_string(byte_string, size, size + cips);
    size += cips;

    uint32_t sid = unmarshall_int(byte_string, size);
    size += sizeof(uint32_t);

    uint32_t s_size = unmarshall_int(byte_string, size);
    size += sizeof(uint32_t);

    std::string s = unmarshall_string(byte_string, size, size + s_size);
    size += s_size;

    uint32_t d_size = unmarshall_int(byte_string, size);
    size += sizeof(uint32_t);

    std::string d = unmarshall_string(byte_string, size, size + d_size);

    std::cout << i << " " << s << " " <<d << '\n';

}


void Proxy::handleReservation(std::string ip, uint32_t message_id, std::string flight_id, uint32_t num_seats)
{
    char* message_type_buff = marshall_int(0);
    char* client_ip_size = marshall_int(ip.size());
    char* client_ip = marshall_string(ip);
    char* message_id_buff = marshall_int(message_id);
    char* service_id_buff = marshall_int(1);
    char* flight_id_buff = marshall_string(flight_id);
    char* flight_id_size_buff = marshall_int(flight_id.size());
    char* num_seats_buff = marshall_int(num_seats);

    char* byte_string = new char[sizeof(uint32_t) * 6 + ip.size() + flight_id.size() + 1];
    
    uint32_t size = 0;

    memcpy(byte_string, message_type_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, client_ip_size, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, client_ip, ip.size());
    size += ip.size();

    memcpy(byte_string + size, service_id_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, flight_id_size_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    memcpy(byte_string + size, flight_id_buff, flight_id.size());
    size += flight_id.size();

    memcpy(byte_string + size, num_seats_buff, sizeof(uint32_t));
    size += sizeof(uint32_t);

    byte_string[size] = '\0';
}