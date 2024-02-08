#pragma once
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "util.h"
#include <thread>
#include <arpa/inet.h>

class serverState {
    public:
        connection_state conn_state;
};


class tinycraftServer {
    public:
        void start_server();

    private:
        static void server_handler(int client_fd, serverState &server_state);
};

