#include "../include/serverChannel.h"
#include <iostream> 

// Destructor
serverChannel::~serverChannel() {
    if(isRunning) {
        Stop();
    }
    std::cout << "ServerChannel destroyed" << std::endl; //debug
}

void serverChannel::Start() {
    if (!channelSocket) {
        throw std::runtime_error("No socket assigned to channel");
        }
    if (!isRunning) {
        std::cout << "[ServerChannel] Starting..." << std::endl;
        channelSocket->WaitForConnect();
        isRunning = true;
        std::cout << "[ServerChannel] Client connected and ready" << std::endl;    
    }
}

void serverChannel::Stop() {
    if (isRunning && channelSocket) {
        channelSocket->Shutdown();
        isRunning = false;
        std::cout << "ServerChannel stopped" << std::endl; //debug
    }
}
void serverChannel::Send(const std::string& message) {
    if (!isRunning) {
        throw std::runtime_error("ServerChannel not running");
    }
    channelSocket->Send(message);
}

std::string serverChannel::Receive(){
    if(!isRunning){
        throw std::runtime_error("ServerChannel not running");
    }
    return channelSocket->Socket::Receive();
}

