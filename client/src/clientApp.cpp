#include "../include/clientApp.h"
#include <iostream>


//ctor
clientApp::clientApp(clientChannel* ch):channel(ch),LEDStatus(false),temperature(0),intThreshold(25){}
//member functions
void clientApp::startConnection(){
    //start channel logic
    channel->Start();
    //after starting connection start receiving commands from server
}
void clientApp::getCommand(){
    //get comand logic
    command=channel->Receive();
}
void clientApp::processCommand(){
    //process command logic
    if(command=="SET_THRESHOLD"){
        setThreshold();
    }
    else if(command=="GET_TEMPERATURE"){
        sendTemp();
    }
}
void clientApp::ledStatus(){
    //handels led status
    LEDStatus = (temperature > intThreshold);
    if(LEDStatus){
        std::cout << "LED is ON" << std::endl;
    }
    else{
        std::cout << "LED is OFF" << std::endl;
    }
}
void clientApp::setThreshold(){
    //sets threshold after reciving it form server
    strThreshold = channel->Receive();
    intThreshold = std::stoi(strThreshold);
}
void clientApp::sendTemp(){
    //sends temprature to server 
    std::cin >> temperature; //simulate reading temperature
    channel->Send(std::to_string(temperature));   
}
