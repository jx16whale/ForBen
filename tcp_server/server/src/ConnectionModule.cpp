#include "..\include\ConnectionModule.h"

// #include <netinet/in.h>
#include <stdio.h>
// #include <sys/socket.h>
#include <winsock2.h>

#include <cstring>
#include <string>

ConnectionModule::ConnectionModule(int port) {
    // Create server socket
    serverSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSockfd == -1) {
        perror("Error creating server socket");
        return;
    }

    // Set server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Bind server socket
    if (bind(serverSockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) ==
        -1) {
        perror("Error binding server socket");
        closesocket(serverSockfd);
        return;
    }

    // Listen for incoming connections
    if (listen(serverSockfd, 5) == -1) {
        perror("Error listening for connections");
        closesocket(serverSockfd);
        return;
    }

    printf("Server is listening for incoming connections on port %d\n", port);
}

ConnectionModule::~ConnectionModule() {
    closesocket(serverSockfd);
    if (clientSockfd != -1) {
        closesocket(clientSockfd);
    }
}

bool ConnectionModule::waitForConnection() {
    // Accept incoming connection
    clientAddrLen = sizeof(clientAddr);
    clientSockfd =
        accept(serverSockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSockfd == -1) {
        perror("Error accepting connection");
        return false;
    }
    printf("Connection accepted from %s:%d\n", inet_ntoa(clientAddr.sin_addr),
           ntohs(clientAddr.sin_port));
    return true;
}

bool ConnectionModule::sendData(const char* data, int dataSize) {
    size_t bytesSent = send(clientSockfd, data, dataSize, 0);
    if (bytesSent == -1) {
        perror("Error sending data");
        return false;
    }
    return true;
}

bool ConnectionModule::receiveData(char* buffer, int bufferSize) {
    size_t bytesReceived = recv(clientSockfd, buffer, bufferSize, 0);
    if (bytesReceived == -1) {
        perror("Error receiving data");
        return false;
    }
    buffer[bytesReceived] = '\0';  // Null-terminate the received data
    return true;
}
