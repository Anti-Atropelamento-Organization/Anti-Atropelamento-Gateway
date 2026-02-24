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

MqttGateway mqtt("TSA_CORPORATIVO", "tsatecnologia", "172.16.2.18");

void setup() {
    Serial.begin(115200);
    gate.setup();
    Serial.println("Gateway LoRa iniciado.");
    delay(2000); // Pequena pausa para garantir que tudo esteja pronto

    mqtt.begin();
    Serial.println("MQTT Gateway iniciado.");
    delay(1000);
}
void loop()
{
    //MF.SendPacketDevice(gate, st_1, st_2, jitterTargetTime); // Usando o timeout do timer como referência para o jitter
    mqtt.handle();

    if(gate.receive()){
        
        
        gate.getLastEvents(eventos);


        uint8_t id = gate.getID();
        uint16_t randomPacketID = gate.getRandomPacketID();
        gate.getTypePacket() == MONITORING_PACKET ? Serial.println("Pacote de Monitoramento recebido.") : Serial.println("Pacote de Log recebido.");
        Serial.println("Pacote recebido do ID: " + String(id) + " com RandomID: " + String(randomPacketID));

        gate.buildAck(id, randomPacketID);
        gate.sendAck();

        uint8_t deviceType = gate.getDeviceType();
        double lat = gate.getLatitude();
        double lng = gate.getLongitude();
        uint8_t battery = gate.getBatteryLevel();
        uint8_t status = gate.getStatus();
        double hdop = gate.getHdop();
        
        mqtt.publishData(id, deviceType, lat, lng, battery, status, hdop, eventos);
        gate.getLastPositions(last5positions);
    }
}