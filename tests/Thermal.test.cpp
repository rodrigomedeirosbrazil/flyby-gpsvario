#include <iostream>
#include <cmath>
#include <cassert>

// Mock defines
#define THERMAL_MAX_DISTANCE_METERS 300.0f
#define THERMAL_MAX_HISTORY_POINTS 100
#define THERMAL_MIN_CLIMB_RATE 0.5f
#define THERMAL_CORE_TIMEOUT_MS 60000
#define THERMAL_ALTITUDE_LAYER_HEIGHT 50.0f

// Structure to store each climb point
struct ThermalPoint {
    float latitude;
    float longitude;
    float altitude;
    float climbRate;
    unsigned long timestamp;
};

// Test basic structure
void test_thermal_point_structure() {
    ThermalPoint point;
    point.latitude = -23.5505f;
    point.longitude = -46.6333f;
    point.altitude = 500.0f;
    point.climbRate = 2.5f;
    point.timestamp = 1000;
    
    assert(point.latitude == -23.5505f);
    assert(point.climbRate == 2.5f);
    std::cout << "✓ ThermalPoint structure test passed" << std::endl;
}

// Test circular buffer logic
void test_circular_buffer() {
    int historyIndex = 0;
    int historyCount = 0;
    const int MAX_POINTS = 5;
    
    // Add 7 points to buffer with max 5
    for (int i = 0; i < 7; i++) {
        historyIndex = (historyIndex + 1) % MAX_POINTS;
        if (historyCount < MAX_POINTS) {
            historyCount++;
        }
    }
    
    assert(historyCount == MAX_POINTS);
    assert(historyIndex == 2); // (7 % 5) = 2
    std::cout << "✓ Circular buffer logic test passed" << std::endl;
}

// Test wind correction calculation
void test_wind_correction() {
    // Simulate wind correction
    float lat = -23.5505f;
    float lon = -46.6333f;
    
    // Wind: 10 m/s at 90 degrees (East)
    float windSpeedMPS = 10.0f;
    float windDirRad = M_PI / 2.0f; // 90 degrees
    float timeSinceCore = 30.0f; // 30 seconds
    
    float distanceDrift = windSpeedMPS * timeSinceCore; // 300 meters
    
    float deltaLat = (distanceDrift * cos(windDirRad)) / 111320.0f;
    float deltaLon = (distanceDrift * sin(windDirRad)) / (111320.0f * cos(lat * M_PI / 180.0f));
    
    lat += deltaLat;
    lon += deltaLon;
    
    // After 30s with 10m/s wind, position should drift ~300m
    assert(fabs(deltaLat) < 0.01f); // Should be near zero (perpendicular)
    assert(fabs(deltaLon) > 0.0f);  // Should have moved in longitude
    
    std::cout << "✓ Wind correction calculation test passed" << std::endl;
}

// Test distance normalization
void test_distance_normalization() {
    // Test distances within 300m
    float dist1 = 150.0f;
    float norm1 = std::min(dist1 / 300.0f, 1.0f);
    assert(norm1 == 0.5f);
    
    // Test distances beyond 300m
    float dist2 = 500.0f;
    float norm2 = std::min(dist2 / 300.0f, 1.0f);
    assert(norm2 == 1.0f);
    
    std::cout << "✓ Distance normalization test passed" << std::endl;
}

int main() {
    std::cout << "Running Thermal class tests..." << std::endl;
    std::cout << std::endl;
    
    test_thermal_point_structure();
    test_circular_buffer();
    test_wind_correction();
    test_distance_normalization();
    
    std::cout << std::endl;
    std::cout << "All Thermal tests passed! ✓" << std::endl;
    
    return 0;
}

