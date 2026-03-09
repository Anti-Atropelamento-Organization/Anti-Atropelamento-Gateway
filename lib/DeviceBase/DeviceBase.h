#ifndef DEVICEBASE_H
#define DEVICEBASE_H

#include "packet.h"
#include "cmslora.h"
#include <Arduino.h>
#include "LoRaBoards.h"
#include <TinyGPS++.h>

#define MONITORING_CHANNEL 1
#define SAFETY_CHANNEL 2

// ############ Eventos ############

#define VEHICLE_TOO_CLOSE_EVENT 1
#define VEHICLE_CLOSE_EVENT 2
#define VEHICLE_AREA_EVENT 3
#define HDOP_HIGH_EVENT 4
#define LOW_BATTERY_EVENT 5
#define SATELLITE_TOO_LOW_EVENT 6
#define NO_GPS_EVENT 7

 
class DeviceBase {
public:
    /**
     *  @brief Construtor da classe DeviceBase
     */
    DeviceBase();
    virtual ~DeviceBase() {}

    /**
     *  @brief Configura o dispositivo, inicializando o módulo LoRa e o GPS
     */
    virtual void setup();

    /**
     *  @brief Alimenta os dados do GPS, precisa ser chamado frequentemente para garantir que os dados estejam atualizados
     */
    void alimentandoGPS();

    /**
     * @brief Obtém o ID do dispositivo
     */
    uint8_t getID() const;

    /**
     * @brief Define o ID do dispositivo
     * @param id O ID a ser definido para o dispositivo
     */
    void setID(uint8_t id);

    /**
     * @brief Obtém a latitude atual do dispositivo
     */

    double getLatitude() const;

    /**
     * @brief Atualiza a latitude do dispositivo com base nos dados do GPS
     */
    void setLatitude();

    /**
     * @brief Força a latitude do dispositivo para um valor específico.
     * @param lat A latitude a ser definida para o dispositivo
     */
    void forceLatitude(double lat);

    /**
     * @brief Obtém a longitude atual do dispositivo
     */
    double getLongitude() const;

    /**
     * @brief Atualiza a longitude do dispositivo com base nos dados do GPS
     */
    void setLongitude();

    /**
     * @brief Força a longitude do dispositivo para um valor específico.
     * @param lng A longitude a ser definida para o dispositivo
     */
    void forceLongitude(double lng);

    /**
     * @brief Obtém a velocidade atual do dispositivo com base no GPS
     */
    double getSpeed() const;

    /**
     * @brief Atualiza a velocidade do dispositivo com base nos dados do GPS
     */
    void setSpeed();

    /**
     * @brief Obtém o curso atual do dispositivo com base no GPS
     */
    double getCourse() const;

    /**
     * @brief Atualiza o curso do dispositivo com base nos dados do GPS
     */
    void setCourse();


    /**
     * @brief Envia um pacote de Safety com os dados atuais do dispositivo.
     */
    void sendSafety();

    /**
     * @brief Envia um pacote de Monitoramento com os dados atuais do dispositivo.
     */
    void sendMonitoring();

    /**
     * @brief Envia um pacote de Log com os dados atuais do dispositivo.
     */
    void sendLog();

    /**
     * @brief Ativa o modo de recebimento do dispositivo.
     * @return true se um pacote foi recebido com sucesso, false caso contrário.
     */
    bool receive();
    

    /**
     * @brief Verifica se o canal LoRa está ocupado antes de tentar enviar um pacote.
     * @param channel O canal a ser verificado (ex: MONITORING_CHANNEL ou SAFETY_CHANNEL)
     * @return true se o canal estiver ocupado, false se estiver livre para transmissão.
     */
    bool isChannelBusy(int channel);

    /**
     * @brief Atualiza os dados do dispositivo com base em uma string recebida via Bluetooth.
     * @param rawData A string bruta recebida via Bluetooth contendo os dados a serem atualizados.
     */
    void updateFromBluetooth(String rawData);

    /**
     * @brief Calcula a distância entre a localização atual do dispositivo e um ponto de destino especificado por latitude e longitude.
     * @param targetLat A latitude do ponto de destino.
     * @param targetLng A longitude do ponto de destino.
     * @return A distância em metros entre a localização atual do dispositivo e o ponto de destino
     */
    float calculateDistance(double targetLat, double targetLng);


    /**
     * @brief Envia um pacote de alerta para um dispositivo específico.
     * @param alertType O tipo de alerta a ser enviado. Os alertas sempre começam com ALERT_
     * @param targetID O ID do dispositivo de destino.
     */
    void sendAlert(uint8_t alertType, uint8_t targetID);

    /**
     * @brief Limpa os eventos armazenados no dispositivo.
     */
    void cleanEvents();

    /**
     * @brief Obtém o número de satélites atualmente visíveis pelo GPS do dispositivo.
     * @return O número de satélites visíveis.
     */
    int getSatValue();


    /**
     * @brief Verifica se o número de satélites visíveis é suficiente para uma localização confiável.
     * @return true se o número de satélites for suficiente, false caso contrário.
     */
    bool getSatValid();

    /**
     * @brief Atualiza o número de satélites visíveis com base nos dados do GPS.
     */
    void setSatValue();

    /**
     * @brief Obtém o valor do HDOP (Horizontal Dilution of Precision) do GPS, que indica a precisão da localização.
     * @return O valor do HDOP.
     */
    double getHdop() const;

    /**
     * @brief Atualiza o valor do HDOP com base nos dados do GPS.
     */
    void setHdop();

