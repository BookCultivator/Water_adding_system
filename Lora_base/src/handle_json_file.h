#include <Arduino.h>
#include <HTTPClient.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

void reset_SPIFFS();
void read_json_file(const char *filename, StaticJsonDocument<256> &doc);
void write_json_file(const char *filename, StaticJsonDocument<256> &doc);
void read_json_fileForSD(int SD_CS_PIN, const char *filename, StaticJsonDocument<256> &doc);
void GetServerJsonToFile(const char *filename, const char *url, StaticJsonDocument<256> &doc);

void reset_SPIFFS() {
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS"); // SPIFFS初始化失敗
        return;
    }
}

void read_json_file(const char *filename, StaticJsonDocument<256> &doc) {  // 讀取JSON檔案
    File file = SPIFFS.open(filename, "r");
    if (!file) {
        Serial.println("file open failed");  // 檔案開啟失敗
        return;
    }
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.println("deserializeJson() failed");  // JSON解析失敗
        return;
    }
    file.close();
}

void write_json_file(const char *filename, StaticJsonDocument<256> &doc) {  // 寫入JSON檔案
    File file = SPIFFS.open(filename, "w");
    if (!file) {
        Serial.println("file open failed");  // 檔案開啟失敗
        return;
    }
    serializeJson(doc, file);
    file.close();
}

void read_json_fileForSD(int SD_CS_PIN, const char *filename, StaticJsonDocument<256> &doc) {
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("SD Card Mount Failed");  // SD卡初始化失敗
        return;
    }
    
    File file = SD.open(filename, FILE_READ);
    if (!file) {
        Serial.println("file open failed");  // 檔案開啟失敗
        return;
    }
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.println("deserializeJson() failed");  // JSON解析失敗
        return;
    }
    file.close();
}

void GetServerJsonToFile(const char *filename, const char *url, StaticJsonDocument<256> &doc) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(url);
        int httpCode = http.GET();
        if (httpCode > 0) {
            if (httpCode == HTTP_CODE_OK) {  // HTTP_CODE_OK = 200
                String payload = http.getString();   
                Serial.println("Get Json Date success");
                Serial.printf("Json Date: %s\n", payload);
                DeserializationError error = deserializeJson(doc, payload);
                if (error) {
                    Serial.println("deserializeJson() failed");  // JSON解析失敗
                    Serial.printf("Error Code: %d\n", httpCode);
                    return;
                }
                File file = SPIFFS.open(filename, "w");
                if (!file) {
                    Serial.println("file open failed");  // 檔案開啟失敗
                    return;
                }  
                serializeJson(doc, file);
                file.print(payload);  // 寫入JSON資料
                file.close();
                Serial.println("Save Json Date success");  // 儲存JSON成功
            }
        }
        http.end();
    }
    else {
        Serial.println("WiFi Disconnected or server error");  // WiFi未連線或伺服器錯誤
    }
}
