# Flyby GPS Vario

## Description
Flyby GPS Vario is an electronic device designed for the world of free flight, such as paragliding and paramotoring. Built on the Arduino platform in C++ for the ESP32 microcontroller, it provides essential flight information including vertical speed (vario), GPS data, and a custom algorithm to detect wind speed and direction. The project is open-source and aims to be a reliable, extensible flight instrument for enthusiasts and developers alike.

## Features
- **Vertical Speed (Vario):** Real-time climb/sink rate using a barometric sensor.
- **GPS Integration:** Provides position, speed, altitude, heading, and satellite data.
- **Custom Wind Algorithm:** Calculates wind speed and direction using GPS data and a unique algorithm developed by the author.
- **Flight Time Tracking:** Automatically detects takeoff and landing to track flight duration.
- **Audio Feedback:** Buzzer for climb/sink tones and status sounds.
- **OLED/LCD Display:** Shows flight data, info boxes, and graphical compass.
- **Compass Integration:** Displays heading and wind direction.
- **Auto QNH Adjustment:** Adjusts barometric reference using GPS altitude.

## Hardware Requirements
- **ESP32 DevKit V1** (or compatible)
- **Barometric Sensor** (e.g., BMP085)
- **GPS Module** (connected via UART)
- **128x64 OLED or LCD Display** (SSD1306 or ST7567/ST7565, configurable)
- **Buzzer** (for audio feedback)
- **Wiring Example:**
  - Display SCL → ESP32 D22
  - Display SDA → ESP32 D21
  - Buzzer → ESP32 D14 (or D18 in simulation)
  - GPS TX/RX → ESP32 D17/D16
  - Power: 3.3V and GND

See `diagram.json` for a sample wiring diagram (Wokwi simulator compatible).

## Installation & Setup
1. **Clone the Repository:**
   ```sh
   git clone https://github.com/yourusername/flyby-gpsvario.git
   ```
2. **Using PlatformIO (Recommended):**
   - Install [PlatformIO](https://platformio.org/) (VS Code extension or CLI)
   - Open the project folder in PlatformIO
   - PlatformIO will automatically install all required libraries
   - Build the project: `pio run`
   - Upload to ESP32: `pio run --target upload`
   - Monitor serial output: `pio device monitor`

3. **Alternative - Arduino IDE:**
   - Select the ESP32 Dev Module board
   - Install required libraries: `Adafruit_BMP085`, `U8g2lib`
   - Rename `src/main.cpp` to `flyby-gpsvario.ino` and move to root
   - Adjust include paths in the main file

4. **Configure Pins (if needed):**
   - Adjust pin definitions in `src/defines.h` for your hardware.

## PlatformIO Environments
- `esp32dev` - Default environment for physical ESP32 hardware
- `wokwi` - Environment for Wokwi simulation with WOKWI flag enabled

## Usage
- On power-up, the device initializes sensors and displays the main screen.
- The display shows vario, GPS data, wind speed/direction, and flight time.
- Audio tones indicate climb/sink rates.
- The device automatically detects takeoff and landing based on GPS speed.
- Wind data is updated in real-time using the custom algorithm.

## Testing
The project includes unit tests for core algorithms (Variometer and Wind calculations).

### Running Tests
You can run tests using the Makefile shortcuts (requires g++):

```sh
# Run all tests
make test-all

# Run individual test suites
make test-variometer
make test-wind

# Clean test artifacts
make test-clean
```

### Manual Test Execution
Alternatively, you can run tests manually:

```sh
# Variometer tests
cd tests
g++ -c -w ../src/Variometer/Variometer.cpp Variometer.test.cpp
g++ -o Variometer.test Variometer.o Variometer.test.o
./Variometer.test

# Wind tests
g++ -c -w ../src/Wind/Wind.cpp Wind.test.cpp
g++ -o Wind.test Wind.o Wind.test.o
./Wind.test
```

### Test Suites
- **Variometer Tests**: Validates climb/sink rate calculations and QNH adjustments
- **Wind Tests**: Validates wind speed and direction algorithm for different wind scenarios (N, S, E, SSE)

## Custom Wind Algorithm
This project features a unique algorithm to estimate wind speed and direction in flight:
- **Data Collection:** GPS heading and speed are stored in 16 cardinal directions.
- **Calculation:** The algorithm compares the maximum and minimum speeds in opposite directions to estimate wind speed and direction.
- **Logic:**
  - If the difference between opposite headings is significant and recent, wind speed is calculated as the difference, and direction is set accordingly.
- **Result:** Provides real-time wind estimation without dedicated wind sensors, ideal for paragliding and paramotoring.

## Contributing
Contributions, bug reports, and feature requests are welcome! Please open an issue or submit a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.