#include <ArduinoJson.h>
#include <String.h>

struct get_data {
    String stringData;
};

struct one_to_one {
    byte Addh = 0x00;    		   //設定ADDH的預設值
    byte Addl = 0x01;  			   //設定ADDL的預設值 
    int Chan = 23;  			   //設定CHAN的預設值
    String message;                //訊息
};

struct one_to_Free {
    byte Addh = 0xFF;    		   //設定ADDH的預設值
    byte Addl = 0xFF;  			   //設定ADDL的預設值 
    int Chan = 23;  			   //設定CHAN的預設值
    String message;                //訊息
};

struct TimeData {                  // 結構體用於存儲時間數據
    int hour;
    int minute;
    int year;
    int mon;
    int day;
};