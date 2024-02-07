#include "server.h"
#include "protocol.h"
#include "util.h"

void handle_client(int server_fd, int client_socket, connection_state &conn_state) {
    // Client -> server messages
    LOG("In client thread");
    char buffer[1024] = {0};
    ssize_t valread;
    while (1) {
        memset(&buffer, 0, sizeof(buffer));
        valread = recv(client_socket, (char*)&buffer, sizeof(buffer), 0);
        if (valread > 0) {
            send(server_fd, buffer, valread, 0);
            handle_serverbound(buffer, valread, conn_state);
        }
    }
}

void handle_server(int server_fd, int client_socket, connection_state &conn_state) {
    // Server -> client messages
    LOG("In server thread");
    char buffer[4096] = {0};
    ssize_t valread;
    while (1) {
        memset(&buffer, 0, sizeof(buffer));
        valread = recv(server_fd, (char*)&buffer, sizeof(buffer), 0);
        if (valread > 0) {
            send(client_socket, buffer, valread, 0);
            handle_clientbound(buffer, valread, conn_state);
        }
    }
}

void start_server() {
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

    // Create actual server connection
    std::string server_hostname = "192.168.137.1"; // Or IP
    uint16_t server_port = 25565;

    int server_fd, status;
    struct sockaddr_in serv_addr;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_hostname.c_str(), &serv_addr.sin_addr) <= 0) {
        perror("Invalid hostname");
        exit(EXIT_FAILURE);
    }

    if ((status = connect(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    connection_state conn_state = Handshaking;

    LOG("Starting server thread");
    std::thread server_thread(handle_server, server_fd, client_socket, std::ref(conn_state));
    LOG("Starting client thread");
    std::thread client_thread(handle_client, server_fd, client_socket, std::ref(conn_state));

    server_thread.join();
    client_thread.join();

    close(server_fd);
    close(client_socket);
    close(client_fd);
}