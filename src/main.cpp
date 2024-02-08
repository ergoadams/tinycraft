#include "server.h"
#include "util.h"

int main() {
    LOG("tinycraft starting!");
    tinycraftServer server;
    server.start_server();
    return 0;
}