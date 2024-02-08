#include "server.h"
#include "protocol.h"
#include "util.h"

void tinycraftServer::server_handler(int client_socket, serverState &server_state) {
    // Handles a client connection
    LOG("In server thread");
    char buffer[4096] = {0};
    char response[4096] = {0};
    int response_length = 0;
    ssize_t valread;
    while (1) {
        memset(&buffer, 0, sizeof(buffer));
        memset(&response, 0, sizeof(response));
        response_length = 0;
        valread = recv(client_socket, (char*)&buffer, sizeof(buffer), 0);
        if (valread > 0) {
            handle_message(buffer, valread, server_state, response, &response_length);
            if (response_length > 0) {
                send(client_socket, response, response_length, 0);

                std::vector<char> response_msg(response, response + response_length);
                printf("server -> client:");
                for (auto c: response_msg) {
                    printf(" %02x", c);
                }
                printf("\n");
            }
        }
    }
}

void tinycraftServer::start_server() {
    // Wait for a client to connect
    uint16_t client_port = 55555;
    int client_fd, client_socket;
    struct sockaddr_in client_address;
    int client_opt = -1;
    socklen_t client_addrlen = sizeof(client_address);

    // Creating socket descriptor
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach socket to port
    if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &client_opt, sizeof(client_opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = INADDR_ANY;
    client_address.sin_port = htons(client_port);
    if (bind(client_fd, (struct sockaddr*)&client_address, sizeof(client_address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    LOG("Socket created.");
    // Start listening on port
    if (listen(client_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    LOG("Listened");
    if ((client_socket = accept(client_fd, (struct sockaddr*)&client_address, &client_addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    LOG("Got client connection.");

    serverState server_state;
    server_state.conn_state = Handshaking;

    LOG("Starting client thread");
    std::thread server_thread(tinycraftServer::server_handler, client_socket, std::ref(server_state));

    server_thread.join();

    close(client_socket);
    close(client_fd);
}