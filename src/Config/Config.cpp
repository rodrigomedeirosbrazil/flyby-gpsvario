#include "Config.h"
#include <Preferences.h>

// Chaves para armazenamento no Preferences
static const char* NAMESPACE = "flyby_config";
static const uint16_t CONFIG_VERSION = 1;

// Chaves individuais para cada configuração
static const char* KEY_VERSION = "version";
static const char* KEY_CHECKSUM = "checksum";
static const char* KEY_TIMEZONE = "timezone";
static const char* KEY_TAKEOFF_SPEED = "takeoff_speed";
static const char* KEY_PDOP_MAX_THRESHOLD = "pdop_max_threshold";
static const char* KEY_QNH = "qnh";
static const char* KEY_QNH_BY_GPS = "qnh_by_gps";
static const char* KEY_VARIO_BEEP_ONLY_IN_FLIGHT = "vario_beep_only_in_flight";
static const char* KEY_CLIMB_RATE = "climb_rate";
static const char* KEY_SINK_RATE = "sink_rate";

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

Config::Config() {
    // Inicializar com valores padrão
    loadDefaults();
}

void Config::begin() {
    // Tentar carregar da memória, se falhar usar defaults
    if (!load()) {
        loadDefaults();
        save(); // Salvar os defaults
    }
}

void Config::loadDefaults() {
    version = CONFIG_VERSION;
    timezone = -3;
    takeoffSpeed = 6;
    pdopMaxThreshold = 220;
    qnh = 101325;
    qnhByGps = true;
    varioBeepOnlyInFlight = true;
    climbRate = 0.1f;
    sinkRate = -2.0f;
    
    // Calcular checksum dos valores padrão
    checksum = calculateChecksum();
}

bool Config::load() {
    Preferences prefs;
    if (!prefs.begin(NAMESPACE, true)) { // true = read-only
        return false;
    }
    
    // Carregar versão e checksum
    version = prefs.getUShort(KEY_VERSION, 0);
    checksum = prefs.getULong(KEY_CHECKSUM, 0);
    
    // Se versão não corresponder, usar defaults
    if (version != CONFIG_VERSION) {
        prefs.end();
        return false;
    }
    
    // Carregar configurações
    timezone = prefs.getChar(KEY_TIMEZONE, -3);
    takeoffSpeed = prefs.getUChar(KEY_TAKEOFF_SPEED, 6);
    pdopMaxThreshold = prefs.getUShort(KEY_PDOP_MAX_THRESHOLD, 220);
    qnh = prefs.getULong(KEY_QNH, 101325);
    qnhByGps = prefs.getBool(KEY_QNH_BY_GPS, true);
    varioBeepOnlyInFlight = prefs.getBool(KEY_VARIO_BEEP_ONLY_IN_FLIGHT, true);
    climbRate = prefs.getFloat(KEY_CLIMB_RATE, 0.1f);
    sinkRate = prefs.getFloat(KEY_SINK_RATE, -2.0f);
    
    prefs.end();
    
    // Validar integridade
    return isValid();
}

bool Config::save() {
    Preferences prefs;
    if (!prefs.begin(NAMESPACE, false)) { // false = read-write
        return false;
    }
    
    // Calcular checksum atual
    checksum = calculateChecksum();
    
    // Salvar versão e checksum
    prefs.putUShort(KEY_VERSION, version);
    prefs.putULong(KEY_CHECKSUM, checksum);
    
    // Salvar configurações
    prefs.putChar(KEY_TIMEZONE, timezone);
    prefs.putUChar(KEY_TAKEOFF_SPEED, takeoffSpeed);
    prefs.putUShort(KEY_PDOP_MAX_THRESHOLD, pdopMaxThreshold);
    prefs.putULong(KEY_QNH, qnh);
    prefs.putBool(KEY_QNH_BY_GPS, qnhByGps);
    prefs.putBool(KEY_VARIO_BEEP_ONLY_IN_FLIGHT, varioBeepOnlyInFlight);
    prefs.putFloat(KEY_CLIMB_RATE, climbRate);
    prefs.putFloat(KEY_SINK_RATE, sinkRate);
    
    prefs.end();
    return true;
}

