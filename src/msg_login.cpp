#include "msg_login.h"

// Serverbound
void msg_login_start(std::vector<char> message) {
    int cur_message_offset = 0;
    std::string player_name = get_string_from_vector(std::vector<char>(message.begin() + cur_message_offset, message.end()));
    cur_message_offset += player_name.length() + 1;
    std::vector<char> player_uuid(message.begin() + cur_message_offset, message.begin() + cur_message_offset + 16);
    LOG("Login start");
    LOG(player_name);
    for (char i: player_uuid) std::cout << int(i) << ' ';
    LOG("");
    LOG("");
}


// Clientbound
void msg_login_acknowledged(connection_state &conn_state) {
    conn_state = Configuration;
    LOG("Login acknowledged");
    LOG("");
}

void msg_login_success(std::vector<char> message) {
    int cur_message_offset = 0;
    std::vector<char> player_uuid(message.begin() + cur_message_offset, message.begin() + cur_message_offset + 16);
    cur_message_offset += 16;
    std::string player_name = get_string_from_vector(std::vector<char>(message.begin() + cur_message_offset, message.end()));
    cur_message_offset += player_name.length() + 1;
    int num_of_properties;
    std::tie(num_of_properties, cur_message_offset) = read_varint(message, cur_message_offset);
    // Properties

    LOG("Login success");
    
    LOG("");
    
}