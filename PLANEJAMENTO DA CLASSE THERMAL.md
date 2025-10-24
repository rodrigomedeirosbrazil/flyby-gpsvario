# 📋 PLANEJAMENTO DA CLASSE THERMAL

## 🎯 Objetivo
Criar uma classe que identifica e rastreia a posição do **núcleo térmico** (thermal core) em relação ao piloto durante o voo, permitindo visualização em um círculo de navegação.

---

## 📊 Análise do Sistema Existente

### Estrutura do Projeto
- **Arquitetura**: Classes modulares com globals.h exportando instâncias
- **Loop Principal**: `FlightCpu::tick()` orquestra todas as chamadas
- **Tarefas por Segundo**: `FlightCpu::bySecondTask()` executa tarefas não críticas
- **Padrão de Design**: Classes com métodos `tick()`, `begin()`, getters específicos

### Classes Relacionadas
1. **Variometer**: Fornece altitude e taxa de subida (vario em m/s)
2. **Gps**: Fornece lat/lon, velocidade, heading
3. **Wind**: Calcula direção e velocidade do vento
4. **Compass**: Desenha círculo de navegação (raio = 27 pixels)
5. **TinyGPS**: Possui métodos estáticos `distance_between()` e `course_to()`

---

## 🏗️ Estrutura da Classe Thermal

### Localização dos Arquivos
```
src/Thermal/
├── Thermal.h
├── Thermal.cpp
```

### Definição do Header (Thermal.h)

```cpp
#ifndef THERMAL_H
#define THERMAL_H

#include "../defines.h"
#include "../TinyGPS/TinyGPS.h"

// Configurações do algoritmo
#define THERMAL_MAX_DISTANCE_METERS 300.0f
#define THERMAL_ALTITUDE_LAYER_HEIGHT 50.0f
#define THERMAL_MAX_HISTORY_POINTS 100
#define THERMAL_MIN_CLIMB_RATE 0.5f  // m/s mínimo para considerar "subindo"
#define THERMAL_CORE_TIMEOUT_MS 60000  // 60 segundos

// Estrutura para armazenar cada ponto de subida
struct ThermalPoint {
    float latitude;
    float longitude;
    float altitude;
    float climbRate;  // vario em m/s
    unsigned long timestamp;
};

class Thermal
{
    public:
        Thermal();
        void tick();  // Chamado a cada segundo
        void reset();  // Limpa histórico

        // Getters principais
        bool isRising();
        float getThermalCoreLatitude();
        float getThermalCoreLongitude();
        int calcDistanceToThermalCoreInMeters();
        int calcBearingToThermalCoreInDegrees();
        unsigned long getTimeSinceLastCore();  // ms desde última gravação

        // Getters auxiliares para debug
        int getHistoryCount();
        float getAverageClimbRate();
        bool hasThermalCore();

    private:
        // Histórico de pontos
        ThermalPoint history[THERMAL_MAX_HISTORY_POINTS];
        int historyCount;
        int historyIndex;  // índice circular

        // Núcleo térmico calculado
        float thermalCoreLatitude;
        float thermalCoreLongitude;
        float thermalCoreAltitude;
        unsigned long thermalCoreTimestamp;
        bool thermalCoreValid;

        // Estado atual
        bool currentlyRising;

        // Métodos privados
        void addPoint(float lat, float lon, float alt, float climbRate, unsigned long now);
        void calculateThermalCore();
        void applyWindCorrection(float &lat, float &lon);
        ThermalPoint findBestLiftPoint();
        float calculateAverageClimbRate();
};

#endif
```

---

## 🧮 Algoritmo de Detecção do Núcleo Térmico

### 1. Coleta de Dados (método `tick()`)

**Frequência**: Executado a cada segundo via `FlightCpu::bySecondTask()`

**Entradas necessárias**:
- `variometer.getAltitude()` - altitude atual
- `variometer.getVario()` - taxa de subida atual (m/s)
- `gps.getLatitude()` e `gps.getLongitude()` - posição atual
- `wind.getDirection()` e `wind.getSpeed()` - vento atual

**Condições para armazenar ponto**:
- GPS deve estar disponível (`gps.isAvailable()`)
- Piloto deve estar em voo (`flightCpu` tem flag `inFlight` - verificar acesso)
- Taxa de subida > `THERMAL_MIN_CLIMB_RATE` (considerar apenas pontos positivos significativos)

### 2. Armazenamento em Buffer Circular

```
history[0] = ponto mais antigo
history[historyIndex] = último ponto adicionado
historyCount = total de pontos válidos (max 100)
```

**Estratégia**:
- Usar array circular para evitar realocações
- Quando cheio, sobrescrever ponto mais antigo
- Cada ponto armazena: lat, lon, alt, climbRate, timestamp (millis)

### 3. Cálculo do Núcleo Térmico

**Estratégia por Camadas de Altitude**:

```
1. Dividir histórico em camadas de 50m (ex: 500-550m, 550-600m, etc)
2. Para cada camada, calcular:
   - Média de climb rate
   - Posição média (lat/lon)
3. Identificar camada com maior climb rate médio
4. Posição média dessa camada = núcleo térmico "bruto"
5. Aplicar correção de vento
```

