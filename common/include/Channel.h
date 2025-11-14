#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include "Socket.h"


/**
 * Abstract base class for communication channels
 * Responsibilities: Manage socket interactions through channelSocket
 * This is a THIN WRAPPER - no business logic here!
 */
class Channel
{
protected:
    // Private Data Members
    Socket* channelSocket;
    bool isRunning;
public:
    
    Channel(Socket* socket) : channelSocket(socket) , isRunning(false) {};

    // Virtual destructor
    virtual ~Channel() {
        if (channelSocket) {
            delete channelSocket;
            channelSocket = nullptr;
        }
    }

    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Send(const std::string& message) = 0;
    virtual void Receive() = 0;

    // Concrete methods
    bool getRunningStatus() const { return isRunning; }
    Socket* getSocket() const { return channelSocket; }
};

#endif // CHANNEL_H