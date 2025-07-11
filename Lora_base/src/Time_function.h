#include <Arduino.h>
#include <Data_Base.h>

const char ntpServer[] = "pool.ntp.org";
const uint16_t gmtOffest = 8 * 3600;  // UTC+8偏移量
const uint8_t daylightOffset = 0;   // 夏令時間
const u_int mode_range = 3;
u_int mode = 0;


void Time_init() {
    configTime(gmtOffest, daylightOffset, ntpServer);
    Serial.println("NTP 時間同步中...");

    struct tm timeinfo;
    int retry = 0;
    const int max_retries = 5;  // 最大重試次數
    while (!getLocalTime(&timeinfo) && retry < max_retries) {
        Serial.println("獲取時間中...");
        retry++;
        delay(1000);
    }
    
    if (retry >= max_retries) {
        Serial.println("時間同步失敗。");
    }
    else {
        Serial.println("時間同步成功！");
    }
}

void getCurrentTime(struct TimeData *ntime) {
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        Serial.println("獲取時間失敗，重試...");
        delay(1000);
    }
    ntime->hour = timeinfo.tm_hour; 
    ntime->minute = timeinfo.tm_min;
    ntime->year = timeinfo.tm_year + 1900;
    ntime->mon = timeinfo.tm_mon + 1;
    ntime->day = timeinfo.tm_mday;
}