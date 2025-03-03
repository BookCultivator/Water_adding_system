#include <Arduino.h>
#include <LoRa.h>

void Lora_init(int BAND, int NSS, int RST, int DIO0, int SF, int SBW, int CR) {
    LoRa.setPins(NSS, RST, DIO0);  //設定LoRa模組的腳位
    if (!LoRa.begin(BAND)) {
        Serial.println("LoRa init failed. Check your connections.");  //如果初始化失敗，請檢查連接
        while (true);
    }
    Serial.println("LoRa init succeeded.");  //初始化成功
    LoRa.setSpreadingFactor(SF);  //設定擴散因子
    LoRa.setSignalBandwidth(SBW);  //設定信號頻寬
    LoRa.setCodingRate4(CR);  //設定編碼率
    Serial.println("LoRa init parameters set.");
}

