#include "EepromService.h"
#include "Arduino.h"

#include <EEPROM.h>

EepromService::EepromService(void){
  EEPROM.begin(EEPROM_MAX_SIZE);
  _ssidAddress = 0;  
  _passwordAddress = _ssidAddress + sizeof(_ssid) + 1;
  _fingerprintAddress = _passwordAddress + sizeof(_password) + 1;  
  _treeIdAddress = _fingerprintAddress + sizeof(_fingerprint) + 1;
  _scheduledTimesAddress = _treeIdAddress + sizeof(_treeId) + 1;
  Serial.print("\n_ssidAddress: ");
  Serial.println(_ssidAddress);
  Serial.print("_passwordAddress: ");
  Serial.println(_passwordAddress);
  Serial.print("_fingerprintAddress: ");
  Serial.println(_fingerprintAddress);
  Serial.print("_treeIdAddress: ");
  Serial.println(_treeIdAddress);
  Serial.print("_scheduledTimesAddress: ");
  Serial.println(_scheduledTimesAddress);
  EEPROM.get(_ssidAddress, this->_ssid);
  EEPROM.get(_passwordAddress, this->_password);
  EEPROM.get(_fingerprintAddress, this->_fingerprint);
  EEPROM.get(_treeIdAddress, this->_treeId);
  EEPROM.get(_scheduledTimesAddress, this->_scheduledTimes);
}

void EepromService::writeSsid(char* ssid){
  memcpy(&this->_ssid, ssid, strlen(ssid) + 1);  
  Serial.print("Writing ssid: ");
  Serial.print(this->_ssid);
  Serial.print(" to address ");
  Serial.print(_ssidAddress);
  EEPROM.put(_ssidAddress, this->_ssid);   
  Serial.print("\n");
}

void EepromService::writePassword(char* password){
  memcpy(&this->_password, password, strlen(password)+1);
  Serial.print("Writing password: ");
  Serial.print(this->_password);
  Serial.print(" to address ");
  Serial.print(_passwordAddress);
  EEPROM.put(_passwordAddress, this->_password); 
  Serial.print("\n");  
}
       

void EepromService::writeFingerprint(char* fingerprint){
  memcpy(&this->_fingerprint, fingerprint, strlen(fingerprint)+1);
  Serial.print("Writing fingerprint: ");
  Serial.print(this->_fingerprint);
  Serial.print(" to address ");
  Serial.print(_fingerprintAddress);
  EEPROM.put(_fingerprintAddress, this->_fingerprint); 
  Serial.print("\n");
}

void EepromService::writeTreeId(char* treeId){
  memcpy(&this->_treeId, treeId, strlen(treeId)+1);
  Serial.print("Writing treeId: ");
  Serial.print(this->_treeId);
  Serial.print(" to address ");
  Serial.print(_treeIdAddress);
  EEPROM.put(_treeIdAddress, this->_treeId); 
  Serial.print("\n");
}

void EepromService::writeScheduledTimes(ScheduledTime scheduledTimes[2]){
  _scheduledTimes[0].hour = scheduledTimes[0].hour;
  _scheduledTimes[0].minute = scheduledTimes[0].minute;
  _scheduledTimes[1].hour = scheduledTimes[1].hour;
  _scheduledTimes[1].minute = scheduledTimes[1].minute;
  
  Serial.println("Writing scheduledTimes:");
  Serial.print(" to address ");
  Serial.println(_scheduledTimesAddress);
  Serial.print("ScheduledTime 1 hour: ");
  Serial.print(_scheduledTimes[0].hour);
  Serial.print(" minute: ");
  Serial.println(_scheduledTimes[0].minute);
  Serial.print("ScheduledTime 2 hour: ");
  Serial.print(_scheduledTimes[1].hour);
  Serial.print(" minute: ");
  Serial.println(_scheduledTimes[1].minute);  
  EEPROM.put(_scheduledTimesAddress, _scheduledTimes); 
  Serial.print("\n");
}

void EepromService::finalizeWrite(){
  EEPROM.commit();
}
   
char* EepromService::Ssid(){
  return this->_ssid;
}

char* EepromService::Password(){
  return this->_password;
}

char* EepromService::Fingerprint(){
  return this->_fingerprint;
}

char* EepromService::TreeId(){
  return this->_treeId;
}

ScheduledTime* EepromService::ScheduledTimes(){
  return this->_scheduledTimes;
}
