#include <cstdio>
#include <vector>
#include <tuple>
#include "util.h"
#include "msg_handshaking.h"
#include "msg_login.h"
#include "msg_configuration.h"
#include "server.h"


void handle_message(char* buffer, int bytes_read, serverState &server_state, char* response, int* response_length);
//void parse_message(std::vector<char> message, bool serverbound, serverState &server_state);