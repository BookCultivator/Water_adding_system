#include <Arduino.h>
#include <SPI.h>
#include <string.h>
#include <Date_Base.h>
#include <Lora_function.h>
#include <WiFi_function.h>
#include <Time_function.h>
#include <handle_json_file.h>

#define M0 23
#define M1 22
#define AUX 21
#define RST 18
#define RTD 19
#define TXD 17

one_to_one obj;  //宣告一個one_to_one物件
one_to_Free obj_free;  //宣告一個one_to_Free物件
get_data obj_get;  //宣告一個get_data物件
Lora_function lora_obj;  //宣告一個Lora_function物件
void WiFi_connect();
void send_address_set(String msg) {
  obj.Addh = 0x00;
  obj.Addl = 0x01; 
  obj.Chan = 23;
  obj.message = msg;  //設定訊息  
};

void setup() {
  Serial.begin(115200);
  lora_obj.Lora_pinSet(M0, M1, AUX, RST, RTD, TXD);  //設定Lora模組的腳位
  lora_obj.Lora_Start();  //啟動Lora模組
  WiFi_connect();
  while (!Serial);
  lora_obj.Lora_ConfigRest();  //重設Lora模組的設定
  Time_init();  //初始化時間
}

void loop() {
  String msg = "Hello World!";  //設定訊息
  send_address_set(msg);  //設定訊息
  lora_obj.Lora_SendMessaege(obj);  //發送訊息
  delay(1000);
}

void WiFi_connect() {
  StaticJsonDocument<256> doc;
  read_json_file("/JsonData/config.json", doc);  //讀取config.json檔案
  JsonArray array = doc["WiFi_Date"];  //取得WiFi資料
  WiFi_STA_connected(array[0]["ssid"], array[0]["password"]);
} 