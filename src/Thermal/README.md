# Thermal

The Thermal class detects and tracks thermal cores (areas of strongest lift) during flight, providing visual guidance to help pilots locate and center thermals.

## Overview

During soaring flight, pilots search for thermals (rising columns of warm air) to gain altitude. The Thermal class analyzes climb rate data combined with GPS position to estimate where the thermal core (strongest lift) is located relative to the pilot's current position.

## Features

- **Automatic thermal core detection** based on climb rate history
- **Wind drift correction** to estimate current thermal position
- **Visual display** on the navigation compass circle
- **Smart filtering** with timeout and minimum climb rate thresholds
- **Circular buffer** for efficient memory usage (100 points max)

## How It Works

### 1. Data Collection
Every second during flight, when climbing at > 0.5 m/s, the system records:
- GPS position (latitude/longitude)
- Barometric altitude
- Climb rate (vertical speed)
- Timestamp

### 2. Core Detection
The system identifies the point with the highest climb rate in the recorded history as the thermal core location.

### 3. Wind Drift Correction
Since thermals drift downwind, the system applies a correction based on:
- Wind speed and direction
- Time elapsed since core detection
- Simple drift model: `position_now = position_recorded + (wind_vector × time)`

### 4. Visualization
The thermal core is displayed as a black dot on the compass circle:
- **Center of circle** = pilot's current position
- **Dot position** = direction and distance to thermal core
- **Circle radius** = 300 meters
- **Distances > 300m** = dot shown at circle edge

## Usage

### Initialization

The Thermal instance is created globally in `globals.cpp`:

```cpp
Thermal thermal;
```

### Automatic Operation

The `tick()` method is called automatically every second by `FlightCpu` when in flight:

```cpp
void FlightCpu::bySecondTask() {
    // ...
    if (inFlight) {
        thermal.tick();
    }
}
```

### Reading Thermal Data

```cpp
// Check if thermal core is detected
if (thermal.hasThermalCore()) {
    // Get thermal core coordinates (wind-corrected)
    float coreLat = thermal.getThermalCoreLatitude();
    float coreLon = thermal.getThermalCoreLongitude();
    
    // Get distance and bearing to core
    int distance = thermal.calcDistanceToThermalCoreInMeters();
    int bearing = thermal.calcBearingToThermalCoreInDegrees();
    
    // Get time since detection
    unsigned long age = thermal.getTimeSinceLastCore();
}

// Check if currently climbing
if (thermal.isRising()) {
    // Pilot is in lift
}
```

### Debug Information

```cpp
// Get number of recorded points
int pointCount = thermal.getHistoryCount();

// Get average climb rate of all recorded points
float avgClimbRate = thermal.getAverageClimbRate();
```

## Configuration

Constants defined in `Thermal.h`:

| Constant | Default | Description |
|----------|---------|-------------|
| `THERMAL_MAX_DISTANCE_METERS` | 300.0 | Maximum display distance (circle radius) |
| `THERMAL_MIN_CLIMB_RATE` | 0.5 | Minimum climb rate (m/s) to record point |
| `THERMAL_MAX_HISTORY_POINTS` | 100 | Maximum points in circular buffer |
| `THERMAL_CORE_TIMEOUT_MS` | 60000 | Time (ms) before thermal core expires |
| `THERMAL_ALTITUDE_LAYER_HEIGHT` | 50.0 | Layer height for altitude-based analysis |

## Algorithm Details

### Circular Buffer

Uses a circular buffer to store the last 100 climb points efficiently:
- No memory reallocation
- Oldest points automatically overwritten
- Constant memory footprint (~2KB)

### Wind Correction Formula

```cpp
time_since_core = (now - core_timestamp) / 1000.0  // seconds
wind_speed_mps = wind_speed_kmh × 0.277778
drift_distance = wind_speed_mps × time_since_core  // meters

// Convert to lat/lon delta
delta_lat = (drift_distance × cos(wind_direction)) / 111320.0
delta_lon = (drift_distance × sin(wind_direction)) / (111320.0 × cos(latitude))

corrected_position = original_position + delta
```

Where 111320 meters ≈ 1 degree of latitude (constant).

### Core Selection

Current implementation: Simple maximum
- Finds point with highest climb rate in history
- Future: May implement altitude-layered analysis

## Display Integration

The `Compass` class automatically draws the thermal core dot when GPS is available:

```cpp
void Compass::drawThermalCore() {
    if (!thermal.hasThermalCore()) return;
    
    // Calculate normalized distance (0.0 to 1.0)
    float normalizedDistance = min(distance / 300.0f, 1.0f);
    
    // Calculate relative angle (top = forward)
    float relativeAngle = bearing - heading;
    
    // Draw filled circle (2px radius) at calculated position
    display.drawDisc(pointX, pointY, 2);
}
```

## Dependencies

- **Variometer**: Provides altitude and climb rate (`getAltitude()`, `getVario()`)
- **GPS**: Provides position and validity (`getLatitude()`, `getLongitude()`, `isAvailable()`)
- **Wind**: Provides wind data for drift correction (`getSpeed()`, `getDirection()`)
- **TinyGPS**: Provides distance and bearing calculations (`distance_between()`, `course_to()`)

## Future Enhancements

### Altitude Layering
Instead of simple maximum, divide history into 50m altitude layers and find the layer with best average lift. This better handles situations where pilot climbs through multiple altitude bands.

### Smoothing
Apply moving average filter to thermal position to reduce jitter in the displayed dot.

### Confidence Score
Calculate confidence based on:
- Number of points collected
- Consistency of climb rates
- Time since detection
- Display different dot sizes/colors based on confidence

### Multiple Thermals
Detect and track multiple thermal cores simultaneously, showing the closest or strongest.

### Persistent History
Save thermal locations to SD card for post-flight analysis and thermal mapping.

## Troubleshooting

### Thermal core not detected
- Ensure GPS has valid fix (`gps.isAvailable()`)
- Verify climb rate > 0.5 m/s
- Check that device is in flight mode
- Wait for at least 3 data points to be collected

### Dot position seems wrong
- Verify wind calculation is working (`wind.isAvailable()`)
- Check GPS heading accuracy
- Confirm barometric altitude is calibrated

### Dot jumps around
- Normal behavior with low point count
- Will stabilize after more data collection
- Consider implementing smoothing filter (future enhancement)

## Testing

Unit tests are available in `tests/Thermal.test.cpp`:

```bash
cd tests
g++ -std=c++11 -o Thermal.test Thermal.test.cpp
./Thermal.test
```

Tests cover:
- ThermalPoint structure
- Circular buffer logic
- Wind correction calculations
- Distance normalization

## Example Flight Scenario

1. **Pilot enters thermal** - Climb rate increases above 0.5 m/s
2. **System starts collecting** - GPS position + climb rate recorded every second
3. **Core detected** - After 3+ points, system identifies strongest lift location
4. **Pilot circles** - Dot shows direction to core (usually center of circle)
5. **Wind drift applied** - As time passes, estimated position drifts downwind
6. **Pilot re-centers** - Follows dot indication to stay in core
7. **Thermal expires** - After 60s without new lift, core marking disappears

## Performance

- **Memory usage**: ~2KB (100 points × 20 bytes)
- **CPU impact**: Minimal (calculations only 1× per second)
- **Update rate**: 1 Hz (sufficient for thermal tracking)

## License

Part of the Flyby GPS Vario project.

