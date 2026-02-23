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
    double lat = -19.967759;
    double lng = -43.955429;
    float battery = 70.5;
    uint8_t meusEventos[5] = {0, 1, 0, 0, 1};

    if (mqttTimer.isReady()) {
        mqtt.publishData(id, lat, lng, battery, meusEventos);
        mqttTimer.reset();
    }
}