#pragma once

// #include <netinet/tcp.h>
#include <stdlib.h>
#include <wpi/Logger.h>
#include <wpi/NetworkStream.h>
#include <wpi/TCPAcceptor.h>
#include <wpi/TCPStream.h>
#include <wpi/UDPClient.h>

#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace wpi;

#define MAX_BUFFER_LENGTH 65536

namespace net {
// TODO: add UDP support.

// TODO: remove this line when moving to a .cpp file.
void acceptNewClients();
void clearAllBuffers();

static vector<char*> buffers;

namespace {
vector<unique_ptr<NetworkStream>> clients;

Logger logger = Logger();
wpi::TCPAcceptor* tcp;
int robot_port = 6666;
// char robot_ip[] = "127.0.0.1";
char robot_ip[] = "";

bool shouldRepalceDuplicateIps = false;
bool isUpdating = false;
bool isNetworkActive = false;

NetworkStream::Error lastError;

std::thread net_thread;
}  // namespace

void initialize() {
    net_thread = std::thread(acceptNewClients);
}

void deinitialize() {
    net_thread.join();
    tcp->shutdown();
    delete tcp;
}

void update() {
    isUpdating = true;

    for (int i = 0; i < buffers.size(); i++) {
        memset(buffers[i], 0, MAX_BUFFER_LENGTH);
        size_t len = clients[i]->receive((char*)buffers[i], MAX_BUFFER_LENGTH, &lastError, 0);
    }

    isUpdating = false;
}

int size() {
    return clients.size();
}

NetworkStream::Error GetLastError() {
    return lastError;
}

void* read(const char* ip) {
    for (std::size_t i = 0; i < clients.size(); i++) {
        if (clients[i]->getPeerIP().data() == ip) {
            return buffers[i];
        }
    }

    return nullptr;
}

int write(const char* ip, char* data, int length) {
    for (std::size_t i = 0; i < clients.size(); i++) {
        if (clients[i]->getPeerIP().data() == ip) {
            return clients[i]->send(data, length, &lastError);
        }
    }

    return -1;
}

int write(int index, char* data, int length) {
    return clients[index]->send(data, length, &lastError);
}

void close(const char* ip) {
    for (std::size_t i = 0; i < clients.size(); i++) {
        if (clients[i]->getPeerIP().data() == ip) {
            clients[i]->close();
            clients[i].release();
            clients.erase(clients.begin() + i);

            free(buffers[i]);
            buffers.erase(buffers.begin() + i);

            // TODO: Log that the client was closed.
            return;
        }
    }

    // TODO: Log that no client was closed.
}

void closeAll() {
    for (std::size_t i = 0; i < clients.size(); i++) {
        clients[i]->close();
        clients[i].release();

        free(buffers[i]);
    }

    clients.clear();
    buffers.clear();

    // TODO: Log that all clients have been closed.
}

void acceptNewClients() {
    printf("Initializing networking system...\n");
    // tcp = new TCPAcceptor(robot_port, robot_ip, logger);
    // tcp = new TCPAcceptor(5800, "127.0.0.1", logger);
    tcp = new wpi::TCPAcceptor(6666, "127.0.0.1", logger);
    if (tcp->start() != 0) {
        printf("failed to initialize networking system.\n");
        return;
    }
    // tcp->accept();
    isNetworkActive = true;
    // net_thread = std::thread(acceptNewClients);
    printf("The networking system has been initialized.\n");

    while (isNetworkActive == true) {
        auto c = tcp->accept();
        // unique_ptr<NetworkStream> client = tcp->accept();

        unique_ptr<NetworkStream> client;

        if (client != nullptr) {
            while (isUpdating == true)
                ;

            bool isInClientList = false;

            for (std::size_t i = 0; i < clients.size(); i++) {
                if (clients[i]->getPeerIP().data() == client->getPeerIP().data()) {
                    isInClientList = true;
                    if (shouldRepalceDuplicateIps == true) {
                        clients[i]->close();

                        clients.erase(clients.begin() + i);
                        free(buffers[i]);
                        buffers.erase(buffers.begin() + i);

                        clients.push_back(std::move(client));
                        buffers.push_back((char*)malloc(MAX_BUFFER_LENGTH));
                        // TODO: Validate size by making sure clients.size() == buffers.size();

                        // TODO: Log that client has been replaced.
                        break;
                    }
                }
            }

            if (isInClientList == false) {
                clients.push_back(std::move(client));
                buffers.push_back((char*)malloc(MAX_BUFFER_LENGTH));
                // TODO: Validate size by making sure clients.size() == buffers.size();

                // TODO: Log that client has been added.
            }
        }
    }
}

const char* getRobotIp() {
    return robot_ip;
}

int getRobotPort() {
    return robot_port;
}

}  // namespace net
