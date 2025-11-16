#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "Socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

/**
 * UDP Socket implementation
 */

class UDPSocket :public Socket{
private:
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clientAddrLen;
public:
    // Constructor
    UDPSocket(const std::string& ip, uint16_t port);
    
    // Destructor
    ~UDPSocket() override;

    void WaitForConnect() override;
    void Connect() override;
    void Send(const std::string& message) override;
    std::string Receive() override;
    void Shutdown() override;

    // UDP-specific methods
    void BindSocket(); 

};

#endif // UDPSOCKET_H