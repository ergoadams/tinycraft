#include <cstdio>
#include <vector>
#include <tuple>
#include "util.h"
#include "msg_handshaking.h"
#include "msg_login.h"
#include "msg_configuration.h"


void handle_serverbound(char* buffer, int bytes_read, connection_state &conn_state);
void handle_clientbound(char* buffer, int bytes_read, connection_state &conn_state);
void parse_message(std::vector<char> message, bool serverbound, connection_state &conn_state);