#pragma once

#include <NetworkStream.h>
#include <TcpStream.h>
#include <winsock.h>
#include <functional>

using namespace wpi;

namespace Networking {
void StartTCPNetwork() {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (!serverSocket) {
        perror("Unable to create a socket.");
    }

    if (!bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr_in))) {
        perror("Unable to bind the socket to an address.");
        closesocket(serverSocket);
    }

    //recvfrom()
}

// void ListenForMessage(uint16_t msgid, bool (*func)(char*)) {
void ListenForMessage(uint16_t msgid, std::function<bool()> func) {
    if (!func()) {
        printf("message failed to be read.");
    }
}

namespace {
u_short port;
sockaddr_in serverAddr;
}  // namespace

}  // namespace Networking