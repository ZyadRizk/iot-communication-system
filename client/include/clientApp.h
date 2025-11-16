#include "../include/clientChannel.h"
#include "../include/TCPSocket.h"
#include <iostream>


class clientApp{
    protected:
        clientChannel* channel;
        bool LEDStatus;
        int temperature ,intThreshold;
        std::string command ,strThreshold;
    public:
        //ctor
        clientApp(clientChannel* ch):channel(ch),LEDStatus(false),temperature(0),intThreshold(25){}
        //member functions
        void startConnection();
        void getCommand();
        void processCommand();
        void ledStatus();
        void setThreshold();
        void sendTemp();
};