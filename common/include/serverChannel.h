#ifndef SERVERCHANNEL_H
#define SERVERCHANNEL_H 


#include "Channel.h"
#include "Socket.h"
/**
 * ServerChannel class derived from Channel
 * Responsibilities: Manage server-side communication through channelSocket
 * This is a THIN WRAPPER - no business logic here!
 */
class serverChannel : public Channel {
public:
    // Constructor
    serverChannel(Socket* socket) : Channel(socket){} ;
    // Destructor
    virtual ~serverChannel() override;
    // Override virtual methods
    void Start() override ;
    void Stop() override ;
    void Send(const std::string& message) override ;
    std::string Receive() override ;
    bool getRunningStatus() const { return isRunning; }

};

#endif // SERVERCHANNEL_H