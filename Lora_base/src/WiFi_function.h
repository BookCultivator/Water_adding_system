#include <Arduino.h>
#include <WiFi.h>  // 若使用 ESP8266 則改用 <ESP8266WiFi.h>
#include <string>

const char* getEncryptionType(uint8_t encryptionType) {
    switch (encryptionType) {
        case WIFI_AUTH_OPEN: return "開放網路 (無密碼)";
        case WIFI_AUTH_WEP: return "WEP";
        case WIFI_AUTH_WPA_PSK: return "WPA/PSK";
        case WIFI_AUTH_WPA2_PSK: return "WPA2/PSK";
        case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2/PSK";
        case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2 Enterprise";
        case WIFI_AUTH_WPA3_PSK: return "WPA3/PSK";
        default: return "未知加密類型";
    }
}

void WiFi_souch() {
  WiFi.mode(WIFI_STA);  // 設定 Wi-Fi 模式為「Station」模式
  WiFi.disconnect();     // 先斷開連線，確保 Wi-Fi 可正常掃描

  Serial.println("開始掃描 Wi-Fi...");
  int networksFound = WiFi.scanNetworks();  // 開始掃描
  
  if (networksFound == 0) {
    Serial.println("找不到 Wi-Fi");
  } else {
    Serial.printf("找到 %d 個 Wi-Fi\n", networksFound);
    for (int i = 0; i < networksFound; i++) {
      uint8_t* Bssid = WiFi.BSSID(i);
      Serial.printf("%d: \n", i + 1);
      Serial.printf("SSID: %s\n", WiFi.SSID(i).c_str());
      Serial.printf("訊號強度: %d dBm\n", WiFi.RSSI(i));
      Serial.printf("BSSID: %02x:%02x:%02x:%02x:%02x:%02x\n", Bssid[0], Bssid[1], Bssid[2], Bssid[3], Bssid[4], Bssid[5]);
      Serial.printf("加密類型: %s\n", getEncryptionType(WiFi.encryptionType(i)));
      Serial.println("---------------------");
    }
  }
}

void WiFi_STA_connected(const char ssid[], const char password[]) {
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  Serial.println("WiFi Connected");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.printf(">.< ");
  }
  Serial.print("local IP: ");
  Serial.println(WiFi.localIP());
}