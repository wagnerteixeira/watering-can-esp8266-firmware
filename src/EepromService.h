#ifndef EepromService_h
#define EepromService_h

#include "NtpService.h"

const int EEPROM_MAX_SIZE = 4096;
const int EEPROM_MAX_STRING_SIZE = 200;

class EepromService {
    private:
        char _ssid[100];
        int _ssidAddress;
        char _password[100];              
        int _passwordAddress;
        char _fingerprint[61];
        int _fingerprintAddress;
        char _treeId[30];  
        int _treeIdAddress;
        ScheduledTime _scheduledTimes[2];
        int _scheduledTimesAddress;
    public:
        EepromService(void);
        void writeSsid(char* ssid);
        void writePassword(char* password);
        void writeFingerprint(char* fingerprint);
        void writeTreeId(char* treeId);
        void writeScheduledTimes(ScheduledTime scheduledTimes[2]);
        char* Ssid();
        char* Password();
        char* Fingerprint();
        char* TreeId();
        ScheduledTime* ScheduledTimes();
        void finalizeWrite();
};

#endif