bool Config::isValid() {
    return validateChecksum() && validateRanges();
}

uint32_t Config::calculateChecksum() const {
    // CRC32 simples baseado nos dados das configurações
    uint32_t crc = 0xFFFFFFFF;
    
    // Incluir todas as configurações no cálculo do checksum
    uint8_t* data = (uint8_t*)&timezone;
    for (int i = 0; i < sizeof(timezone); i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    
    data = (uint8_t*)&takeoffSpeed;
    for (int i = 0; i < sizeof(takeoffSpeed); i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    
    data = (uint8_t*)&pdopMaxThreshold;
    for (int i = 0; i < sizeof(pdopMaxThreshold); i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    
    data = (uint8_t*)&qnh;
    for (int i = 0; i < sizeof(qnh); i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    
    data = (uint8_t*)&qnhByGps;
    for (int i = 0; i < sizeof(qnhByGps); i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    
    data = (uint8_t*)&varioBeepOnlyInFlight;
    for (int i = 0; i < sizeof(varioBeepOnlyInFlight); i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    
    data = (uint8_t*)&climbRate;
    for (int i = 0; i < sizeof(climbRate); i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    
    data = (uint8_t*)&sinkRate;
    for (int i = 0; i < sizeof(sinkRate); i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    
    return ~crc;
}

bool Config::validateChecksum() const {
    return checksum == calculateChecksum();
}

bool Config::validateRanges() const {
    return (timezone >= -12 && timezone <= 14) &&           // Fuso horário válido
           (takeoffSpeed >= 3 && takeoffSpeed <= 15) &&     // Velocidade de decolagem razoável
           (pdopMaxThreshold >= 50 && pdopMaxThreshold <= 1000) && // PDOP válido
           (qnh >= 95000 && qnh <= 105000) &&               // QNH válido (Pa)
           (climbRate >= 0.0f && climbRate <= 5.0f) &&     // Taxa de subida válida
           (sinkRate >= -10.0f && sinkRate <= 0.0f);        // Taxa de descida válida
}

// Getters
int8_t Config::getTimezone() const { return timezone; }
uint8_t Config::getTakeoffSpeed() const { return takeoffSpeed; }
uint16_t Config::getPdopMaxThreshold() const { return pdopMaxThreshold; }
uint32_t Config::getQnh() const { return qnh; }
bool Config::getQnhByGps() const { return qnhByGps; }
bool Config::getVarioBeepOnlyInFlight() const { return varioBeepOnlyInFlight; }
float Config::getClimbRate() const { return climbRate; }
float Config::getSinkRate() const { return sinkRate; }

// Setters
void Config::setTimezone(int8_t value) { 
    if (value >= -12 && value <= 14) {
        timezone = value; 
    }
}
void Config::setTakeoffSpeed(uint8_t value) { 
    if (value >= 3 && value <= 15) {
        takeoffSpeed = value; 
    }
}
void Config::setPdopMaxThreshold(uint16_t value) { 
    if (value >= 50 && value <= 1000) {
        pdopMaxThreshold = value; 
    }
}
void Config::setQnh(uint32_t value) { 
    if (value >= 95000 && value <= 105000) {
        qnh = value; 
    }
}
void Config::setQnhByGps(bool value) { qnhByGps = value; }
void Config::setVarioBeepOnlyInFlight(bool value) { varioBeepOnlyInFlight = value; }
void Config::setClimbRate(float value) { 
    if (value >= 0.0f && value <= 5.0f) {
        climbRate = value; 
    }
}
void Config::setSinkRate(float value) { 
    if (value >= -10.0f && value <= 0.0f) {
        sinkRate = value; 
    }
}
