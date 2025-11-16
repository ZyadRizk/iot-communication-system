#include "../include/UDPSocket.h"
#include <iostream>

//ctor
UDPSocket::UDPSocket(const std::string& ip, uint16_t port) 
    : Socket(ip, port), clientAddrLen(sizeof(cliaddr)) {
    // Step 1: Create a socket
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd < 0) 
        throw std::runtime_error("Failed to create UDP socket"); 
    std::cout << "UDP Socket has been created successfully" << std::endl; //debug   

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
    
    // Setup address structures
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Convert the server address from text to binary form
    if (ip == "0.0.0.0" || ip.empty()) {
        servaddr.sin_addr.s_addr = INADDR_ANY;
    } else {
        inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr);
    }
}

//dtor
UDPSocket::~UDPSocket() {
    Shutdown();
}

void UDPSocket::BindSocket() {
    if (bind(socketFd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        throw std::runtime_error("Failed to bind UDP socket");
    }
    std::cout << "UDP Server bound to " << ipAddress << ":" << port << std::endl; //debug
}

void UDPSocket::WaitForConnect() {
    BindSocket();
    isConnected = true; // UDP is connectionless, so we consider it "connected"
    std::cout << "UDP Server ready to receive" << std::endl;
}

void UDPSocket::Connect() {
    // UDP is connectionless; no action needed
    isConnected = true; // UDP is connectionless, so we consider it "connected"
    std::cout << "UDP Client ready to send to " << ipAddress << ":" << port << std::endl; //debug
}

void UDPSocket::Send(const std::string& message) {\
    //make shoure its connected
    if (!isConnected) {
        throw std::runtime_error("Socket not connected");
    }
    ssize_t bytesSent = sendto(socketFd, message.c_str(), message.length(), 0,
        (struct sockaddr*)&servaddr, sizeof(servaddr));
    //check if send was successful
    if (bytesSent < 0) {
        throw std::runtime_error("Failed to send UDP message");
    }
}

std::string UDPSocket::Receive() {
    char buffer[1024];
    ssize_t bytesReceived = recvfrom(socketFd, buffer, sizeof(buffer) - 1, 0,
        (struct sockaddr*)&cliaddr, &clientAddrLen);
    if (bytesReceived < 0) {
        throw std::runtime_error("Failed to receive UDP message");
    }
    buffer[bytesReceived] = '\0'; // Null-terminate the received data
    std::cout << "Received UDP message: " << buffer << std::endl; //debug
    return std::string(buffer, bytesReceived);
}

void UDPSocket::Shutdown() {
    if (socketFd != -1) {
        close(socketFd);
        socketFd = -1;
        isConnected = false;
        std::cout << "UDP Socket has been shut down" << std::endl; //debug
    }
}






