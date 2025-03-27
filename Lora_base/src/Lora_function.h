#include <Arduino.h>
#include <ArduinoJson.h>
#include <String.h>
#include <LoRa_E220.h>
#include <Date_Base.h>
#include <vector>

int *_M0, *_M1, *_AUX, *_RST, *_RTD, *_TXD;
LoRa_E220 e220_obj(&Serial2,*_AUX, *_M0, *_M1);

class Lora_function {
    private:
        byte ADDl;
        
    public:
        void Lora_pinSet(int &M0, int &M1, int &AUX, int &RST, int &RTD, int &TXD);
        void Lora_Start();
        void Lora_Restart();
        void Lora_getConfig();
        void Lora_setConfig();
        void printParameters(struct Configuration configuration);
        void printModuleInformation(struct ModuleInformation moduleInformation);
        void Lora_sendData(struct send_data &data);
};

void Lora_function::Lora_pinSet(int &M0, int &M1, int &AUX, int &RST, int &RTD, int &TXD) {  //設定Lora模組的腳位
    _M0 = &M0;
    _M1 = &M1;
    _AUX = &AUX;  
    _RST = &RST;
    _RTD = &RTD;
    _TXD = &TXD;
}

void Lora_function::Lora_Start() {
    Serial2.begin(9600, SERIAL_8N1, *_TXD, *_RTD);
    Serial.println("Serial2 begin.");
    e220_obj.begin();
}

void Lora_function::Lora_getConfig() {
    ResponseStructContainer c;         //宣告一個回應結構體
    c = e220_obj.getConfiguration();   //取得設定
    Configuration conf = *(Configuration *)c.data;   //取得設定資料
    Serial.println(c.status.getResponseDescription());   //印出回應描述
    Serial.println(c.status.code);   //印出回應代碼
    printParameters(conf);   //印出設定資料

    ResponseStructContainer cMi;      //宣告一個回應結構體
	cMi = e220_obj.getModuleInformation();
	ModuleInformation mi = *(ModuleInformation*)cMi.data;
	Serial.println(cMi.status.getResponseDescription());
	Serial.println(cMi.status.code);
	printModuleInformation(mi);

    c.close();  //關閉回應結構體
    cMi.close();  //關閉回應結構體
}

void Lora_function::printParameters(struct Configuration configuration) {
	Serial.println("----------------------------------------");

	Serial.print(F("HEAD : "));  Serial.print(configuration.COMMAND, HEX);Serial.print(" ");Serial.print(configuration.STARTING_ADDRESS, HEX);Serial.print(" ");Serial.println(configuration.LENGHT, HEX);
	Serial.println(F(" "));
	Serial.print(F("AddH : "));  Serial.println(configuration.ADDH, HEX);
	Serial.print(F("AddL : "));  Serial.println(configuration.ADDL, HEX);
	Serial.println(F(" "));
	Serial.print(F("Chan : "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
	Serial.println(F(" "));
	Serial.print(F("SpeedParityBit     : "));  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
	Serial.print(F("SpeedUARTDatte     : "));  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRateDescription());
	Serial.print(F("SpeedAirDataRate   : "));  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRateDescription());
	Serial.println(F(" "));
	Serial.print(F("OptionSubPacketSett: "));  Serial.print(configuration.OPTION.subPacketSetting, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getSubPacketSetting());
	Serial.print(F("OptionTranPower    : "));  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());
	Serial.print(F("OptionRSSIAmbientNo: "));  Serial.print(configuration.OPTION.RSSIAmbientNoise, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getRSSIAmbientNoiseEnable());
	Serial.println(F(" "));
	Serial.print(F("TransModeWORPeriod : "));  Serial.print(configuration.TRANSMISSION_MODE.WORPeriod, BIN);Serial.print(" -> "); Serial.println(configuration.TRANSMISSION_MODE.getWORPeriodByParamsDescription());
	Serial.print(F("TransModeEnableLBT : "));  Serial.print(configuration.TRANSMISSION_MODE.enableLBT, BIN);Serial.print(" -> "); Serial.println(configuration.TRANSMISSION_MODE.getLBTEnableByteDescription());
	Serial.print(F("TransModeEnableRSSI: "));  Serial.print(configuration.TRANSMISSION_MODE.enableRSSI, BIN);Serial.print(" -> "); Serial.println(configuration.TRANSMISSION_MODE.getRSSIEnableByteDescription());
	Serial.print(F("TransModeFixedTrans: "));  Serial.print(configuration.TRANSMISSION_MODE.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.TRANSMISSION_MODE.getFixedTransmissionDescription());


	Serial.println("----------------------------------------");
}

void Lora_function::printModuleInformation(struct ModuleInformation moduleInformation) {
	Serial.println("----------------------------------------");
	Serial.print(F("HEAD: "));  Serial.print(moduleInformation.COMMAND, HEX);Serial.print(" ");Serial.print(moduleInformation.STARTING_ADDRESS, HEX);Serial.print(" ");Serial.println(moduleInformation.LENGHT, DEC);

	Serial.print(F("Model no.: "));  Serial.println(moduleInformation.model, HEX);
	Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
	Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
	Serial.println("----------------------------------------");
}

void Lora_function::Lora_sendData(struct send_data &data) {
    
}

