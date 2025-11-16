#include "../include/clientChannel.h"
#include <iostream>

class clientApp{
    protected:
        clientChannel* channel;
        bool LEDStatus;
        int temperature ,threshold;
        std::string command;
    public:
        //ctor
        clientApp(clientChannel* ch):channel(ch),LEDStatus(false),temperature(0),threshold(25){}
        //member functions
        void startConnection(){
            //start channel logic
            channel->Start();
            //after starting connection start receiving commands from server
        }
        void getCommand(){
            //get comand logic
            /*command=*/channel->Receive();
        }
        void processCommand(){
            //process command logic
            if(command=="SET_THRESHOLD"){
                setThreshold();
            }
            else if(command=="GET_TEMPERATURE"){
                sendTemp();
            }
        }
        void ledStatus(){
            //handels led status
            LEDStatus = (temperature > threshold);
            if(LEDStatus){
                std::cout << "LED is ON" << std::endl;
            }
            else{
                std::cout << "LED is OFF" << std::endl;
            }
        }
        void setThreshold(){
            //sets threshold after reciving it form server
            //threshold = /*value from server*/;
        }
        void sendTemp(){
            //sends temprature to server 
            std::cin >> temperature; //simulate reading temperature
            channel->Send(std::to_string(temperature));   
        }
};