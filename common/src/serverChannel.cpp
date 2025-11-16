#include "../include/serverChannel.h"
#include <iostream> 

// Destructor
ServerChannel::~ServerChannel() {
    if(isRunning) {
        Stop();
    }
    std::cout << "ServerChannel destroyed" << std::endl; //debug
}

void ServerChannel::Start() {
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

void ServerChannel::Stop() {
    if (isRunning && channelSocket) {
        channelSocket->Shutdown();
        isRunning = false;
        std::cout << "ServerChannel stopped" << std::endl; //debug
    }
}
void ServerChannel::Send(const std::string& message) {
    if (!isRunning) {
        throw std::runtime_error("ServerChannel not running");
    }
    channelSocket->Send(message);
}

std::string ServerChannel::Receive(){
    if(!isRunning){
        throw std::runtime_error("ServerChannel not running");
    }
    return channelSocket->Socket::Receive();
}

