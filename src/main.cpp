#include <Arduino.h>
#include "MqttGateway.h"
#include "SimpleTimer.h"

SimpleTimer mqttTimer(5000);
MqttGateway mqtt("Lucas", "Qualquer123!", "192.168.0.38");

void setup() {
    Serial.begin(115200);
    mqtt.begin();
}

void loop() {
    mqtt.handle();

    uint8_t id = 1;
    double lat = -23.5505;
    double lng = -46.6333;
    float battery = 70.5;
    uint8_t meusEventos[5] = {0, 1, 0, 0, 1};

    if (mqttTimer.isReady()) { 
        mqtt.publishData(id, lat, lng, battery, meusEventos);
        mqttTimer.reset();
    }
}