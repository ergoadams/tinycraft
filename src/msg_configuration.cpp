#include "msg_configuration.h"

void msg_clientbound_plugin_message(std::vector<char> message) {
    int cur_message_offset = 0;
    std::string channel = get_string_from_vector(std::vector<char>(message.begin() + cur_message_offset, message.end()));
    cur_message_offset += channel.length() + 1;
    std::vector<char> data(message.begin() + cur_message_offset, message.end());
    LOG("Clientbound plugin message");
    LOG(channel);
    LOG("");
}

void msg_client_information(std::vector<char> message) {
    int cur_message_offset = 0;
    std::string locale = get_string_from_vector(std::vector<char>(message.begin() + cur_message_offset, message.end()));
    cur_message_offset += locale.length() + 1;
    int view_distance = message[cur_message_offset++];
    int chat_mode;
    std::tie(chat_mode, cur_message_offset) = read_varint(message, cur_message_offset);
    int chat_colors = message[cur_message_offset++];
    int displayed_skin_parts = message[cur_message_offset++];
    int main_hand;
    std::tie(main_hand, cur_message_offset) = read_varint(message, cur_message_offset);
    int enable_text_filtering = message[cur_message_offset++];
    int allow_server_listings = message[cur_message_offset++];

    LOG("Client information");
    LOG(locale);
    LOG(view_distance);
    LOG(chat_mode);
    LOG(chat_colors);
    LOG(displayed_skin_parts);
    LOG(main_hand);
    LOG(enable_text_filtering);
    LOG(allow_server_listings);
    LOG("");
}

void msg_serverbound_plugin_message(std::vector<char> message) {
    int cur_message_offset = 0;
    std::string channel = get_string_from_vector(std::vector<char>(message.begin() + cur_message_offset, message.end()));
    cur_message_offset += channel.length() + 1;
    std::vector<char> data(message.begin() + cur_message_offset, message.end());
    LOG("Serverbound plugin message");
    LOG(channel);
    LOG("");
}