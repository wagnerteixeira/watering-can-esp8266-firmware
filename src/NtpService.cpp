#include "NtpService.h"

#include <NTPClient.h>

NtpService::NtpService(void){
  _timeClient = new NTPClient(_ntpUdp, POOL_SERVER_NAME, UTC_OFFSET_IN_SECONDS, UPDATE_INTERVAL);  
  _timeClient->begin();
}

bool NtpService::IsScheduledTime(ScheduledTime scheduledTime){
  _timeClient->update();
  return (scheduledTime.hour == _timeClient->getHours() && scheduledTime.minute == _timeClient->getMinutes());
}

String NtpService::getFormattedTime() const {
  return this->_timeClient->getFormattedTime();
}


/*&  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  Serial.println(timeClient.getFormattedTime());*/
