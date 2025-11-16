#include <iostream>
#include <thread>
#include <chrono>
#include "../include/serverApp.h"

int main() {
    serverApp app;
    app.startConnection();
    if(!app.channel->getRunningStatus()){
        std::cerr << "Failed to start server channel" << std::endl;
        return -1;
    }
    try{
        while (true)
        {
            app.sendCommand();      // Check if threshold changed
            app.displayStatus();        // Show current status
            
            // Loop every 1 sec
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch(const std::exception& ex){
        std::cerr << "Client error: " << ex.what() << std::endl;
    }
}