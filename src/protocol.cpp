#include "protocol.h"

/*void parse_message(std::vector<char> message, bool serverbound, serverState &server_state) {
    int cur_message_offset = 0;
    int message_length = 0;
    int packet_id = 0;
    
    bool more_to_process = true;
    while (more_to_process) {
        std::tie(message_length, cur_message_offset) = read_varint(message, cur_message_offset);
        std::tie(packet_id, cur_message_offset) = read_varint(message, cur_message_offset);
        std::vector<char> cur_message(message.begin() + cur_message_offset, message.begin() + cur_message_offset + message_length);
        if (serverbound) {
            // Client -> server messages
            switch (conn_state) {
                case Handshaking:
                    switch (packet_id) {
                        case 0x00:
                            msg_handshake(cur_message, conn_state);
                            break;
                        default:
                            LOG("Unknown serverbound handshaking packet");
                            LOG(packet_id); 
                            break;
                    }
                    break;
                case Login:
                    switch (packet_id) {
                        case 0x00:
                            msg_login_start(cur_message);
                            break;
                         case 0x03:
                            msg_login_acknowledged(conn_state);
                            break;
                        default:
                            LOG("Unknown serverbound login packet");
                            LOG(packet_id); 
                            break;
                    }
                    break;
                case Configuration:
                    switch (packet_id) {
                        case 0x00:
                            msg_client_information(cur_message);
                            break;
                        case 0x01:
                            msg_serverbound_plugin_message(cur_message);
                            break;
                        default:
                            LOG("Unknown serverbound configuration packet");
                            LOG(packet_id); 
                            break;
                    }
                    break;
                default: 
                    LOG("Unhandled serverbound conn_state"); 
                    LOG(conn_state);
                    break;
            }
        } else {
            // Clientbound
            switch (conn_state) {
                case Login:
                    switch (packet_id) {
                        case 0x02:
                            msg_login_success(cur_message);
                            break;
                        default:
                            LOG("Unknown clientbound login packet");
                            LOG(packet_id); 
                            break;
                    }
                    break;
                case Configuration:
                    switch (packet_id) {
                        case 0x00:
                            msg_clientbound_plugin_message(cur_message);
                            break;
                        default:
                            LOG("Unknown clientbound configuration packet");
                            LOG(packet_id); 
                            break;
                    }
                    break;
                default:
                    LOG("Unhandled clientbound conn_state");
                    LOG(conn_state);
                    break;
            }
        }

        // In case of multiple packets in one vector, check if any messages remain
        if ((cur_message_offset + message_length) >= message.size()) {
            more_to_process = false;
        }
        cur_message_offset += message_length - 1;
    }
}*/

void handle_message(char* buffer, int bytes_read, serverState &server_state, char* response, int* response_length) {
    std::vector<char> message(buffer, buffer + bytes_read);
    printf("client -> server:");
    for (auto c: message) {
        printf(" %02x", c);
    }
    printf("\n");
    *response_length = 0;
    //parse_message(message, false, conn_state);
}