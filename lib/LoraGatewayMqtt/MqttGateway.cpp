#include "MqttGateway.h"


MqttGateway::MqttGateway(const char* ssid, const char* password, const char* brokerIp) 
    : ssid(ssid), password(password), brokerIp(brokerIp), client(espClient) {}

void MqttGateway::begin() {
    setupWifi();
    client.setServer(brokerIp, 1883);
    client.setBufferSize(1024); // Aumenta o buffer para permitir payloads maiores
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

void MqttGateway::publishDataMonitoring(uint8_t id, uint8_t deviceType, double lat, double lng, uint8_t battery, uint8_t status, double hdop) {
    JsonDocument doc;
    
    doc["id"] = id;
    doc["deviceType"] = deviceType;
    doc["latitude"] = serialized(String(lat, 6)); 
    doc["longitude"] = serialized(String(lng, 6));
    doc["battery"] = battery;
    doc["status"] = status;
    doc["hdop"] = hdop;
    
    doc["timestamp"] = millis();

    char buffer[256];
    serializeJson(doc, buffer);
    
    if (client.publish("gateway/data", buffer)) {
        Serial.println();
        Serial.print("MQTT Monitoring Enviado");
    }
}

void MqttGateway::publishDataLog(uint8_t id, uint8_t deviceType, int32_t lastPositions[5][2], uint8_t events[5], ActiveVehicles nearbyVehicles[MAX_VEHICLES]) {

    JsonDocument doc; 

    doc["id"] = id;
    doc["deviceType"] = deviceType;

    JsonArray positionsArray = doc["lastPositions"].to<JsonArray>();
    for (int i = 0; i < 5; i++) {
        JsonArray pos = positionsArray.add<JsonArray>();
        pos.add(lastPositions[i][0]);
        pos.add(lastPositions[i][1]);
    }

    JsonArray eventsArray = doc["events"].to<JsonArray>();
    for (int i = 0; i < 5; i++) {
        eventsArray.add(events[i]);
    }

    JsonArray vehiclesArray = doc["nearbyVehicles"].to<JsonArray>();
    for (int i = 0; i < MAX_VEHICLES; i++) {
        // Só adiciona se o veículo for válido (ex: id diferente de 0) para economizar espaço
        if(nearbyVehicles[i].id != 0) { 
            JsonObject veh = vehiclesArray.add<JsonObject>();
            veh["id"] = nearbyVehicles[i].id;
            veh["dist"] = nearbyVehicles[i].distance; // nomes curtos economizam bytes
            veh["seen"] = nearbyVehicles[i].lastSeenMs;
        }
    }

    doc["ts"] = millis();


    char buffer[1024]; 
    serializeJson(doc, buffer);

    if (client.publish("gateway/log", buffer)) {
        Serial.println("\nMQTT Log Enviado com sucesso!");
    } else {
        Serial.println("\nFalha ao enviar MQTT Log - Payload muito grande ou sem conexão");
    }
}