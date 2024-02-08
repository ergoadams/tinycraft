#include "util.h"

void msg_login_start(std::vector<char> message);
void msg_login_acknowledged(connection_state &conn_state);
void msg_login_success(std::vector<char> message);
