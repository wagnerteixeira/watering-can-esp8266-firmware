#include <ArduinoJson.h>

#include "HttpService.h"

HttpService::HttpService(char* treeId, char* fingerprint){
  _treeId =  treeId;
  _fingerprint = fingerprint;  
}

void HttpService::addTreeId(String& data){
  data.concat("\"treeId\":\"");
  data.concat(_treeId);
  data.concat("\"");
}

bool HttpService::watered(bool watered){
  if (_fingerprint != NULL)
    _httpClient.begin(URL_WATERED, _fingerprint);
  else
    _httpClient.begin(URL_WATERED);
  _httpClient.addHeader("Content-Type", "application/json");
  //const char* dataWatered = "{\"treeId\": \"bonsai\", \"watered\": true }";
  String data = String("{");   
  this->addTreeId(data);    
  if (watered)
    data.concat(", \"watered\": true }");
  else
    data.concat(", \"watered\":false }");  
  Serial.println(data);
  int httpCode = _httpClient.POST(data);
  if (httpCode > 0) { //Check the returning code
    String payload = _httpClient.getString();   //Get the request response payload    
    _httpClient.end(); 
    Serial.println(payload);
    StaticJsonDocument<70> doc;
    DeserializationError error = deserializeJson(doc, payload);
    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return false;
    }

    bool result =  doc["result"];
    String message = doc["message"];
    Serial.print("result: ");
    Serial.println(result);
    Serial.print("message: ");
    Serial.println(message);
    return result;
  }
  else{
    Serial.print("Error: ");
    Serial.println(httpCode);
    _httpClient.end();
    return false;
  }
}


bool HttpService::wateringCan(){
  if (_fingerprint != NULL)
    _httpClient.begin(URL_WATERING_CAN, _fingerprint);
  else
    _httpClient.begin(URL_WATERING_CAN);
  _httpClient.addHeader("Content-Type", "application/json");
  //dataWateringCan = "{\"treeId\": \"bonsai\"}";
  String data = String("{");   
  this->addTreeId(data);    
  data.concat("}");
  Serial.println(data);
  int httpCode = _httpClient.POST(data);
  if (httpCode > 0) { //Check the returning code
    String payload = _httpClient.getString();   //Get the request response payload
    _httpClient.end(); 
    Serial.println(payload);
    StaticJsonDocument<70> doc;
    DeserializationError error = deserializeJson(doc, payload);
    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return false;
    }
    bool result =  doc["watering"];    
    String message = doc["message"];
    Serial.print("result: ");
    Serial.println(result);
    Serial.print("message: ");
    Serial.println(message);
    return result;
  }
  else{
    Serial.print("Error: ");
    Serial.println(httpCode);
    _httpClient.end();
    return false;
  }
}

/*void sendWatered(){
  //finalize watering
  httpClient.begin(urlWatered, fingerprint);
  httpClient.addHeader("Content-Type", "application/json");
  int httpCode = httpClient.POST(dataWatered);
 
  if (httpCode > 0) { //Check the returning code
    String payload = httpClient.getString();   //Get the request response payload
    httpClient.end(); 
    StaticJsonDocument<70> doc;
    DeserializationError error = deserializeJson(doc, payload);
    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    bool result =  doc["result"];
    String message = doc["message"];
    Serial.print("result: ");
    Serial.println(result);
    Serial.print("message: ");
    Serial.println(message);
  }
  else{
    Serial.print("Error: ");
    Serial.println(httpCode);
    httpClient.end();
    digitalWrite(pinToWatering, HIGH);
  } 
}
*/