    /**
    * @brief Obtém o raio de segurança atual do dispositivo para um determinado índice.
    * @param index O índice do raio de segurança a ser obtido.
    * @return O valor do raio de segurança em metros.
    */
    double getRadius(int index) const;

    /**
     * @brief Calcula e atualiza os raios de segurança do dispositivo com base no valor do HDOP.
     */
    void setRadius(double hdop);

    /**
     * @brief Verifica se o dispositivo possui localização.
     * @return true se o dispositivo tiver localização atualizada, false caso contrário.
     */
    bool hasLocation();

    /**
     * @brief Obtém a latitude recebida no último pacote decodificado.
     * @return A latitude recebida.
     */
    double getReceivedLat();

    /**
     * @brief Obtém a longitude recebida no último pacote decodificado.
     * @return A longitude recebida.
     */
    double getReceivedLng();

    /**
     * @brief Obtém o ID do dispositivo contido no último pacote recebido.
     * @return O ID recebido no pacote.
     */
    uint8_t getReceivedID();

    /**
     * @brief Obtém o tipo do último pacote recebido.
     * @return O tipo do pacote recebido.
     */
    uint8_t getTypePacket();

    /**
     * @brief Obtém o identificador aleatório do último pacote recebido.
     * @return O identificador aleatório do pacote.
     */
    uint16_t getRandomPacketID();

    /**
     * @brief Obtém o identificador aleatório de monitoramento do próprio dispositivo.
     * @return O identificador de monitoramento atual.
     */
    uint16_t getMyRandomMonitoringID();

    /**
     * @brief Obtém o identificador aleatório de log do próprio dispositivo.
     * @return O identificador de log atual.
     */
    uint16_t getMyRandomLogID();

protected:

    /**
     * @brief Monta o payload do pacote de Safety.
     */
    virtual void buildSafetyPacket() = 0;

    /**
     * @brief Monta o payload do pacote de Monitoramento.
     */
    virtual void buildMonitoringPacket() = 0;

    /**
     * @brief Monta o payload do pacote de Log.
     */
    virtual void buildLogPacket() {};

    /**
     * @brief Hook chamado após decodificação de pacote recebido.
     */
    virtual void onReceiveDecoded() {}

    /**
     * @brief Define o Spreading Factor usado no envio de Safety.
     * @return Valor do SF para Safety.
     */
    virtual uint8_t safetySF() const { return 7; }

    /**
     * @brief Define o Spreading Factor usado no envio de Monitoramento.
     * @return Valor do SF para Monitoramento.
     */
    virtual uint8_t monitoringSF() const { return 9; }

protected:
    /**
     * @brief Identificador único do dispositivo.
     */
    uint8_t deviceID = 0;

    /**
     * @brief Identificador do dispositivo de destino para transmissões direcionadas.
     */
    uint8_t destId = 0;

    /**
     * @brief Latitude atual do dispositivo.
     */
    double deviceLatitude = 0.0;

    /**
     * @brief Longitude atual do dispositivo.
     */
    double deviceLongitude = 0.0;

    /**
     * @brief Nível de bateria do dispositivo em porcentagem.
     */
    uint8_t batteryLevel = 100;

    /**
     * @brief Status atual do dispositivo.
     */
    uint8_t status = 0;

    /**
     * @brief Tipo do dispositivo utilizado no protocolo.
     */
    uint8_t deviceType = 0; 

    /**
     * @brief Histórico das últimas cinco posições (latitude/longitude).
     */
    int32_t last5positions[5][2];

    /**
     * @brief Histórico dos últimos cinco eventos detectados.
     */
    uint8_t last5events[5];

    /**
     * @brief Quantidade atual de satélites visíveis.
     */
    uint8_t satelites = 0;

    /**
     * @brief Buffer do pacote de Safety a ser transmitido.
     */
    uint8_t safetyPacket[SAFETY_PACKET_SIZE];

    /**
     * @brief Buffer do pacote de Monitoramento a ser transmitido.
     */
    uint8_t monitoringPacket[MONITORING_PACKET_SIZE];

    /**
     * @brief Buffer do pacote de Log a ser transmitido.
     */
    uint8_t logPacket[LOG_PACKET_SIZE];

    /**
     * @brief Buffer bruto do último pacote recebido via LoRa.
     */
    uint8_t receivedPacket[255];

    /**
     * @brief Velocidade atual do dispositivo.
     */
    double speed = 0.0;

    /**
     * @brief Curso (heading) atual do dispositivo.
     */
    double deviceCourse = 0.0;

    /**
     * @brief Valor atual de HDOP utilizado para estimar precisão de GPS.
     */
    double deviceHdop = 0.0;

    /**
     * @brief Raios de segurança calculados para diferentes níveis de alerta.
     */
    double deviceRadius[3] = {0.0, 0.0, 0.0};

    /**
     * @brief Lista de veículos próximos monitorados pelo gateway.
     */
    ActiveVehicles nearbyVehicles[MAX_VEHICLES];

    /**
     * @brief Auxiliar para codificação e decodificação de pacotes do protocolo.
     */
    packet pckt;

    /**
     * @brief Interface de comunicação LoRa.
     */
    CMSLoRa lora;

    /**
     * @brief Instância do parser GPS.
     */
    TinyGPSPlus gps;

    /**
     * @brief Último ID do pacote recebido.
     */
    uint8_t lastPacketID;

    /**
     * @brief ID aleatório atual usado nos pacotes de monitoramento.
     */
    uint16_t monitoringRandomID;

    /**
     * @brief ID aleatório atual usado nos pacotes de log.
     */
    uint16_t LogRandomID;
};

#endif