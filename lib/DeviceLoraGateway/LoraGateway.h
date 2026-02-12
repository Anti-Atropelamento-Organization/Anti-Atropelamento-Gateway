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
    int32_t (*getLast5Positions())[2];
    void getLast5Events(uint8_t (&events)[5]);
    uint8_t getStatus();
    uint8_t getSatellites();
    double getHdop();
};

#endif