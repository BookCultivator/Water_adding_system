#include <ArduinoJson.h>
#include <String.h>

struct get_data {
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

