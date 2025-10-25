#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

class Config {
public:
    // Singleton pattern
    static Config& getInstance();
    
    // Main methods
    void begin();                     // Initialize and load from memory
    bool load();                      // Load configurations from ESP32
    bool save();                      // Save configurations to ESP32
    void loadDefaults();              // Restore default values
    bool isValid();                   // Verify data integrity
    
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
    Config(const Config&) = delete;   // Prevent copy
    Config& operator=(const Config&) = delete; // Prevent assignment
    
    // Control variables
    uint32_t checksum;                // For corruption verification
    uint16_t version;                 // Configuration version
    
    // The 8 configurations
    int8_t timezone;
    uint8_t takeoffSpeed;
    uint16_t pdopMaxThreshold;
    uint32_t qnh;
    bool qnhByGps;
    bool varioBeepOnlyInFlight;
    float climbRate;
    float sinkRate;
    
    // Private methods
    uint32_t calculateChecksum() const;
    bool validateChecksum() const;
    bool validateRanges() const;
};

#endif // CONFIG_H