**Estratégia Alternativa (mais simples para MVP)**:

```
1. Encontrar o ponto individual com maior climb rate nos últimos N pontos
2. Usar posição desse ponto como núcleo bruto
3. Aplicar correção de vento
```

### 4. Correção de Vento

A térmico se desloca com o vento. Precisamos estimar onde o núcleo está **agora**, não onde estava quando o piloto passou.

**Fórmula**:
```cpp
float timeSinceCore = (now - thermalCoreTimestamp) / 1000.0f;  // segundos
float windSpeedMPS = wind.getSpeed() * 0.277778f;  // km/h para m/s
float distanceDrift = windSpeedMPS * timeSinceCore;  // metros
float windDirectionRad = radians(wind.getDirection());

// Deslocar núcleo na direção do vento
float deltaLat = (distanceDrift * cos(windDirectionRad)) / 111320.0f;  // graus
float deltaLon = (distanceDrift * sin(windDirectionRad)) / (111320.0f * cos(radians(thermalCoreLatitude)));

correctedLat = thermalCoreLatitude + deltaLat;
correctedLon = thermalCoreLongitude + deltaLon;
```

**Nota**: 111320 metros ≈ 1 grau de latitude (constante global)

### 5. Timeout do Núcleo

Se passaram mais de 60 segundos desde a última detecção, considerar núcleo inválido.

---

## 🔄 Integração com o Sistema

### Modificações Necessárias

#### 1. globals.h e globals.cpp
```cpp
// globals.h
class Thermal;
extern Thermal thermal;

// globals.cpp
#include "Thermal/Thermal.h"
Thermal thermal;
```

#### 2. FlightCpu.cpp
```cpp
// No método bySecondTask(), adicionar:
void FlightCpu::bySecondTask() {
    // ... código existente ...

    if (inFlight) {
        wind.storeSpeed(gps.getHeading(), gps.getSpeed(), millis());
        thermal.tick();  // NOVA LINHA
    }
}
```

#### 3. compass.h e compass.cpp

**Adicionar método para desenhar ponto do térmico**:

```cpp
// compass.h
private:
    void drawThermalCore();

// compass.cpp
void Compass::draw() {
    // ... código existente ...
    drawWindDirection();
    drawThermalCore();  // NOVA LINHA
    return;
}

void Compass::drawThermalCore() {
    if (!thermal.hasThermalCore()) {
        return;
    }

    // Calcular posição relativa no círculo (300m = raio)
    int distance = thermal.calcDistanceToThermalCoreInMeters();
    int bearing = thermal.calcBearingToThermalCoreInDegrees();

    // Limitar ao raio do círculo
    float normalizedDistance = min(distance / 300.0f, 1.0f);

    // Calcular posição do ponto no círculo
    // O topo do círculo sempre aponta para heading atual
    float relativeAngle = bearing - gps.getHeading();
    float angleRad = radians(relativeAngle - 90);

    int pointX = x + (cos(angleRad) * this->size * normalizedDistance);
    int pointY = y + (sin(angleRad) * this->size * normalizedDistance);

    // Desenhar ponto preto (círculo preenchido de raio 2)
    display.drawDisc(pointX, pointY, 2);
}
```

---

## 🎨 Saídas da Classe

### Métodos Públicos Detalhados

#### `bool isRising()`
- Retorna `true` se climb rate atual > `THERMAL_MIN_CLIMB_RATE`
- Atualizado a cada `tick()`

#### `float getThermalCoreLatitude()` e `getLongitude()`
- Retorna coordenadas **corrigidas** pelo vento
- Se núcleo inválido/expirado, retorna 0.0

#### `int calcDistanceToThermalCoreInMeters()`
- Usa `TinyGPS::distance_between()` entre posição atual e núcleo
- Retorna distância em metros (0 se núcleo inválido)

#### `int calcBearingToThermalCoreInDegrees()`
- Usa `TinyGPS::course_to()` entre posição atual e núcleo
- Retorna bearing em graus (0-359)

#### `unsigned long getTimeSinceLastCore()`
- Retorna `millis() - thermalCoreTimestamp`
- Útil para UI mostrar "há quanto tempo foi detectado"

---

## 📝 Detalhes de Implementação

### Inicialização
```cpp
Thermal::Thermal() {
    historyCount = 0;
    historyIndex = 0;
    thermalCoreValid = false;
    currentlyRising = false;
    thermalCoreLatitude = 0;
    thermalCoreLongitude = 0;
    thermalCoreTimestamp = 0;

    // Zerar array de histórico
    for (int i = 0; i < THERMAL_MAX_HISTORY_POINTS; i++) {
        history[i].latitude = 0;
        history[i].longitude = 0;
        history[i].altitude = 0;
        history[i].climbRate = 0;
        history[i].timestamp = 0;
    }
}
```

