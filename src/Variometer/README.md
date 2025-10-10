# Variometer

A variometer (also known as a vertical speed indicator or rate of climb indicator) calculates the rate of altitude change based on atmospheric pressure measurements.

## Usage

### Initialization

```cpp
Variometer vario;
```

### Setting QNH (Sea Level Pressure)

```cpp
vario.setQnh(101325);
```

The QNH value should be provided in Pascals (Pa). Standard atmospheric pressure is 101325 Pa (1013.25 hPa).

### Reading Pressure

Call the `tick()` method periodically with the current pressure and timestamp:

```cpp
long pressure = sensor.readPressure() * 100;
long timestamp = millis();
vario.tick(pressure, timestamp);
```

**Important:** 
- Pressure must be in Pascals (Pa). If your sensor returns hPa, multiply by 100.
- Timestamp must be in milliseconds.
- Call `tick()` regularly (recommended: every 50-100ms) for accurate results.
- Do not call `tick()` in rapid loops without real time progression.

### Getting Vertical Speed

```cpp
float verticalSpeed = vario.getVario();
```

Returns the vertical speed in **meters per second (m/s)**.
- Positive values indicate climbing (ascending)
- Negative values indicate descending
- Zero indicates level flight

### Getting Altitude

```cpp
float altitude = vario.getAltitude();
```

Returns the current altitude in meters, calculated from the current pressure and QNH.

### Setting QNH by Known Altitude

```cpp
vario.setQnhByAltitude(500.0);
```

If you know your current altitude, you can use this method to automatically calculate and set the correct QNH value.

## Algorithm

The variometer uses a linear regression algorithm to calculate the vertical speed based on pressure changes over time. It:

1. Maintains a rolling buffer of pressure samples (averaged for noise reduction)
2. Stores the last 50 samples with their timestamps
3. Uses linear regression on the last 40 samples to calculate the rate of altitude change
4. Converts pressure changes to altitude using the barometric formula

## Units Summary

| Measurement | Unit | Notes |
|-------------|------|-------|
| Pressure (input) | Pascal (Pa) | Multiply hPa by 100 |
| QNH | Pascal (Pa) | Standard: 101325 Pa |
| Timestamp | milliseconds | Use `millis()` |
| Vertical Speed | meters/second (m/s) | Return value of `getVario()` |
| Altitude | meters | Return value of `getAltitude()` |

## Example

```cpp
#include "Variometer.h"

Variometer vario;

void setup() {
  vario.setQnh(101325);
}

void loop() {
  long pressure = readPressureFromSensor();
  vario.tick(pressure, millis());
  
  float verticalSpeed = vario.getVario();
  float altitude = vario.getAltitude();
  
  Serial.print("Vertical Speed: ");
  Serial.print(verticalSpeed);
  Serial.println(" m/s");
  
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");
  
  delay(100);
}
```

