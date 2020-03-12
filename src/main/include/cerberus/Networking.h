#pragma once

// #define _WIN32

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <vector>
#include <string.h>

#ifndef NET_BUFFER_SIZE
#define NET_BUFFER_SIZE 1024
#endif

namespace net {
namespace {
int sock_tcp = -1;
int sock_udp = -1;

std::vector<int> sock_clients;
std::vector<char*> buff_clients;

struct sockaddr_in tcp_address;

std::thread thread_networking;
std::thread thread_listener;

bool isActive = false;
bool isUpdating = false;

#ifdef _WIN32
	WSADATA wsaData;
#endif
}  // namespace

void networkingThread();
void listenerThread();


void initialize() {
	#ifdef _WIN32
	WSADATA wsaData;
	
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR) {
        printf("failed to initialize network code.\n");
        // TODO: Proper logging.
        // TODO: error check.
		return;
	}
	#endif

    // Create a tcp socket descriptor.
    if ((sock_tcp = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("failed to create a tcp socket.\n");
        // TODO: Proper logging.
        // TODO: error check.
    }

    // Create a udp socket descriptor.
    if ((sock_udp = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        printf("failed to create a udp socket.\n");
        // TODO: Proper logging.
        // TODO: error check.
    }

    // configure the tcp socket properties.
    // see: https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-setsockopt for details.
	#ifndef _WIN32
    int option = 1;
    if (setsockopt(sock_tcp, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option)) < 0) {
	#else
	const char option = 1;
	if (setsockopt(sock_tcp, SOL_SOCKET, SO_REUSEADDR | SO_REUSE_UNICASTPORT, &option, sizeof(option)) != 0) {
	#endif
        // TODO: Proper logging.
        // TODO: error check.
        printf("could not configure the tcp socket.\n");
        return;
    }

    // bind the tcp socket to the specifed port.
    tcp_address.sin_family = AF_INET;
    tcp_address.sin_addr.s_addr = INADDR_ANY;
    tcp_address.sin_port = htons(6666);

    if (::bind(sock_tcp, (struct sockaddr*)&tcp_address, sizeof(tcp_address)) < 0) {
        // TODO: Proper logging.
        // TODO: error check.
        printf("failed to bind the tcp socket to port 6666.\n");
        return;
    }

    // Run the listener and main networking thread loops.
    isActive = true;

    thread_listener = std::thread(listenerThread);
    thread_networking = std::thread(networkingThread);
}
void deinitialize() {
    isActive = false;

    thread_networking.join();
    thread_listener.join();
}

void update() {}

void networkingThread() {
	while (isActive == false);

    while (isActive) {
		// FIXME: handle when a connection is closed.
        for (int i = sock_clients.size() - 1; i >= 0; i--) {
			#ifndef _WIN32
            if (read(sock_clients[i], buff_clients[i], NET_BUFFER_SIZE) < 0) {
			#else
            if (recv(sock_clients[i], buff_clients[i], NET_BUFFER_SIZE, 0) < MSG_OOB) {
			#endif
                // TODO: Proper logging.
                // TODO: error check.
                printf("failed to read from tcp socket at index %i.\n", i);
                isActive = false;
                return;
            }

			// FIXME: make a more perminate solution for storing client data.
			if(buff_clients[i] != nullptr) {
				struct sockaddr_in client_address;
				socklen_t client_address_len = sizeof(client_address);
				getpeername(sock_clients[i], (struct sockaddr*)&client_address, &client_address_len);
				printf("[%s:%d] %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), buff_clients[i]);
			}
        }
    }
}

void listenerThread() {
	while (isActive == false);
	
    while (isActive) {
        // listen for tcp clients trying to connect.
        if (listen(sock_tcp, 3) < 0) {
            // TODO: Proper logging.
            // TODO: error check.
            printf("failed to listen on tcp socket.\n");
            isActive = false;
            return;
        }

        // Accept the tcp client into a new socket.
        int sock_client;
        if ((sock_client = accept(sock_tcp, (struct sockaddr*)&tcp_address, (socklen_t*)&tcp_address)) < 0) {
            // TODO: Proper logging.
            // TODO: error check.
            printf("failed to accept an incomming tcp socket.\n");
            isActive = false;
            return;
        }

        // Allocate a buffer for the client.
        buff_clients.push_back((char*)malloc(NET_BUFFER_SIZE));

        if (buff_clients[buff_clients.size() - 1] == nullptr) {
            // TODO: Proper logging.
            // TODO: error check.
            printf("failed to allocate buffer memory for new client.\n");
            buff_clients.pop_back();
            isActive = false;
            return;
        }

        // Add socket to socket vector.
        sock_clients.push_back(sock_client);
    }
}

}  // namespace net