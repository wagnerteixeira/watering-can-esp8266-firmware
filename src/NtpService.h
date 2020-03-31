#ifndef NtpService_h
#define NtpService_h

#define POOL_SERVER_NAME "br.pool.ntp.org"
#define UTC_OFFSET_IN_SECONDS  -10800
#define DAYLIGHT_OFFSET_IN_SECONDS  0
#define UPDATE_INTERVAL 60000
//const char DAYS_OF_WEEK[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#include <NTPClient.h>
#include <WiFiUdp.h>

struct ScheduledTime {
  int hour;
  int minute;
};

class NtpService {
    private:              
      WiFiUDP _ntpUdp;

    public:
      NtpService(void);      
      bool IsScheduledTime(ScheduledTime scheduledTime);  
      String getFormattedTime() const;
      NTPClient* _timeClient;
};


#endif
