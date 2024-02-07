
.PHONY: tinycraft
tinycraft:
	g++ -std=c++17 -o tinycraft src/main.cpp src/server.cpp src/protocol.cpp src/util.cpp src/msg_handshaking.cpp src/msg_login.cpp src/msg_configuration.cpp -pthread