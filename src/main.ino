#include "EepromService.h"
#include "WifiService.h"
#include "HttpService.h"
#include "NtpService.h"

const char *ssid =  "SA";     // replace with your wifi ssid and wpa2 key
const char *pass =  "1a2b3c4d5e";

const unsigned long WAIT_TIME = 60 * 1000; //1 minute
int PIN_TO_WATERING = 13; 
const int DELAY_WATERING = 2000;

const char* fingerprint = "05 8B 82 BC FE B3 F4 3A FA 4F 77 45 D2 D0 48 E3 6E 29 BD CE";
const char* treeId = "bonsai";

WifiService* wifiService;
EepromService* eepromService;
HttpService* httpService;
NtpService* ntpService;
ScheduledTime scheduledTimes[2];

void initializeEeprom(){
  /*Serial.println("ssid");
  char* newSsid = (char*)malloc(strlen(ssid) + 1);
  strcpy(newSsid, ssid);
  Serial.println(newSsid);
  eepromService->writeSsid(newSsid);

  Serial.println("password");  
  char* newPassword = (char*)malloc(strlen(pass) + 1);
  strcpy(newPassword, pass);
  Serial.println(newPassword);
  eepromService->writePassword(newPassword);

  Serial.println("fingerprint");  
  char* newFingerprint = (char*)malloc(strlen(fingerprint) + 1);
  strcpy(newFingerprint, fingerprint);
  Serial.println(newFingerprint);
  eepromService->writeFingerprint(newFingerprint);  

  Serial.println("treeId");  
  char* newTreeId = (char*)malloc(strlen(treeId) + 1);
  strcpy(newTreeId, treeId);
  Serial.println(newTreeId);
  eepromService->writeTreeId(newTreeId);  */


  Serial.println("scheduledTimes");    
  eepromService->writeScheduledTimes(scheduledTimes); 
  
  eepromService->finalizeWrite();
}

void printEeprom() {
  Serial.println("Print EEPROM data");
  Serial.print("Ssid: ");
  Serial.println(eepromService->Ssid());
  Serial.print("Password: ");
  Serial.println(eepromService->Password());
  Serial.print("Fingerprint: ");
  Serial.println(eepromService->Fingerprint());
  Serial.print("Treeid: ");
  Serial.println(eepromService->TreeId());

  Serial.print("ScheduledTime 1 hour: ");
  Serial.print(eepromService->ScheduledTimes()[0].hour);
  Serial.print(" minute: ");
  Serial.println(eepromService->ScheduledTimes()[0].minute);
  Serial.print("ScheduledTime 2 hour: ");
  Serial.print(eepromService->ScheduledTimes()[1].hour);
  Serial.print(" minute: ");
  Serial.println(eepromService->ScheduledTimes()[1].minute);   
}
void setup() {
  // put your setup code here, to run once:     
  Serial.begin(115200);
  while (!Serial) continue;  
  
  eepromService = new EepromService();    
  /*scheduledTimes[0].hour = 8;
  scheduledTimes[0].minute = 0;

  scheduledTimes[1].hour = 20;
  scheduledTimes[1].minute = 00;
  
  initializeEeprom();*/
  printEeprom();
  wifiService = new WifiService(eepromService->Ssid(), eepromService->Password());  
  httpService = new HttpService(eepromService->TreeId(), eepromService->Fingerprint());
  
  wifiService->Connect();
  if (!wifiService->IsConnected())
    return;

  ntpService = new NtpService();

  pinMode(PIN_TO_WATERING, OUTPUT);   
  digitalWrite(PIN_TO_WATERING, HIGH);
}

void watering() {
  digitalWrite(PIN_TO_WATERING, LOW); 
  delay(DELAY_WATERING);
  digitalWrite(PIN_TO_WATERING, HIGH);
  httpService->watered(true);
  delay(WAIT_TIME);
}

void loop() {
  Serial.println("init loop");
  Serial.println("Watering Test");
  Serial.println(ntpService->getFormattedTime());
  //watering();    
  if (ntpService->IsScheduledTime(eepromService->ScheduledTimes()[0]) ||
      ntpService->IsScheduledTime(eepromService->ScheduledTimes()[1]) ||
      httpService->wateringCan()){
    watering();    
  }
  else  
    delay(WAIT_TIME); 
  /*
  httpClient.begin(urlWateringCan, fingerprint);
  httpClient.addHeader("Content-Type", "application/json");
  int httpCode = httpClient.POST(dataWateringCan);
   
  if (httpCode > 0) { //Check the returning code
    
    String payload = httpClient.getString();   //Get the request response payload
    httpClient.end();
    Serial.println(payload);                     //Print the response payload
    // Allocate the JSON document
    // Use arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<70> doc;
    
    DeserializationError error = deserializeJson(doc, payload);

    Serial.println("Depois desserialize");
  
    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    bool rel =  doc["watering"];
    Serial.print("rel: ");
    Serial.println(rel);

    String srel = String(rel);
    Serial.print("srel: ");
    Serial.println(srel);    
    if(rel) {    
      watering();  
      //sendWatered();
      //1 minuto de espera
      delay(waitTime);
    }
    else
      digitalWrite(pinToWatering, HIGH); // Desliga Bomba 
  }
  else {
    Serial.print("Error: ");
    Serial.println(httpCode);
    httpClient.end();
    digitalWrite(pinToWatering, HIGH);
  }
  
  delay(waitTime); 
  
  /*digitalWrite(12, LOW); 
  valPin12 = digitalRead(12);
  Serial.println(valPin12);
  // put your main code here, to run repeatedly:
  digitalWrite(13, valPin12); // Acende o Led
  delay(500); // Aguarda 1 segundo
  digitalWrite(13, LOW); // Apaga o Led
  //delay(500); // Aguarda 1 segundo*/

 

}
