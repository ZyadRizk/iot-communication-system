#include <iostream>
#include <thread>
#include <chrono>
#include "../include/clientApp.h"
#include "../../common/include/clientChannel.h"
#include "../../common/include/TCPSocket.h"


int main(){
    //create socket
    TCPSocket* tcp = new TCPSocket("127.0.0.1", 8080);
    clientChannel client(tcp);
    clientApp app(&client);
    app.startConnection();
    try{
        while (true)
        {
            app.getCommand();
            app.processCommand();
            app.ledStatus();
            // loop every 1 sec
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch(const std::exception& ex){
        std::cerr << "Client error: " << ex.what() << std::endl;
    }
    
}