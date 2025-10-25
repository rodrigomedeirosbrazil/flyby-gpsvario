#include "Webserver.h"
#include "pages.h"
#include "../defines.h"
#include "../Config/Config.h"
#include <ArduinoJson.h>

Webserver::Webserver() {
    server = nullptr;
    active = false;
    uploadInProgress = false;
    uploadSize = 0;
    uploadReceived = 0;
    startTime = 0;
}

void Webserver::begin() {
    startTime = millis();
    active = true;

    setupWiFi();
    setupWebServer();
    setupRoutes();

    server->begin();
}

void Webserver::tick() {
    if (!active) {
        return;
    }

    // Check timeout only if no clients are connected
    // Once someone connects, keep webserver active
    if (WiFi.softAPgetStationNum() == 0) {
        if (millis() - startTime >= WEBSERVER_TIMEOUT) {
            stop();
        }
    }
}

void Webserver::stop() {
    if (!active) {
        return;
    }

    if (server) {
        server->end();
        delete server;
        server = nullptr;
    }

    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);

    active = false;
}

bool Webserver::isActive() {
    return active;
}

float Webserver::getProgress() {
    if (!uploadInProgress || uploadSize == 0) {
        return 0.0;
    }
    return (float)uploadReceived / (float)uploadSize * 100.0;
}

void Webserver::setupWiFi() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(WEBSERVER_WIFI_SSID, WEBSERVER_WIFI_PASSWORD, WEBSERVER_WIFI_CHANNEL);
}

void Webserver::setupWebServer() {
    server = new AsyncWebServer(80);
}

void Webserver::setupRoutes() {
    // Home page
    server->on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        this->handleHome(request);
    });

    // OTA page
    server->on("/ota", HTTP_GET, [this](AsyncWebServerRequest *request) {
        this->handleOTAPage(request);
    });

    // Info page
    server->on("/info", HTTP_GET, [this](AsyncWebServerRequest *request) {
        this->handleInfo(request);
    });

    // Configuration page
    server->on("/config", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", HTML_CONFIG_PAGE);
    });

    // API endpoints for configuration
    server->on("/api/config", HTTP_GET, [this](AsyncWebServerRequest *request) {
        this->handleConfigGet(request);
    });

    server->on("/api/config", HTTP_POST, [this](AsyncWebServerRequest *request) {
        this->handleConfigPost(request);
    });

    server->on("/api/config/defaults", HTTP_POST, [this](AsyncWebServerRequest *request) {
        this->handleConfigDefaults(request);
    });

    // OTA upload handler
    server->on("/ota/upload", HTTP_POST,
        [this](AsyncWebServerRequest *request) {
            // This is called after upload completes
            if (Update.hasError()) {
                request->send(500, "text/plain", "Update failed");
            } else {
                request->send(200, "text/plain", "Update successful! Rebooting...");
                delay(1000);
                ESP.restart();
            }
        },
        [this](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
            this->handleOTAUpload(request, filename, index, data, len, final);
        }
    );
}

void Webserver::handleHome(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", HTML_HOME);
}

void Webserver::handleOTAPage(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", HTML_OTA);
}

void Webserver::handleInfo(AsyncWebServerRequest *request) {
    String info = "Flyby GPS Vario\n";
    info += "Uptime: " + String(millis() / 1000) + "s\n";
    info += "Free heap: " + String(ESP.getFreeHeap()) + " bytes\n";
    request->send(200, "text/plain", info);
}

void Webserver::handleOTAUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    if (index == 0) {
        uploadInProgress = true;
        uploadSize = request->contentLength();
        uploadReceived = 0;

        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
            // Update failed to begin
        }
    }

    if (len) {
        if (Update.write(data, len) != len) {
            // Write failed
        } else {
            uploadReceived += len;
        }
    }

    if (final) {
        if (Update.end(true)) {
            uploadInProgress = false;
        } else {
            uploadInProgress = false;
        }
    }
}

// Configuration API handlers
void Webserver::handleConfigGet(AsyncWebServerRequest *request) {
    Config& config = Config::getInstance();
    
    DynamicJsonDocument doc(1024);
    doc["timezone"] = config.getTimezone();
    doc["takeoffSpeed"] = config.getTakeoffSpeed();
    doc["pdopMaxThreshold"] = config.getPdopMaxThreshold();
    doc["qnh"] = config.getQnh();
    doc["qnhByGps"] = config.getQnhByGps();
    doc["varioBeepOnlyInFlight"] = config.getVarioBeepOnlyInFlight();
    doc["climbRate"] = config.getClimbRate();
    doc["sinkRate"] = config.getSinkRate();
    
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response);
}

void Webserver::handleConfigPost(AsyncWebServerRequest *request) {
    Config& config = Config::getInstance();
    
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, request->getBody());
    
    if (error) {
        DynamicJsonDocument errorDoc(256);
        errorDoc["success"] = false;
        errorDoc["error"] = "Invalid JSON";
        String errorResponse;
        serializeJson(errorDoc, errorResponse);
        request->send(400, "application/json", errorResponse);
        return;
    }
    
    // Update configuration values
    if (doc.containsKey("timezone")) {
        config.setTimezone(doc["timezone"]);
    }
    if (doc.containsKey("takeoffSpeed")) {
        config.setTakeoffSpeed(doc["takeoffSpeed"]);
    }
    if (doc.containsKey("pdopMaxThreshold")) {
        config.setPdopMaxThreshold(doc["pdopMaxThreshold"]);
    }
    if (doc.containsKey("qnh")) {
        config.setQnh(doc["qnh"]);
    }
    if (doc.containsKey("qnhByGps")) {
        config.setQnhByGps(doc["qnhByGps"]);
    }
    if (doc.containsKey("varioBeepOnlyInFlight")) {
        config.setVarioBeepOnlyInFlight(doc["varioBeepOnlyInFlight"]);
    }
    if (doc.containsKey("climbRate")) {
        config.setClimbRate(doc["climbRate"]);
    }
    if (doc.containsKey("sinkRate")) {
        config.setSinkRate(doc["sinkRate"]);
    }
    
    // Save configuration
    bool success = config.save();
    
    DynamicJsonDocument responseDoc(256);
    responseDoc["success"] = success;
    if (!success) {
        responseDoc["error"] = "Failed to save configuration";
    }
    
    String response;
    serializeJson(responseDoc, response);
    request->send(success ? 200 : 500, "application/json", response);
}

void Webserver::handleConfigDefaults(AsyncWebServerRequest *request) {
    Config& config = Config::getInstance();
    config.loadDefaults();
    bool success = config.save();
    
    DynamicJsonDocument responseDoc(256);
    responseDoc["success"] = success;
    if (!success) {
        responseDoc["error"] = "Failed to reset configuration";
    }
    
    String response;
    serializeJson(responseDoc, response);
    request->send(success ? 200 : 500, "application/json", response);
}

