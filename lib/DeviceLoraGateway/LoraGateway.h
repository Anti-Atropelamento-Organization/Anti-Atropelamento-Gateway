#ifndef LORAGATEWAY_H
#define LORAGATEWAY_H

#include "DeviceBase.h"

class LoraGateway : public DeviceBase {
public:
    LoraGateway();
    void setup() override;
    void buildSafetyPacket() override;
    void buildMonitoringPacket() override;

    uint8_t getID();
    uint8_t getDeviceType();
    double getLatitude();
    double getLongitude();
    uint8_t getBatteryLevel();
    void getLastPositions(int32_t (&positions)[5][2]);
    void getLastEvents(uint8_t (&events)[5]);
    void getNearbyVehicles(ActiveVehicles (&vehicles)[MAX_VEHICLES]);
    uint8_t getStatus();
    uint8_t getSatellites();
    double getHdop();
    uint16_t getRandomPacketID();
    void sendAck();
    void buildAck(uint8_t targetID, uint16_t packetID);
};

#endif