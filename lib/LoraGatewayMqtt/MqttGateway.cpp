#include "MqttGateway.h"

MqttGateway::MqttGateway(const char* ssid, const char* password, const char* brokerIp) 
    : ssid(ssid), password(password), brokerIp(brokerIp), client(espClient) {}

void MqttGateway::begin() {
    setupWifi();
    client.setServer(brokerIp, 1883);
}

void MqttGateway::setupWifi() {
    Serial.printf("\nConectando em %s", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado!");
}

void MqttGateway::reconnect() {
    while (!client.connected()) {
        Serial.print("Tentando conexão MQTT...");
   
        if (client.connect("Heltec_Gateway_V3")) {
            Serial.println("conectado");
            client.publish("gateway/status", "online");
        } else {
            Serial.printf("falhou, rc=%d. Tentando em 5s...\n", client.state());
            delay(5000);
        }
    }
}

void MqttGateway::handle() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}

bool MqttGateway::isConnected() {
    return client.connected();
}

void MqttGateway::publishData(uint8_t id, uint8_t deviceType, double lat, double lng, uint8_t battery, uint8_t status, double hdop, uint8_t events[5]) {
    JsonDocument doc;
    
    doc["id"] = id;
    doc["deviceType"] = deviceType;
    doc["latitude"] = serialized(String(lat, 6)); 
    doc["longitude"] = serialized(String(lng, 6));
    doc["battery"] = battery;
    doc["status"] = status;
    doc["hdop"] = hdop;
    
    JsonArray envtArray = doc["eventos"].to<JsonArray>();
    for(int i=0; i<5; i++) {
        envtArray.add(events[i]);
    }
    
    doc["timestamp"] = millis();

    char buffer[256];
    serializeJson(doc, buffer);
    
    if (client.publish("gateway/data", buffer)) {
        Serial.println();
        Serial.print("MQTT Enviado: ");
        Serial.println(buffer);
    }
}