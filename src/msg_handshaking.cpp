#include "msg_handshaking.h"

void msg_handshake(std::vector<char> message, connection_state &conn_state) {
    int cur_message_offset = 0;
    int protocol_version = 0;
    std::tie(protocol_version, cur_message_offset) = read_varint(message, cur_message_offset);

    std::string server_address = get_string_from_vector(std::vector<char>(message.begin() + cur_message_offset, message.end()));
    cur_message_offset += server_address.length() + 1;

    uint16_t server_port = ((uint16_t)message[cur_message_offset] << 8) | message[cur_message_offset + 1];
    cur_message_offset += 2;
    int next_state_val = 0;
    std::tie(next_state_val, cur_message_offset) = read_varint(message, cur_message_offset);
    connection_state next_state{next_state_val};
    conn_state = next_state;

    LOG("Handshake");
    LOG(protocol_version);
    LOG(server_address);
    LOG(server_port);
    LOG(next_state);
    LOG("");
}