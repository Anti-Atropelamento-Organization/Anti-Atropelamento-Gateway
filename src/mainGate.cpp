#include "LoraGateway.h"
#include "SimpleTimer.h"
#include "MqttGateway.h"

LoraGateway gate;
SimpleTimer st_1(2000);
SimpleTimer st_2(5000);
SimpleTimer mqttTimer(5000);
uint8_t eventos[5] = {};
int32_t last5positions[5][2] = {};
ActiveVehicles nearbyVehicles[MAX_VEHICLES] = {};

unsigned long jitterTargetTime = 0;


// MqttGateway mqtt("NET_2GE8461A", "DDE8461A", "192.168.0.17");
MqttGateway mqtt("TSA_CORPORATIVO", "tsatecnologia", "172.16.2.18");

void setup() {
    Serial.begin(115200);
    gate.setup();
    Serial.println("Gateway LoRa iniciado.");
    delay(2000);

    mqtt.begin();
    Serial.println("MQTT Gateway iniciado.");
    delay(1000);
}
void loop()
{
    mqtt.handle();

    if(gate.receive()){

        uint8_t id = gate.getID();
        uint16_t randomPacketID = gate.getRandomPacketID();

        gate.buildAck(id, randomPacketID);
        gate.sendAck();
        Serial.println();

        gate.getDeviceType() == VEHICLE_DEVICE ? Serial.println("Tipo do dispositivo: Veículo") : Serial.println("Tipo do dispositivo: Pessoal");

        if(gate.getTypePacket() == MONITORING_PACKET) {
            Serial.println("Pacote de Monitoramento recebido.");
            uint8_t deviceType = gate.getDeviceType();
            double lat = gate.getLatitude();
            double lng = gate.getLongitude();
            uint8_t battery = gate.getBatteryLevel();
            uint8_t status = gate.getStatus();
            float hdop = gate.getHdop();

            Serial.print("ID: ");
            Serial.println(id);
            Serial.print("Latitude: ");
            Serial.println(lat, 6);
            Serial.print("Longitude: ");
            Serial.println(lng, 6);
            Serial.print("Bateria: ");
            Serial.println(battery);
            Serial.print("Status: ");
            Serial.println(status);
            Serial.print("HDOP: ");
            Serial.println(hdop);
            Serial.println();
            Serial.println();
            mqtt.publishDataMonitoring(id, deviceType, lat, lng, battery, status, hdop);
        } else if(gate.getTypePacket() == LOG_PACKET) {
            Serial.println("Pacote de Log recebido.");
            gate.getLastPositions(last5positions);
            gate.getLastEvents(eventos);
            gate.getNearbyVehicles(nearbyVehicles);
            uint8_t deviceType = gate.getDeviceType();
            mqtt.publishDataLog(id, deviceType, last5positions, eventos, nearbyVehicles);
        }
    }
}