#ifndef clientCHANNEL_H
#define clientCHANNEL_H 


#include "Channel.h"
#include "Socket.h"
/**
 * clientChannel class derived from Channel
 * Responsibilities: Manage client-side communication through channelSocket
 * This is a THIN WRAPPER - no business logic here!
 */
class clientChannel : public Channel {
public:
    // Constructor
    clientChannel(Socket* socket) : Channel(socket){} ;
    // Destructor
    virtual ~clientChannel() override;
    // Override virtual methods
    void Start() override ;
    void Stop() override ;
    void Send(const std::string& message) override ;
    void Receive() override ;
    bool getRunningStatus() const { return isRunning; }

};

#endif // clientCHANNEL_H