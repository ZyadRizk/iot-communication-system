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

// Bind and listen method
void TCPSocket::BindAndListen(int backlog) {
    // Step 3: Bind the socket to the specified IP and port
    if (bind(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Bind failed!");
    }
    std::cout<<"Server : Socket has been binded successfully \n"; //debug
    // Step 4: Listen for incoming connections
    if (listen(socketFd, backlog) < 0) {
        throw std::runtime_error("Listen failed!"); 
    std::cout<<"Server : listening \n"; //debug 
    }

}

int TCPSocket::AcceptConnection() {
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

void TCPSocket::WaitForConnect() {
    AcceptConnection();
}

void TCPSocket::Connect() {
    // Step 3: Connect to the server
    if (connect(clientSocketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
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

void TCPSocket::Receive() {
    if (!isConnected) {
        throw std::runtime_error("Socket not connected");
    }
    int fd = (clientSocketFd > 0) ? clientSocketFd : socketFd;
    char buffer[1024] = {0};
    ssize_t bytesRead = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead < 0) { 
        
    }
    if (bytesRead < 0) {
        throw std::runtime_error("Failed to receive TCP message");
    } else if (bytesRead == 0) {
        isConnected = false;
        throw std::runtime_error("Connection closed by peer");
    }

    std::string(buffer, bytesRead);
}
