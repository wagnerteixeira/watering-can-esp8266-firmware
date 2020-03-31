#ifndef WifiService_h
#define WifiService_h

#include <ESP8266WiFi.h>


const int WIFI_TIMEOUT = 30;
const int WIFI_DELAY = 500;

class WifiService {
    private:        
        bool _connected;
        char* _ssid;              
        char* _password;

    public:
        WifiService(char* ssid, char* password);
        bool Connect();
        void Disconnect();
        bool IsConnected();
};

#endif
