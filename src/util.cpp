#include "util.h"

std::tuple<int, int> read_varint(std::vector<char> message, int offset) {
    int value = 0;
    int position = 0;
    int cur_byte_offset = offset;
    char cur_byte;
    while (1) {
        cur_byte = message[cur_byte_offset];
        cur_byte_offset++;
        value |= (cur_byte & 0x7F) << position;

        if ((cur_byte & 0x80) == 0) break;

        position += 7;
    }
    return std::make_tuple(value, cur_byte_offset);
}

std::string get_string_from_vector(std::vector<char> message) {
    int string_length = 0;
    int offset = 0;
    std::tie(string_length, offset) = read_varint(message, offset);
    return std::string(message.begin() + offset, message.begin() + offset + string_length);
}