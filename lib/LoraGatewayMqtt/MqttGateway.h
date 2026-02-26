#ifndef MQTTGATEWAY_H
#define MQTTGATEWAY_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "../packet/packet.h"

class MqttGateway {
public:
    MqttGateway(const char* ssid, const char* password, const char* brokerIp);
    
    void begin();
    void handle();
    bool isConnected();

    void publishDataMonitoring(uint8_t id, uint8_t deviceType, double lat, double lng, uint8_t battery, uint8_t status, double hdop);
    void publishDataLog(uint8_t id, uint8_t deviceType,int32_t lastPositions[5][2] ,uint8_t events[5], ActiveVehicles nearbyVehicles[MAX_VEHICLES]);

private:
    const char* ssid;   
    const char* password;
    const char* brokerIp;
    
    WiFiClient espClient;
    PubSubClient client;

    void setupWifi();
    void reconnect();
};

#endif