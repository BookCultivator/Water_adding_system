#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>
#include <Lora_function.h>

#define BAND 433E6 //頻率
#define MOSI 27    //MOSI腳位
#define MISO 19    //MISO腳位
#define SCK 5      //時脈腳位
#define NSS 18     //片選腳位
#define RST 14     //重置腳位
#define DIO0 26    //中斷腳位

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Lora_init(BAND, NSS, RST, DIO0, 12, 125E3, 5);  //初始化LoRa模組
  
}

void loop() {
}