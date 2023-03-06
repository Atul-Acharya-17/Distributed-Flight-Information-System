#include "proxy.hpp"
#include <iostream>

#include "../marshall/marshall.hpp"
#include "../marshall/unmarshall.hpp"

#include <bits/stdc++.h>


void Proxy::handleInfoQuery(std::string flight_num)
{

    // unsigned char marshalled_string[sizeof(uint32_t) * 5 + flight_num.size() + 1];
    // marshalled_string[sizeof(uint32_t) * 5 + flight_num.size()] = '\0';

    // unsigned char message_type[sizeof(uint32_t)];
    // unsigned char client_id[sizeof(uint32_t)];
    // unsigned char message_id[sizeof(uint32_t)];
    // unsigned char flight_id[flight_num.size()];
    // unsigned char service_id[sizeof(uint32_t)];
    // unsigned char flight_num_size[sizeof(uint32_t)];

    // marshall_int(0, message_type);
    // marshall_int(1, client_id);
    // marshall_int(2, message_id);
    // marshall_int(5, service_id);
    // marshall_int((uint32_t) (flight_num.size()), flight_num_size);
    // marshall_string(flight_num, flight_id);

    // copy_string(marshalled_string, message_type, 0, sizeof(uint32_t));
    // copy_string(marshalled_string, client_id, sizeof(uint32_t), 2 * sizeof(uint32_t));
    // copy_string(marshalled_string, message_id, 2 * sizeof(uint32_t), 3 * sizeof(uint32_t));
    // copy_string(marshalled_string, service_id, 3 * sizeof(uint32_t), 4 * sizeof(uint32_t));
    // copy_string(marshalled_string, flight_num_size, 4 * sizeof(uint32_t), 5 * sizeof(uint32_t));
    // copy_string(marshalled_string, flight_id, 5 * sizeof(uint32_t), 5 * sizeof(uint32_t) + flight_num.size());

    unsigned char* message_type = marshall_int(0);
    unsigned char* client_id = marshall_int(1);
    unsigned char* message_id = marshall_int(4);
    unsigned char* flight_id = marshall_string(flight_num);
    unsigned char* service_id = marshall_int(2);
    unsigned char* flight_id_size = marshall_int(flight_num.size());

    unsigned char* byte_string = new unsigned char[sizeof(uint32_t) * 5 + flight_num.size() + 1];

    // Copy all strings in one
    // sprintf((char*)byte_string, "%s%s%s%s%s%s", message_type, client_id, message_id, service_id, flight_id_size, flight_id);
    memcpy(byte_string, message_type, sizeof(uint32_t));
    memcpy(byte_string + sizeof(uint32_t), client_id, sizeof(uint32_t));
    memcpy(byte_string + 2 * sizeof(uint32_t), message_id, sizeof(uint32_t));
    memcpy(byte_string + 3 * sizeof(uint32_t), service_id, sizeof(uint32_t));
    memcpy(byte_string + 4 * sizeof(uint32_t), flight_id_size, sizeof(uint32_t));
    memcpy(byte_string + 5 * sizeof(uint32_t), flight_id, flight_num.size());

    uint32_t mt = unmarshall_int(byte_string, 0);
    uint32_t cid = unmarshall_int(byte_string, sizeof(uint32_t));
    uint32_t mid = unmarshall_int(byte_string, 2 * sizeof(uint32_t));
    uint32_t sid = unmarshall_int(byte_string, 3 * sizeof(uint32_t));
    uint32_t fid_size = unmarshall_int(byte_string, 4 * sizeof(uint32_t));

    std::string fid = unmarshall_string(byte_string, 5 * sizeof(uint32_t), 5 * sizeof(uint32_t) + fid_size);

    std::cout << mt << " " << cid << " " << mid << " " << sid << " " << fid_size << " " << fid << '\n';

}