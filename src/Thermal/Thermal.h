#ifndef THERMAL_H
#define THERMAL_H

#include "../defines.h"
#include "../TinyGPS/TinyGPS.h"

// Algorithm configuration
#define THERMAL_MAX_DISTANCE_METERS 300.0f
#define THERMAL_ALTITUDE_LAYER_HEIGHT 50.0f
#define THERMAL_MAX_HISTORY_POINTS 100
#define THERMAL_MIN_CLIMB_RATE 0.5f  // m/s minimum to consider "climbing"
#define THERMAL_CORE_TIMEOUT_MS 60000  // 60 seconds

// Structure to store each climb point
struct ThermalPoint {
    float latitude;
    float longitude;
    float altitude;
    float climbRate;  // vario in m/s
    unsigned long timestamp;
};

class Thermal
{
    public:
        Thermal();
        void tick();  // Called every second
        void reset();  // Clear history
        
        // Main getters
        bool isRising();
        float getThermalCoreLatitude();
        float getThermalCoreLongitude();
        int calcDistanceToThermalCoreInMeters();
        int calcBearingToThermalCoreInDegrees();
        unsigned long getTimeSinceLastCore();  // ms since last core recording
        
        // Debug/auxiliary getters
        int getHistoryCount();
        float getAverageClimbRate();
        bool hasThermalCore();
        
    private:
        // Point history
        ThermalPoint history[THERMAL_MAX_HISTORY_POINTS];
        int historyCount;
        int historyIndex;  // circular index
        
        // Calculated thermal core
        float thermalCoreLatitude;
        float thermalCoreLongitude;
        float thermalCoreAltitude;
        unsigned long thermalCoreTimestamp;
        bool thermalCoreValid;
        
        // Current state
        bool currentlyRising;
        
        // Private methods
        void addPoint(float lat, float lon, float alt, float climbRate, unsigned long now);
        void calculateThermalCore();
        void applyWindCorrection(float &lat, float &lon);
        ThermalPoint findBestLiftPoint();
        float calculateAverageClimbRate();
};

#endif

