#include <Arduino.h>
#include <ArduinoJson.h>
#include <String.h>
#include <LoRa_E220.h>
#include <Data_Base.h>
#include <vector>

class Config {
	private:
		Configuration conf;
		ResponseStructContainer c;
	public:
		void Lora_getConfig(struct LoRa_E220 &obj);  //取得設定
	    void printParameters(struct Configuration configuration);  //印出參數
		void printModuleInformation(struct ModuleInformation moduleInformation);  //印出模組資訊
		void Config_structReset(struct LoRa_E220 &obj);  //重設結構體
		void Config_structSet(struct LoRa_E220 &obj);
		void setConfig_ADDH(byte in_da);
		void setConfig_ADDL(byte in_da);
		void setConfig_CHAN(int in_da);
		void setConfig_uartBaudRate(int in_da);
		void setConfig_airDataRate(int in_da);
		void setConfig_uartParity(int in_da);
		void setConfig_subPacketSetting(int in_da);
		void setConfig_RSSIAmbientNoise(int in_da);
		void setConfig_transmissionPower(int in_da);
		void setConfig_enableRSSI(int in_da);
		void setConfig_fixedTransmission(int in_da);
		void setConfig_enableLBT(int in_da);
		void setConfig_WORPeriod(int in_da);
};

void Config::Lora_getConfig(struct LoRa_E220 &obj) {
    ResponseStructContainer c = obj.getConfiguration();   //取得設定
    Configuration conf = *(Configuration *)c.data;   //取得設定資料
    Serial.println(c.status.getResponseDescription());   //印出回應描述
    Serial.println(c.status.code);   //印出回應代碼
    printParameters(conf);   //印出設定資料

    ResponseStructContainer cMi;      //宣告一個回應結構體
	cMi = obj.getModuleInformation();
	ModuleInformation mi = *(ModuleInformation*)cMi.data;
	Serial.println(cMi.status.getResponseDescription());
	Serial.println(cMi.status.code);
	printModuleInformation(mi);

    c.close();  //關閉回應結構體
    cMi.close();  //關閉回應結構體
}

void Config::Config_structReset(struct LoRa_E220 &obj) {  //重設結構體
	ResponseStructContainer locale_c = obj.getConfiguration();  //取得設定
	conf = *(Configuration *)locale_c.data;  //取得設定資料
	Serial.println(locale_c.status.getResponseDescription());  //印出回應描述
	Serial.println(locale_c.status.code);  //印出回應代碼
}

void Config::Config_structSet(struct LoRa_E220 &obj) {  //設定結構體
	ResponseStatus re = obj.setConfiguration(conf, WRITE_CFG_PWR_DWN_SAVE);  //設定參數
	Serial.println(re.getResponseDescription());  //印出回應描述
	Serial.println(re.code);  //印出回應代碼
	Serial.println("Set configuration done.");  //印出設定完成
	c.close();  //關閉回應結構體
}

void Config::setConfig_ADDH(byte in_da) {
	conf.ADDH = in_da;
}

void Config::setConfig_ADDL(byte in_da) {
	conf.ADDL = in_da;
}

void Config::setConfig_CHAN(int in_da) {
	conf.CHAN = in_da;
}

void Config::setConfig_uartBaudRate(int in_da) {
	conf.SPED.uartBaudRate = in_da;
}

void Config::setConfig_airDataRate(int in_da) {
	conf.SPED.airDataRate = in_da;
}

void Config::setConfig_uartParity(int in_da) {
	conf.SPED.uartParity = in_da;
}

void Config::setConfig_subPacketSetting(int in_da) {
	conf.OPTION.subPacketSetting = in_da;
}

void Config::setConfig_RSSIAmbientNoise(int in_da) {
	conf.OPTION.RSSIAmbientNoise = in_da;
}

void Config::setConfig_transmissionPower(int in_da) {
	conf.OPTION.transmissionPower = in_da;
}

void Config::setConfig_enableRSSI(int in_da) {
	conf.TRANSMISSION_MODE.enableRSSI = in_da;
}

void Config::setConfig_fixedTransmission(int in_da) {
	conf.TRANSMISSION_MODE.fixedTransmission = in_da;
}

void Config::setConfig_enableLBT(int in_da) {
	conf.TRANSMISSION_MODE.enableLBT = in_da;
}

void Config::setConfig_WORPeriod(int in_da) {
	conf.TRANSMISSION_MODE.WORPeriod = in_da;
}

