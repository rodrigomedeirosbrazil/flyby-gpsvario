# Makefile - Shortcuts for PlatformIO
# Use: make <command>

.PHONY: help build upload monitor clean wokwi install test test-variometer test-wind test-all test-clean

help:
	@echo "Available commands:"
	@echo "  make build          - Build for ESP32"
	@echo "  make upload         - Upload to ESP32"
	@echo "  make monitor        - Serial monitor"
	@echo "  make clean          - Clean build"
	@echo "  make wokwi          - Build for Wokwi"
	@echo "  make install        - Install dependencies"
	@echo "  make test-all       - Run all unit tests"
	@echo "  make test-variometer - Run Variometer tests"
	@echo "  make test-wind      - Run Wind tests"
	@echo "  make flash          - Upload + Monitor"
	@echo ""
	@echo "Environments:"
	@echo "  make build-wokwi    - Build for simulation"
	@echo "  make build-esp32    - Build for hardware"

# Build
build:
	platformio run -e esp32dev

build-esp32:
	platformio run -e esp32dev

build-wokwi:
	platformio run -e wokwi

# Upload and Monitor
upload:
	platformio run -e esp32dev --target upload

monitor:
	platformio device monitor

flash: upload
	platformio device monitor

# Wokwi
wokwi: build-wokwi
	@echo "Build complete! Now start Wokwi in VS Code (F1 -> Wokwi: Start Simulator)"

# Maintenance
clean:
	platformio run --target clean
	@$(MAKE) test-clean

install:
	platformio pkg install

# Unit Tests
test-variometer:
	@echo "Running Variometer tests..."
	@cd tests && \
		g++ -c -w ../src/Variometer/Variometer.cpp Variometer.test.cpp && \
		g++ -o Variometer.test Variometer.o Variometer.test.o && \
		./Variometer.test

test-wind:
	@echo "Running Wind tests..."
	@cd tests && \
		g++ -c -w ../src/Wind/Wind.cpp Wind.test.cpp && \
		g++ -o Wind.test Wind.o Wind.test.o && \
		./Wind.test

test-all: test-variometer test-wind
	@echo ""
	@echo "All tests completed!"

test-clean:
	@rm -f tests/*.test tests/*.o

# Info
info:
	platformio device list
	@echo ""
	platformio system info

