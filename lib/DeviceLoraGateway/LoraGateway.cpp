#include "LoraGateway.h"

LoraGateway::LoraGateway() : DeviceBase() {
    deviceType = 3;
}

void LoraGateway::buildSafetyPacket() {
    // O gateway não envia pacotes de segurança, então deixamos vazio
}

void LoraGateway::buildMonitoringPacket() {
    // O gateway não envia pacotes de monitoramento, então deixamos vazio
}

void LoraGateway::setup()
{
    lora.begin();
    lora.SpreadingFactor(9);
    lora.StartReceive();
    // lora.receiveData(receivedPacket, 0, 0);
}
uint8_t LoraGateway::getID()
{
    return pckt.getDeviceID();
}
uint8_t LoraGateway::getDeviceType()
{
    return pckt.getDeviceType();
}
double LoraGateway::getLatitude()
{
    return pckt.getLat();
}
double LoraGateway::getLongitude()
{
    return pckt.getLng();
}
uint8_t LoraGateway::getBatteryLevel()
{
    return 0;
}
void LoraGateway::getLastPositions(int32_t (&positions)[5][2])
{
    pckt.getLast5Positions(positions);
}
void LoraGateway::getLastEvents(uint8_t (&events)[5])
{
    pckt.getLast5Events(events);
}
void LoraGateway::getNearbyVehicles(ActiveVehicles (&vehicles)[MAX_VEHICLES])
{
    pckt.getNearbyVehicles(vehicles);
}
uint8_t LoraGateway::getStatus()
{
    return pckt.getStatus();
}
uint8_t LoraGateway::getSatellites()
{
    return pckt.getSatellites();
}
double LoraGateway::getHdop()
{
    return pckt.getHdop();
}


void LoraGateway::sendAck() {
    Serial.println("[LoraGateway] Enviando ACK...");
    lora.sendData(ackPacket, ACK_PACKET_SIZE);
}

void LoraGateway::buildAck(uint8_t targetID, uint16_t packetID) {
    pckt.ackPacket(targetID, packetID, ackPacket);
}



