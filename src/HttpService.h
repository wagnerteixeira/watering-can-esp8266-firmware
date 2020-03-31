#ifndef HttpService_h
#define HttpService_h

#include <ESP8266HTTPClient.h>

#define URL_WATERING_CAN "https://us-central1-watering-can-271217.cloudfunctions.net/wateringCan"
#define URL_WATERED "https://us-central1-watering-can-271217.cloudfunctions.net/watered"

class HttpService {
    private:             
      HTTPClient _httpClient;   
      char* _treeId;
      char* _fingerprint;
      void addTreeId(String& data);
      
    public:
        HttpService(char* treeId, char* fingerprint);
        bool wateringCan();
        bool watered(bool watered);
};


#endif
