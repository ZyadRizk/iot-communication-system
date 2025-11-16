#include "../common/include/serverChannel.h"
#include "../common/include/TCPSocket.h"
#include <vector>

class serverApp {
private:
    TCPSocket* socket;
    int intThreshold, prevThreshold, intTemprature, port=8080;
    std::string strThreshold, command, strTemprature;
    std::vector<int> tempReadings;
    bool ledStatus;
    
    public:
    serverChannel* channel;
    serverApp(): socket(nullptr), channel(nullptr), 
    intThreshold(30), prevThreshold(-1),
    intTemprature(0), ledStatus(false){};
    ~serverApp();
    void startConnection();
    void sendCommand();
    void mangeCommand();
    void setThreshold();
    void saveTemperature();
    void requestTemperature();
    void updateLedStatus();
    void displayStatus();
};