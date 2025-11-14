#include "../include/TCPSocket.h"
#include "../include/serverChannel.h"
#include <iostream>

int main() {
    try {
        TCPSocket* tcp = new TCPSocket("0.0.0.0", 8080);
        ServerChannel server(tcp);

        server.Start(); // Waits for client
        server.Receive(); // prints received msg

        server.Send("Hello from server");

        server.Stop();
    }
    catch (const std::exception& ex) {
        std::cerr << "Server error: " << ex.what() << std::endl;
    }
}
