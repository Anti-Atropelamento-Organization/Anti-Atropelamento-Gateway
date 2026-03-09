#ifndef LORAGATEWAY_H
#define LORAGATEWAY_H

#include "DeviceBase.h"

/**
 * @brief Implementação de gateway LoRa baseada em DeviceBase.
 */
class LoraGateway : public DeviceBase {
public:
    /**
     * @brief Construtor da classe LoraGateway.
     */
    LoraGateway();

    /**
     * @brief Configura o gateway e inicializa recursos necessários.
     */
    void setup() override;

    /**
     * @brief Monta o payload do pacote de Safety do gateway.
     */
    void buildSafetyPacket() override;

    /**
     * @brief Monta o payload do pacote de Monitoramento do gateway.
     */
    void buildMonitoringPacket() override;

    /**
     * @brief Obtém o ID do último pacote recebido.
     * @return ID do último pacote recebido.
     */
    uint8_t getID();

    /**
     * @brief Obtém o tipo de dispositivo do último pacote recebido.
     * @return Tipo do dispositivo.
     */
    uint8_t getDeviceType();

    /**
     * @brief Obtém a latitude do último pacote recebido.
     * @return Latitude atual.
     */
    double getLatitude();

    /**
     * @brief Obtém a longitude do último pacote recebido.
     * @return Longitude atual.
     */
    double getLongitude();

    /**
     * @brief Obtém o nível de bateria atual do último pacote recebido.
     * @return Nível de bateria em porcentagem.
     */
    uint8_t getBatteryLevel();

    /**
     * @brief Copia o histórico das últimas posições registradas.
     * @param positions Referência para matriz de saída com as posições.
     */
    void getLastPositions(int32_t (&positions)[5][2]);

    /**
     * @brief Copia o histórico dos últimos eventos detectados.
     * @param events Referência para vetor de saída com os eventos.
     */
    void getLastEvents(uint8_t (&events)[5]);

    /**
     * @brief Obtém a lista de veículos próximos do último dispositivo que enviou o pacote.
     * @param vehicles Referência para vetor de saída com os veículos próximos.
     */
    void getNearbyVehicles(ActiveVehicles (&vehicles)[MAX_VEHICLES]);

    /**
     * @brief Obtém o status do último pacote recebido.
     * @return Status atual do dispositivo.
     */
    uint8_t getStatus();

    /**
     * @brief Obtém a quantidade de satélites visíveis.
     * @return Número de satélites visíveis.
     */
    uint8_t getSatellites();

    /**
     * @brief Obtém o valor atual de HDOP do último pacote recebido.
     * @return Valor de HDOP.
     */
    double getHdop();

    /**
     * @brief Buffer do pacote ACK a ser transmitido.
     */
    uint8_t ackPacket[ACK_PACKET_SIZE];
    
    /**
     * @brief Envia o pacote ACK montado no buffer interno.
     */
    void sendAck();

    /**
     * @brief Monta um pacote ACK para um dispositivo e pacote específicos.
     * @param targetID ID do dispositivo de destino do ACK.
     * @param packetID ID do pacote que está sendo confirmado.
     */
    void buildAck(uint8_t targetID, uint16_t packetID);
};

#endif