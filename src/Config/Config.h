#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

class Config {
public:
    // Singleton pattern
    static Config& getInstance();
    
    // Métodos principais
    void begin();                     // Inicializa e carrega da memória
    bool load();                      // Carrega configurações do ESP32
    bool save();                      // Salva configurações no ESP32
    void loadDefaults();              // Restaura valores padrão
    bool isValid();                   // Verifica integridade dos dados
    
    // Getters
    int8_t getTimezone() const;
    uint8_t getTakeoffSpeed() const;
    uint16_t getPdopMaxThreshold() const;
    uint32_t getQnh() const;
    bool getQnhByGps() const;
    bool getVarioBeepOnlyInFlight() const;
    float getClimbRate() const;
    float getSinkRate() const;
    
    // Setters
    void setTimezone(int8_t value);
    void setTakeoffSpeed(uint8_t value);
    void setPdopMaxThreshold(uint16_t value);
    void setQnh(uint32_t value);
    void setQnhByGps(bool value);
    void setVarioBeepOnlyInFlight(bool value);
    void setClimbRate(float value);
    void setSinkRate(float value);
    
private:
    Config();                         // Singleton
    Config(const Config&) = delete;   // Previne cópia
    Config& operator=(const Config&) = delete; // Previne atribuição
    
    // Variáveis de controle
    uint32_t checksum;                // Para verificar corrupção
    uint16_t version;                 // Versão da config
    
    // As 8 configurações
    int8_t timezone;
    uint8_t takeoffSpeed;
    uint16_t pdopMaxThreshold;
    uint32_t qnh;
    bool qnhByGps;
    bool varioBeepOnlyInFlight;
    float climbRate;
    float sinkRate;
    
    // Métodos privados
    uint32_t calculateChecksum() const;
    bool validateChecksum() const;
    bool validateRanges() const;
};

#endif // CONFIG_H
