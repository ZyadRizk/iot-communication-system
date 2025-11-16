#include "../include/TCPSocket.h"
#include <iostream>

//ctor
TCPSocket::TCPSocket(const std::string& ip, uint16_t port) 
    : Socket(ip, port), clientSocketFd(-1) {
    // Step 1: Create a socket
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == 0) {
        throw std::runtime_error("Failed to create TCP socket");
    }
    std::cout << "Socket has been created successfully" << std::endl; //debug
    
    // Allow address reuse
    int opt = 1;
    setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Step 2: Specify the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    
    // Convert the server address from text to binary form
    if (ip == "0.0.0.0" || ip.empty()) {
        serverAddr.sin_addr.s_addr = INADDR_ANY;
    } else {
        inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
    }
}

//dtor
TCPSocket::~TCPSocket() {
    Shutdown();
}

// Private: Bind and listen
void TCPSocket::BindAndListen(int backlog) {
    // Only bind if not already bound
    if (!isBound) {
        // Step 3: Bind the socket to the specified IP and port
        if (bind(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            throw std::runtime_error("Bind failed!");
        }
        isBound = true;
        std::cout << "Server: Socket has been bound successfully to " 
                  << ipAddress << ":" << port << std::endl;
    }
    
    // Only listen if not already listening
    if (!isListening) {
        // Step 4: Listen for incoming connections
        if (listen(socketFd, backlog) < 0) {
            throw std::runtime_error("Listen failed!"); 
        }
        isListening = true;
        std::cout << "Server: Listening for connections (backlog=" << backlog << ")" << std::endl;
    }
}

int TCPSocket::AcceptConnection() {
    std::cout << "Server: Waiting for client connection..." << std::endl; //debug
    socklen_t addrLen = sizeof(clientAddr);
    clientSocketFd = accept(socketFd, (struct sockaddr*)&clientAddr, &addrLen);
    if (clientSocketFd < 0) {
        throw std::runtime_error("Accept failed!");
    }
    isConnected = true;
    std::cout << "Server: Connection accepted from "
              << inet_ntoa(clientAddr.sin_addr) << ":"
              << ntohs(clientAddr.sin_port) << std::endl; //debug
    return clientSocketFd;
}

// Public: Wait for connection (Server mode)
void TCPSocket::WaitForConnect() {
    BindAndListen();
    AcceptConnection();
}

// Public: Connect to server (Client mode)
void TCPSocket::Connect() {
    // Step 3: Connect to the server
    std::cout << "Connecting to TCP server at " << ipAddress << ":" << port << "..." << std::endl; //debug
    if (connect(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Connection failed!");
    }
    std::cout << "Connected to TCP server at " << ipAddress << ":" << port << std::endl; //debug
    isConnected = true;
}

void TCPSocket::Send(const std::string& message) {
    if (!isConnected) {
        throw std::runtime_error("Socket not connected");
    }
    int fd = (clientSocketFd > 0) ? clientSocketFd : socketFd;

    ssize_t bytesSent = send(fd, message.c_str(), message.length(), 0);
    if (bytesSent < 0) {
        throw std::runtime_error("Failed to send TCP message");
    }
    std::cout << "Sent " << bytesSent << " bytes: " << message << std::endl; //debug
}

std::string TCPSocket::Receive() {
    if (!isConnected) {
        throw std::runtime_error("Socket not connected");
    }
    int fd = (clientSocketFd > 0) ? clientSocketFd : socketFd;
    char buffer[1024] = {0};
    ssize_t bytesRead = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead < 0) {
        throw std::runtime_error("Failed to receive TCP message");
    } else if (bytesRead == 0) {
        isConnected = false;
        throw std::runtime_error("Connection closed by peer");
    }
    std::string(buffer, bytesRead);
    std::cout << "Received " << bytesRead << " bytes: " << buffer << std::endl; //debug
    return std::string(buffer, bytesRead);
}

void TCPSocket::Shutdown() {
    if (clientSocketFd != -1) {
        close(clientSocketFd);
        clientSocketFd = -1;
    }
    if (socketFd != -1) {
        close(socketFd);
        socketFd = -1;
    }
    isConnected = false;
    std::cout << "TCP Socket has been shut down" << std::endl; //debug
}