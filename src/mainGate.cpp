#include "LoraGateway.h"
#include "SimpleTimer.h"
#include "mainFunctions.h"

LoraGateway gate;
mainFunctions MF;
SimpleTimer st_1(2000);
SimpleTimer st_2(5000);
uint8_t eventos[5] = {};
int32_t last5positions[5][2] = {};
ActiveVehicles nearbyVehicles[MAX_VEHICLES] = {};

unsigned long jitterTargetTime = 0;


void setup() {
    Serial.begin(115200);
    gate.setup();
    Serial.println("Gateway LoRa iniciado.");
    delay(2000); // Pequena pausa para garantir que tudo esteja pronto

}
void loop()
{
    //MF.SendPacketDevice(gate, st_1, st_2, jitterTargetTime); // Usando o timeout do timer como referência para o jitter
    if(gate.receive()){
    Serial.println("dados recebidos:");
        Serial.print("ID: "); Serial.println(gate.getID());
        Serial.print("Latitude: "); Serial.println(gate.getLatitude(), 6);
        Serial.print("Longitude: "); Serial.println(gate.getLongitude(), 6);
        Serial.print("Hdop: "); Serial.println(gate.getHdop(), 2);
        Serial.print("Battery: "); Serial.println(gate.getBatteryLevel());
        Serial.print("Satellites: "); Serial.println(gate.getSatellites());
        Serial.print("Status: "); Serial.println(gate.getStatus());
        gate.getLastEvents(eventos);
        Serial.print("Last 5 events: ");
        for (int i = 0; i < 5; i++) {
            Serial.print(eventos[i]);
            if (i < 4) Serial.print(", ");
        }
        Serial.println();
        Serial.print("Last 5 positions: ");
        gate.getLastPositions(last5positions);
        for (int i = 0; i < 5; i++) {
            Serial.print("(");
            Serial.print(last5positions[i][0]);
            Serial.print(", ");
            Serial.print(last5positions[i][1]);
            Serial.print(")");
            if (i < 4) Serial.print(", ");
        }
        Serial.println();
        Serial.println("Nearby Vehicles:");
        gate.getNearbyVehicles(nearbyVehicles);
        for (int i = 0; i < MAX_VEHICLES; i++) {
            if (nearbyVehicles[i].id != 0) { // Supondo que ID 0 seja inválido
                Serial.print("ID: "); Serial.print(nearbyVehicles[i].id);
                Serial.print(", Distance: "); Serial.print(nearbyVehicles[i].distance, 2);
                Serial.print("m, Last Seen: "); Serial.print(nearbyVehicles[i].lastSeenMs);
                Serial.println("ms ago");
            }
        }
    }
}