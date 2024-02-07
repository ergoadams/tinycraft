#pragma once
#include <iostream>
#include <vector>
#include <tuple>

#define LOG(msg) std::cout << msg << std::endl

enum connection_state : int {
    Handshaking = 0,
    Status = 1,
    Login = 2,
    Configuration = 3
};

std::tuple<int, int> read_varint(std::vector<char> message, int offset);
std::string get_string_from_vector(std::vector<char> message);