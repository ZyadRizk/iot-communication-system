#ifndef SOCKET_H
#define SOCKET_H

#include <string>

class Socket{
protected:
    int socketFd;              // Socket file descriptor
    std::string ipAddress;     // IP address
    unsigned short port;       // Port number
    bool isConnected;          // Connection status
public:
    // Constructor
    Socket(const std::string& ip, unsigned short p) 
        : socketFd(-1), ipAddress(ip), port(p), isConnected(false) {}
    virtual ~Socket(){} ;

    virtual void WaitForConnect() = 0;
    virtual void Connect() = 0;
    virtual void Send(const std::string& message) = 0;
    virtual std::string Receive() = 0;
    virtual void Shutdown() = 0;

    // Concrete helper methods
    bool getConnectionStatus() const { return isConnected; }
    int getSocketFd() const { return socketFd; }
    std::string getIpAddress() const { return ipAddress; }
    unsigned short getPort() const { return port; }
};

#endif // SOCKET_H