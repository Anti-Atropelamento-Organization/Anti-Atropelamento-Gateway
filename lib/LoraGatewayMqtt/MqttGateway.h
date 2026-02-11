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

    void publishData(uint8_t id, double lat, double lng, float battery, uint8_t events[5]);

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