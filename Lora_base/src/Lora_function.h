#include <Arduino.h>
#include <LoRa.h>
#include <String.h>
#include <ArduinoJson.h>
#include <vector>

struct read_data {
    int intData;
    float floatData;
    String stringData;
    StaticJsonDocument<256> jsonData;
};

struct send_data {
    int intData;
    float floatData;
    String stringData;
    String jsonData;
};

void Lora_init(int BAND, int NSS, int RST, int DIO0, int SF, int SBW, int CR);
void Lora_send(String message);
void Lora_readData(char type, struct read_data *data_out);
void Lora_sendData(char type, struct send_data *data_in);

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

void Lora_sendData(char type, struct send_data *data_in) {
    if (type == 'int') {
        LoRa.beginPacket();
        LoRa.write((uint8_t *) &data_in->intData, sizeof(data_in->intData));
        LoRa.endPacket();
        Serial.println("Date sent.");
    }
    else if (type == 'float') {
        LoRa.beginPacket();
        LoRa.write((uint8_t *) &data_in->floatData, sizeof(data_in->floatData));
        LoRa.endPacket();
        Serial.println("Date sent.");
    }
    else if (type == 'String') {
        LoRa.beginPacket();
        LoRa.print(data_in->stringData);
        LoRa.endPacket();
        Serial.println("Date sent.");
    }
    else if (type == 'json') {
        LoRa.beginPacket();
        LoRa.print(data_in->jsonData);
        LoRa.endPacket();
        Serial.println("Date sent.");
    }
}

void Lroa_readData(char type, struct read_data *data_out) {
    if (type == 'int') {     //讀取數值資料
        int intData;
        LoRa.readBytes((uint8_t *) &intData, sizeof(intData));
        Serial.println(intData);
        data_out->intData = intData;            //將資料存入data_out
    }
    else if (type == 'float') {
        float floatData;
        LoRa.readBytes((uint8_t *) &floatData, sizeof(floatData));
        Serial.println(floatData);
        data_out->floatData = floatData;        //將資料存入data_out
    }
    
    else if (type == 'String') {
        String strdata = LoRa.readString();     //讀取字串資料
        Serial.println(strdata);
        data_out->stringData = strdata;         //將資料存入data_out
    }
    else if (type == 'json') {
        String jsondata = LoRa.readString();    //讀取json資料
        Serial.println("response: ");
        Serial.println(jsondata);
        deserializeJson(data_out->jsonData, jsondata);  //解析json資料
    }
    else {
        Serial.println("Type error.");  //類型錯誤
    }
}
