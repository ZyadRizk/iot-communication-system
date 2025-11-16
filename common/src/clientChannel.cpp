#include <iostream>
#include "../include/clientChannel.h"

clientChannel::~clientChannel(){
    if(isRunning){
        Stop();
    }
    std::cout << "CLient Channel destroyed" << std::endl; //debug
}

void clientChannel::Start(){
    if(!isRunning){
        std::cout << "client channel starting..." << std::endl;
        channelSocket->Connect();
        isRunning = true;
        std::cout << "client channel started" << std::endl;
    }
}

void clientChannel::Send(const std::string& message){
    if(!isRunning){
        throw std::runtime_error("ServerChannel not running");
    }
    channelSocket->Socket::Send(message);
}

std::string clientChannel::Receive(){
    if(!isRunning){
        throw std::runtime_error("ServerChannel not running");
    }
    return channelSocket->Socket::Receive();
}

void clientChannel::Stop(){
    if (isRunning && channelSocket) {
        channelSocket->Shutdown();
        isRunning = false;
        std::cout << "[ServerChannel] Stopped" << std::endl;
    }
}