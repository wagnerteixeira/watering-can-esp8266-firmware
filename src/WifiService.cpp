#include "WifiService.h"

WifiService::WifiService(char* ssid, char* password){
  _ssid = ssid;
  _password = password;
}

bool WifiService::IsConnected(){
  return _connected;
}

bool WifiService::Connect() {
  Serial.println("Connecting to ");
  Serial.println(_ssid); 
  WiFi.begin(_ssid, _password); 

  int timeout = WIFI_TIMEOUT * WIFI_DELAY;
  while ((WiFi.status() != WL_CONNECTED) && (timeout > 0))
  { 
    delay(WIFI_DELAY);
    Serial.print(".");
    timeout -= WIFI_DELAY;
  }  
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");   
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    _connected = true;
  }
  else{
    Serial.println("");
    Serial.println("WiFi not connected"); 
    _connected = false;
  }

  return _connected;
}


void WifiService::Disconnect() {
  _connected = false;
  WiFi.disconnect();
}
