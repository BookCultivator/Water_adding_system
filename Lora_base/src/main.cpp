#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>
#include <string.h>
#include <Lora_function.h>
#include <WiFi_function.h>
#include <Time_function.h>
#include <handle_json_file.h>

#define BAND 433E6 //頻率
#define MOSI 27    //MOSI腳位
#define MISO 19    //MISO腳位
#define SCK 5      //時脈腳位
#define NSS 18     //片選腳位
#define RST 14     //重置腳位
#define DIO0 26    //中斷腳位

void WiFi_connect();

void setup() {
  Serial.begin(115200);
  reset_SPIFFS();
  WiFi_connect();
  while (!Serial);
  Lora_init(BAND, NSS, RST, DIO0, 12, 125E3, 5);  //初始化LoRa模組
  Time_init();  //初始化時間
}

void loop() {
}

void WiFi_connect() {
  StaticJsonDocument<256> doc;
  read_json_file("/JsonData/config.json", doc);  //讀取config.json檔案
  JsonArray array = doc["WiFi_Date"];  //取得WiFi資料
  WiFi_STA_connected(array[0]["ssid"], array[0]["password"]);
} 