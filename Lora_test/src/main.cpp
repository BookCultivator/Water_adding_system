#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

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

  LoRa.setPins(NSS, RST, DIO0);  //設定LoRa模組的腳位
  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa init failed. Check your connections.");  //如果初始化失敗，請檢查連接
    while (true);
  }
  Serial.println("LoRa init succeeded.");
  // LoRa.setSpreadingFactor(12);
  // LoRa.setSignalBandwidth(125E3);
  // LoRa.setCodingRate4(5);
  // LoRa.setPreambleLength(8);
  // LoRa.setSyncWord(0x34);
  // LoRa.enableCrc();
  // LoRa.idle();
  Serial.println("LoRa init parameters set.");
}

void loop() {
}