void Config::printParameters(struct Configuration configuration) {
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

void Config::printModuleInformation(struct ModuleInformation moduleInformation) {
	Serial.println("----------------------------------------");
	Serial.print(F("HEAD: "));  Serial.print(moduleInformation.COMMAND, HEX);Serial.print(" ");Serial.print(moduleInformation.STARTING_ADDRESS, HEX);Serial.print(" ");Serial.println(moduleInformation.LENGHT, DEC);

	Serial.print(F("Model no.: "));  Serial.println(moduleInformation.model, HEX);
	Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
	Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
	Serial.println("----------------------------------------");
}

class Lora_function {
    private:
		int _M0, _M1, _AUX, _RST, _RTD, _TXD;
		LoRa_E220 e220_obj = LoRa_E220(&Serial2,_AUX, _M0, _M1);  //宣告一個LoRa_E220物件
        byte ADDH = 0x03;    		   //設定ADDH的預設值
		byte ADDL = 0x00;  			   //設定ADDL的預設值
		int CHAN = 23;   		  	   //設定CHAN的預設值
		int uartBaudRate = UART_BPS_9600;  //設定uartBaudRate的預設值
		int airDataRate = AIR_DATA_RATE_100_96;  //設定airDataRate的預設值
		int uartParity = MODE_00_8N1;  //設定uartParity的預設值
		int subPacketSetting = SPS_200_00; //設定subPacketSetting的預設值
		int RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;   //設定RSSIAmbientNoise的預設值
		int transmissionPower = POWER_22;  //設定transmissionPower的預設值
		int enableRSSI = RSSI_DISABLED;  //設定enableRSSI的預設值
		int fixedTransmission = FT_TRANSPARENT_TRANSMISSION;  //設定fixedTransmission的預設值
		int enableLBT = LBT_DISABLED;  //設定enableLBT的預設值
		int WORPeriod = WOR_2000_011;  //設定WORPeriod的預設值
    public:
        void Lora_pinSet(int M0, int M1, int AUX, int RST, int RTD, int TXD);
        void Lora_Start();
        void Lora_ConfigRest();
        void Lora_SendMessaege(struct one_to_one &obj);  //發送訊息
		void Lora_SendMessaege(struct one_to_Free &obj);  //發送訊息
		void Lora_GetMessage(struct get_data *obj);  //接收訊息
};

void Lora_function::Lora_pinSet(int M0, int M1, int AUX, int RST, int RTD, int TXD) {  //設定Lora模組的腳位
    _M0 = M0;
    _M1 = M1;
    _AUX = AUX;  
    _RST = RST;
    _RTD = RTD;
    _TXD = TXD;
}

void Lora_function::Lora_Start() {
    Serial2.begin(9600, SERIAL_8N1, _TXD, _RTD);
    Serial.println("Serial2 begin.");
    e220_obj.begin();
}

void Lora_function::Lora_ConfigRest() {
	Config conf;
	conf.Config_structReset(e220_obj);  //重設結構體
	conf.setConfig_ADDH(ADDH);  //設定ADDH
	conf.setConfig_ADDL(ADDL);  //設定ADDL
	conf.setConfig_CHAN(CHAN);  //設定CHAN
	conf.setConfig_uartBaudRate(uartBaudRate);  //設定uartBaudRate
	conf.setConfig_airDataRate(airDataRate);  //設定airDataRate
	conf.setConfig_uartParity(uartParity);  //設定uartParity
	conf.setConfig_subPacketSetting(subPacketSetting);  //設定subPacketSetting
	conf.setConfig_RSSIAmbientNoise(RSSIAmbientNoise);  //設定RSSIAmbientNoise
	conf.setConfig_transmissionPower(transmissionPower);  //設定transmissionPower
	conf.setConfig_enableRSSI(enableRSSI);  //設定enableRSSI
	conf.setConfig_fixedTransmission(fixedTransmission);  //設定fixedTransmission
	conf.setConfig_enableLBT(enableLBT);  //設定enableLBT
	conf.setConfig_WORPeriod(WORPeriod);  //設定WORPeriod
	conf.Config_structSet(e220_obj);  //設定結構體
}

void Lora_function::Lora_SendMessaege(struct one_to_one &obj) {  //發送訊息
	ResponseStatus re = e220_obj.sendFixedMessage(obj.Addh, obj.Addl, obj.Chan, obj.message);  //發送固定訊息
	Serial.println(re.getResponseDescription());  //印出回應描述
	Serial.println(re.code);  //印出回應代碼
	Serial.println("Send message done.");  //印出發送完成
	if (!re.code) {
		Serial.println("Send message failed.");
		return;  //如果發送失敗，則返回
	}
}

void Lora_function::Lora_SendMessaege(struct one_to_Free &obj) {  //發送訊息
	ResponseStatus re = e220_obj.sendFixedMessage(obj.Addh, obj.Addl, obj.Chan, obj.message);  //發送固定訊息
	Serial.println(re.getResponseDescription());  //印出回應描述
	Serial.println(re.code);  //印出回應代碼
	Serial.println("Send message done.");  //印出發送完成
	if (!re.code) {
		Serial.println("Send message failed.");
		return;  //如果發送失敗，則返回
	}
}

void Lora_function::Lora_GetMessage(struct get_data *obj) {
	if (e220_obj.available()>1) {
		ResponseContainer r = e220_obj.receiveMessageRSSI();  //接收訊息
		if (r.status.code != 1) {
			Serial.println(r.status.getResponseDescription());  //印出回應描述
			Serial.println(r.status.code);  //印出回應代碼
		}
		else {
			Serial.println(r.status.getResponseDescription());  //印出回應描述
			Serial.println(r.data);  //印出接收的資料
			obj->stringData = r.data;  //將接收的資料存入get_data結構體
		}
		Serial.print("RSSI: ");  Serial.println(r.rssi, DEC);  //印出RSSI
	}
	else {
		Serial.println("No data available.");  //印出沒有資料可用
	}
}


