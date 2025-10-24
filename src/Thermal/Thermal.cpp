#include <Arduino.h>
#include "Thermal.h"
#include "../globals.h"
#include "../Variometer/Variometer.h"
#include "../Gps/Gps.h"
#include "../Wind/Wind.h"
#include "../TinyGPS/TinyGPS.h"

Thermal::Thermal() {
    historyCount = 0;
    historyIndex = 0;
    thermalCoreValid = false;
    currentlyRising = false;
    thermalCoreLatitude = 0;
    thermalCoreLongitude = 0;
    thermalCoreAltitude = 0;
    thermalCoreTimestamp = 0;

    // Zero history array
    for (int i = 0; i < THERMAL_MAX_HISTORY_POINTS; i++) {
        history[i].latitude = 0;
        history[i].longitude = 0;
        history[i].altitude = 0;
        history[i].climbRate = 0;
        history[i].timestamp = 0;
    }
}

void Thermal::tick() {
    unsigned long now = millis();

    // Check thermal core timeout
    if (thermalCoreValid && (now - thermalCoreTimestamp > THERMAL_CORE_TIMEOUT_MS)) {
        thermalCoreValid = false;
    }

    // Check if we are climbing
    float vario = variometer.getVario();
    currentlyRising = (vario >= THERMAL_MIN_CLIMB_RATE);

    // Collect point only if climbing and GPS is valid
    if (!gps.isAvailable()) {
        return;
    }

    if (currentlyRising) {
        float lat = gps.getLatitude();
        float lon = gps.getLongitude();
        float alt = variometer.getAltitude();

        addPoint(lat, lon, alt, vario, now);
        calculateThermalCore();
    }
}

void Thermal::reset() {
    historyCount = 0;
    historyIndex = 0;
    thermalCoreValid = false;
    currentlyRising = false;
}

bool Thermal::isRising() {
    return currentlyRising;
}

float Thermal::getThermalCoreLatitude() {
    if (!thermalCoreValid) {
        return 0.0f;
    }

    float lat = thermalCoreLatitude;
    float lon = thermalCoreLongitude;
    applyWindCorrection(lat, lon);

    return lat;
}

float Thermal::getThermalCoreLongitude() {
    if (!thermalCoreValid) {
        return 0.0f;
    }

    float lat = thermalCoreLatitude;
    float lon = thermalCoreLongitude;
    applyWindCorrection(lat, lon);

    return lon;
}

int Thermal::calcDistanceToThermalCoreInMeters() {
    if (!thermalCoreValid || !gps.isAvailable()) {
        return 0;
    }

    float coreLat = getThermalCoreLatitude();
    float coreLon = getThermalCoreLongitude();
    float currentLat = gps.getLatitude();
    float currentLon = gps.getLongitude();

    float distance = TinyGPS::distance_between(currentLat, currentLon, coreLat, coreLon);

    return (int)distance;
}

int Thermal::calcBearingToThermalCoreInDegrees() {
    if (!thermalCoreValid || !gps.isAvailable()) {
        return 0;
    }

    float coreLat = getThermalCoreLatitude();
    float coreLon = getThermalCoreLongitude();
    float currentLat = gps.getLatitude();
    float currentLon = gps.getLongitude();

    float bearing = TinyGPS::course_to(currentLat, currentLon, coreLat, coreLon);

    return (int)bearing;
}

unsigned long Thermal::getTimeSinceLastCore() {
    if (!thermalCoreValid) {
        return 0;
    }

    return millis() - thermalCoreTimestamp;
}

int Thermal::getHistoryCount() {
    return historyCount;
}

float Thermal::getAverageClimbRate() {
    return calculateAverageClimbRate();
}

bool Thermal::hasThermalCore() {
    return thermalCoreValid;
}

// Private methods

void Thermal::addPoint(float lat, float lon, float alt, float climbRate, unsigned long now) {
    // Add point to circular buffer
    history[historyIndex].latitude = lat;
    history[historyIndex].longitude = lon;
    history[historyIndex].altitude = alt;
    history[historyIndex].climbRate = climbRate;
    history[historyIndex].timestamp = now;

    // Advance circular index
    historyIndex = (historyIndex + 1) % THERMAL_MAX_HISTORY_POINTS;

    // Update count (max is THERMAL_MAX_HISTORY_POINTS)
    if (historyCount < THERMAL_MAX_HISTORY_POINTS) {
        historyCount++;
    }
}

void Thermal::calculateThermalCore() {
    if (historyCount < 3) {
        return;  // Minimum points required
    }

    ThermalPoint bestPoint = findBestLiftPoint();

    thermalCoreLatitude = bestPoint.latitude;
    thermalCoreLongitude = bestPoint.longitude;
    thermalCoreAltitude = bestPoint.altitude;
    thermalCoreTimestamp = bestPoint.timestamp;
    thermalCoreValid = true;
}

ThermalPoint Thermal::findBestLiftPoint() {
    ThermalPoint best = history[0];

    for (int i = 0; i < historyCount; i++) {
        if (history[i].climbRate > best.climbRate) {
            best = history[i];
        }
    }

    return best;
}

void Thermal::applyWindCorrection(float &lat, float &lon) {
    if (!wind.isAvailable()) {
        return;  // No wind, no correction
    }

    unsigned long now = millis();
    float timeSinceCore = (now - thermalCoreTimestamp) / 1000.0f;

    // Convert speed from km/h to m/s
    float windSpeedMPS = wind.getSpeed() * 0.277778f;
    float distanceDrift = windSpeedMPS * timeSinceCore;

    // Calculate displacement in degrees
    float windDirRad = radians((float)wind.getDirection());

    // 1 degree lat ≈ 111320 meters
    float deltaLat = (distanceDrift * cos(windDirRad)) / 111320.0f;

    // 1 degree lon depends on latitude
    float deltaLon = (distanceDrift * sin(windDirRad)) /
                     (111320.0f * cos(radians(lat)));

    lat += deltaLat;
    lon += deltaLon;
}

float Thermal::calculateAverageClimbRate() {
    if (historyCount == 0) {
        return 0.0f;
    }

    float sum = 0.0f;
    for (int i = 0; i < historyCount; i++) {
        sum += history[i].climbRate;
    }

    return sum / historyCount;
}

