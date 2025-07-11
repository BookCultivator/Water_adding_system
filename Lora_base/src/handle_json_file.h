#include <Arduino.h>
#include <HTTPClient.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <SD.h>


class JsonFileHandle {
private:
    DeserializationError _error;  // JSON反序列化錯誤
    StaticJsonDocument<256> _doc;  // JSON靜態文檔
public:
    void reset_SPIFFS();  // 重設SPIFFS
    void read_json_file(const char *filename, StaticJsonDocument<256> &doc);  // 讀取JSON檔案
    void write_json_file(const char *filename, StaticJsonDocument<256> &doc);  // 寫入JSON檔案
    void read_json_fileForSD(int SD_CS_PIN, const char *filename, StaticJsonDocument<256> &doc);  // 讀取SD卡上的JSON檔案
    void GetServerJsonToFile(const char *filename, const char *url);  // 從伺服器獲取JSON並儲存到檔案
    void Json_to_String(StaticJsonDocument<256> &doc, String &jsonString);  // 將JSON轉換為字串
    void String_to_Json(String &jsonString, StaticJsonDocument<256> &doc);  // 將字串轉換為JSON
};

void JsonFileHandle::reset_SPIFFS() {
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS"); // SPIFFS初始化失敗
        return;
    }
}

void JsonFileHandle::Json_to_String(StaticJsonDocument<256> &doc, String &jsonString) {  // 將JSON轉換為字串
    serializeJson(doc, jsonString);  // 將JSON序列化為字串
}

void JsonFileHandle::String_to_Json(String &jsonString, StaticJsonDocument<256> &doc) {  // 將字串轉換為JSON
    _error = deserializeJson(doc, jsonString);  // 反序列化字串為JSON
    if (_error) {
        Serial.println("deserializeJson() failed");  // JSON解析失敗
        return;
    }
}

void JsonFileHandle::read_json_file(const char *filename, StaticJsonDocument<256> &doc) {  // 讀取JSON檔案
    File file = SPIFFS.open(filename, "r");
    if (!file) {
        Serial.println("file open failed");  // 檔案開啟失敗
        return;
    }
    _error = deserializeJson(doc, file);
    if (_error) {
        Serial.println("deserializeJson() failed");  // JSON解析失敗
        return;
    }
    file.close();
}

void JsonFileHandle::write_json_file(const char *filename, StaticJsonDocument<256> &doc) {  // 寫入JSON檔案
    File file = SPIFFS.open(filename, "w");
    if (!file) {
        Serial.println("file open failed");  // 檔案開啟失敗
        return;
    }
    serializeJson(doc, file);
    file.close();
}

void JsonFileHandle::read_json_fileForSD(int SD_CS_PIN, const char *filename, StaticJsonDocument<256> &doc) {
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("SD Card Mount Failed");  // SD卡初始化失敗
        return;
    }
    
    File file = SD.open(filename, FILE_READ);
    if (!file) {
        Serial.println("file open failed");  // 檔案開啟失敗
        return;
    }
    _error = deserializeJson(doc, file);
    if (_error) {
        Serial.println("deserializeJson() failed");  // JSON解析失敗
        return;
    }
    file.close();
}

void JsonFileHandle::GetServerJsonToFile(const char *filename, const char *url) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Disconnected");  // WiFi未連線
        return;
    }

    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode <= 0) {
        Serial.println("HTTP GET failed");  // HTTP GET請求失敗
        return;
    }

    if (httpCode == HTTP_CODE_OK) {  // HTTP_CODE_OK = 200
        String payload = http.getString();   
        Serial.println("Get Json Date success");
        Serial.printf("Json Date: %s\n", payload.c_str());  // 印出JSON資料
        _error = deserializeJson(_doc, payload);  // 解析JSON資料
        if (_error) {
            Serial.println("deserializeJson() failed");  // JSON解析失敗
            Serial.printf("Error Code: %d\n", httpCode);    
            return;
        }
        File file = SPIFFS.open(filename, "w");
        if (!file) {
            Serial.println("file open failed");  // 檔案開啟失敗
            return;
        }  
        serializeJson(_doc, file);
        file.close();
        Serial.println("Save Json Date success");  // 儲存JSON成功
    }
    else {
        Serial.printf("HTTP GET failed, Error Code: %d\n", httpCode);  // HTTP GET請求失敗
    }
    http.end();  // 結束HTTP請求
    Serial.println("HTTP end");  // 結束HTTP請求
}