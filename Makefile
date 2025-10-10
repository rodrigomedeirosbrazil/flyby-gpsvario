# Makefile - Atalhos para PlatformIO
# Use: make <comando>

.PHONY: help build upload monitor clean wokwi install test

help:
	@echo "Comandos disponíveis:"
	@echo "  make build          - Compilar para ESP32"
	@echo "  make upload         - Upload para ESP32"
	@echo "  make monitor        - Monitor serial"
	@echo "  make clean          - Limpar build"
	@echo "  make wokwi          - Compilar para Wokwi"
	@echo "  make install        - Instalar dependências"
	@echo "  make test           - Executar testes"
	@echo "  make flash          - Upload + Monitor"
	@echo ""
	@echo "Ambientes:"
	@echo "  make build-wokwi    - Build para simulação"
	@echo "  make build-esp32    - Build para hardware"

# Compilação
build:
	platformio run -e esp32dev

build-esp32:
	platformio run -e esp32dev

build-wokwi:
	platformio run -e wokwi

# Upload e Monitor
upload:
	platformio run -e esp32dev --target upload

monitor:
	platformio device monitor

flash: upload
	platformio device monitor

# Wokwi
wokwi: build-wokwi
	@echo "Build concluído! Agora inicie o Wokwi no VS Code (F1 -> Wokwi: Start Simulator)"

# Manutenção
clean:
	platformio run --target clean

install:
	platformio pkg install

# Testes
test:
	platformio test

# Info
info:
	platformio device list
	@echo ""
	platformio system info

