#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "Socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

/**
 * TCP Socket implementation
 */

class TCPSocket :public Socket{
private:
    int clientSocketFd;  // For server: connected client socket
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    bool isBound;       // Track if socket is bound
    bool isListening;   // Track if socket is listening
public:
    // Constructor
    TCPSocket(const std::string& ip, uint16_t port);
    
    // Destructor
    ~TCPSocket() override;

    void WaitForConnect() override;
    void Connect() override;
    void Send(const std::string& message) override;
    void Receive() override;
    void Shutdown() override;

    // TCP-specific methods
    void BindAndListen(int backlog = 5); 
    int AcceptConnection();
};

#endif // TCPSOCKET_H