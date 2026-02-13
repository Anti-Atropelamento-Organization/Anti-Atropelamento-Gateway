#ifndef MQTTGATEWAY_H
#define MQTTGATEWAY_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttGateway {
public:
    MqttGateway(const char* ssid, const char* password, const char* brokerIp);
    
    void begin();
    void handle();
    bool isConnected();

    void publishData(uint8_t id, uint8_t deviceType, double lat, double lng, uint8_t battery, uint8_t status, double hdop, uint8_t events[5]);

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