#pragma once

// #include <netinet/tcp.h>
#include <stdlib.h>
#include <wpi/Logger.h>
#include <wpi/NetworkStream.h>
#include <wpi/TCPAcceptor.h>
#include <wpi/UDPClient.h>

#include <string>
#include <vector>

using namespace std;
using namespace wpi;

namespace Networking {
void AcceptNewClient();

namespace {
static vector<unique_ptr<NetworkStream>> clients;
static TCPAcceptor* tcp;
static Logger logger = Logger();
static int robot_port = 6666;
static char* robot_ip = (char*)"127.0.0.1";

static bool shouldRepalceDuplicateIps = false;

NetworkStream::Error lastError;
}  // namespace

void Initalize() {
    tcp = new TCPAcceptor(robot_port, nullptr, logger);
    tcp->start();
}

void Deinitalize() {
    tcp->shutdown();
	delete tcp;
}

void Update() {
    AcceptNewClient();
}

int Size() {
	return clients.size();
}

NetworkStream::Error GetLastError() {
	return lastError;
}

int Read(int index, char* data, int length) {
    return clients[index]->receive(data, length, &lastError, 0);
}

int Read(const char* ip, char* data, int length) {
    for (std::size_t i = 0; i < clients.size(); i++) {
        if (clients[i]->getPeerIP().data() == ip) {
            return clients[i]->receive(data, length, &lastError, 0);
        }
    }

	return -1;
}

int Write(const char* ip, char* data, int length) {
    for (std::size_t i = 0; i < clients.size(); i++) {
        if (clients[i]->getPeerIP().data() == ip) {
            return clients[i]->send(data, length, &lastError);
        }
    }

	return -1;
}

int Write(int index, char* data, int length) {
    return clients[index]->send(data, length, &lastError);
}

void Close(const char* ip) {
    for (std::size_t i = 0; i < clients.size(); i++) {
        if (clients[i]->getPeerIP().data() == ip) {
            clients[i]->close();
            clients[i].release();
            clients.erase(clients.begin() + i);
            return;
        }
    }
}

void CloseAll() {
    for (std::size_t i = 0; i < clients.size(); i++) {
        clients[i]->close();
        clients[i].release();
    }

	clients.clear();
}

void AcceptNewClient() {
    unique_ptr<NetworkStream> client = tcp->accept();

    if (client != nullptr) {
        bool isInClientList = false;

        for (std::size_t i = 0; i < clients.size(); i++) {
            if (clients[i]->getPeerIP().data() == client->getPeerIP().data()) {
                isInClientList = true;
                if (shouldRepalceDuplicateIps == true) {
                    clients[i]->close();

                    clients.erase(clients.begin() + i);
                    clients.push_back(std::move(client));
                    break;
                }
            }
        }

        if (isInClientList == false) {
            clients.push_back(std::move(client));
        }
    }
}

const char* GetRobotIp() {
    return robot_ip;
}

int GetRobotPort() {
    return robot_port;
}

}  // namespace Networking
