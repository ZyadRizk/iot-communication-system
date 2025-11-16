#include "serverApp.h"
#include <iostream>

serverApp::serverApp(): socket(nullptr), channel(nullptr), 
    intThreshold(30), prevThreshold(-1),
    intTemprature(0), ledStatus(false){ 
    socket = new TCPSocket("0.0.0.0", port);
    channel = new serverChannel(socket);
}

serverApp::~serverApp() {
    if (channel) {
        channel->Stop();
        delete channel;
    }
}

void serverApp::startConnection(){
    std::cout << "Server: Starting..." << std::endl;
    channel->Start();
    std::cout << "Server: Client connected!" << std::endl;
}

void serverApp::mangeCommand(){
    if(command == "SET_THRESHOLD"){
        setThreshold();
    }
    else if(command == "Get_TEMPERATURE"){
        requestTemperature();
        updateLedStatus();
    }
    else{
        std::cout << "Server: Unknown command received." << std::endl;
    }
}

void serverApp::sendCommand(){
    std::cin >> command;
    channel->Send(command);
    mangeCommand();
}

void serverApp::setThreshold(){
    channel->Send("SET_THRESHOLD");
    std::cin >> strThreshold;
    strThreshold = std::to_string(intThreshold);
    channel->Send(strThreshold);    
    std::cout << "Server: Threshold set to " << strThreshold << std::endl;
}

void serverApp::saveTemperature(){
    tempReadings.push_back(intTemprature);
    std::cout << "Server: Temperature " << intTemprature << "°C saved." << std::endl;
}

void  serverApp::requestTemperature(){
    strTemprature = channel->Receive();
    intTemprature = std::stoi(strTemprature);
    std::cout << "Server: Current Temperature is " << intTemprature << "°C" << std::endl;
    saveTemperature();
}

void serverApp::updateLedStatus() {
    ledStatus = (intTemprature > intThreshold);
}

void serverApp::displayStatus() {
    std::cout << "[STATUS] Temp: " << intTemprature << "°C | "
              << "Threshold: " << intThreshold << "°C | "
              << "LED: " << (ledStatus ? "ON" : "OFF") << " | "
              << "History: " << tempReadings.size() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}