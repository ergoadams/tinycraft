#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "util.h"
#include <thread>
#include <arpa/inet.h>

void handle_client(int server_fd, int client_fd);
void handle_server(int server_fd, int client_fd);
void start_server();