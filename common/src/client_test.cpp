#include "../include/TCPSocket.h"
#include "../include/clientChannel.h"
#include <iostream>

int main() {
    try {
        TCPSocket* tcp = new TCPSocket("127.0.0.1", 8080);
        clientChannel client(tcp);

        client.Start();        // Connect to server
        client.Send("Hello from client");
        client.Receive();      // prints server reply
        client.Stop();
    }
    catch (const std::exception& ex) {
        std::cerr << "Client error: " << ex.what() << std::endl;
    }
}