### Método tick()
```cpp
void Thermal::tick() {
    unsigned long now = millis();

    // Verificar timeout do núcleo
    if (thermalCoreValid && (now - thermalCoreTimestamp > THERMAL_CORE_TIMEOUT_MS)) {
        thermalCoreValid = false;
    }

    // Verificar se estamos subindo
    float vario = variometer.getVario();
    currentlyRising = (vario >= THERMAL_MIN_CLIMB_RATE);

    // Coletar ponto apenas se subindo e GPS válido
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
```

### Estratégia de Cálculo (versão simples)
```cpp
void Thermal::calculateThermalCore() {
    if (historyCount < 3) {
        return;  // Mínimo de pontos necessários
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
```

### Aplicação de Correção de Vento
```cpp
void Thermal::applyWindCorrection(float &lat, float &lon) {
    if (!wind.isAvailable()) {
        return;  // Sem vento, sem correção
    }

    unsigned long now = millis();
    float timeSinceCore = (now - thermalCoreTimestamp) / 1000.0f;

    // Converter velocidade de km/h para m/s
    float windSpeedMPS = wind.getSpeed() * 0.277778f;
    float distanceDrift = windSpeedMPS * timeSinceCore;

    // Calcular deslocamento em graus
    float windDirRad = radians((float)wind.getDirection());

    // 1 grau lat ≈ 111320 metros
    float deltaLat = (distanceDrift * cos(windDirRad)) / 111320.0f;

    // 1 grau lon depende da latitude
    float deltaLon = (distanceDrift * sin(windDirRad)) /
                     (111320.0f * cos(radians(lat)));

    lat += deltaLat;
    lon += deltaLon;
}
```

---

## ✅ Checklist de Implementação

### Fase 1: Estrutura Básica
- [ ] Criar diretório `src/Thermal/`
- [ ] Criar `Thermal.h` com estruturas e declarações
- [ ] Criar `Thermal.cpp` com implementação básica
- [ ] Adicionar ao `globals.h` e `globals.cpp`

### Fase 2: Coleta de Dados
- [ ] Implementar `tick()` com coleta de pontos
- [ ] Implementar `addPoint()` com buffer circular
- [ ] Implementar `isRising()`
- [ ] Testar coleta de histórico

### Fase 3: Cálculo do Núcleo
- [ ] Implementar `findBestLiftPoint()`
- [ ] Implementar `calculateThermalCore()`
- [ ] Implementar timeout de núcleo
- [ ] Testar detecção básica

### Fase 4: Correção de Vento
- [ ] Implementar `applyWindCorrection()`
- [ ] Testar com diferentes condições de vento
- [ ] Validar cálculos de deriva

### Fase 5: Integração
- [ ] Adicionar chamada em `FlightCpu::bySecondTask()`
- [ ] Implementar `drawThermalCore()` em `Compass`
- [ ] Testar visualização no círculo
- [ ] Ajustar tamanhos e posições visuais

### Fase 6: Refinamentos
- [ ] Adicionar métodos auxiliares de debug
- [ ] Implementar estratégia de camadas (se necessário)
- [ ] Otimizar performance
- [ ] Criar README.md com documentação

---

## 🚀 Melhorias Futuras (Pós-MVP)

1. **Algoritmo de Camadas**
   - Dividir histórico em faixas de 50m
   - Calcular núcleo por camada
   - Detectar térmicas múltiplas

2. **Suavização**
   - Aplicar filtro de média móvel nas coordenadas do núcleo
   - Evitar "pulos" bruscos do ponto no círculo

3. **Confiança**
   - Adicionar score de confiança baseado em:
     - Número de pontos coletados
     - Consistência dos climb rates
     - Tempo desde última detecção

4. **Histórico Persistente**
   - Salvar núcleos térmicos em SD card/EEPROM
   - Criar mapa de térmicas do voo

5. **Múltiplas Térmicas**
   - Detectar múltiplas térmicas simultâneas
   - Mostrar a mais próxima ou mais forte

---

## 🔍 Considerações Técnicas

### Memória
- `ThermalPoint` = ~20 bytes
- 100 pontos = ~2KB de RAM
- Aceitável para ESP32

### Performance
- Cálculos executados apenas 1x por segundo
- Algoritmo linear O(n) para busca de melhor ponto
- Impacto mínimo no loop principal

### Precisão GPS
- GPS fornece lat/lon com ~5m de precisão
- Suficiente para indicação geral de direção
- Erro acumulado na correção de vento é aceitável

### Constantes para Ajuste
```cpp
THERMAL_MAX_DISTANCE_METERS = 300  // Raio do círculo
THERMAL_MIN_CLIMB_RATE = 0.5       // Sensibilidade (ajustar conforme voo real)
THERMAL_CORE_TIMEOUT_MS = 60000    // Validade do núcleo
```

---

## 📚 Referências de Código

- **TinyGPS::distance_between()**: Cálculo Haversine para distância
- **TinyGPS::course_to()**: Bearing entre dois pontos
- **Variometer**: Exemplo de buffer circular com regressão linear
- **Wind**: Exemplo de cálculo baseado em direções cardinais
- **Compass**: Exemplo de desenho em círculo polar
