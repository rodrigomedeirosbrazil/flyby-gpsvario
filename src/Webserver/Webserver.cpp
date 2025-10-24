#include "Webserver.h"
#include "pages.h"
#include "../defines.h"

Webserver::Webserver() {
    server = nullptr;
    active = false;
    uploadInProgress = false;
    uploadSize = 0;
    uploadReceived = 0;
    startTime = 0;
}

void Webserver::begin() {
    Serial.println("Starting webserver...");
    startTime = millis();
    active = true;
    
    setupWiFi();
    setupWebServer();
    setupRoutes();
    
    server->begin();
    Serial.println("Webserver started");
}

void Webserver::tick() {
    if (!active) {
        return;
    }
    
    // Check timeout
    if (millis() - startTime >= WEBSERVER_TIMEOUT) {
        Serial.println("Webserver timeout reached");
        stop();
    }
}

void Webserver::stop() {
    if (!active) {
        return;
    }
    
    Serial.println("Stopping webserver...");
    
    if (server) {
        server->end();
        delete server;
        server = nullptr;
    }
    
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);
    
    active = false;
    Serial.println("Webserver stopped");
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
    Serial.println("Setting up WiFi AP...");
    
    WiFi.mode(WIFI_AP);
    WiFi.softAP(WEBSERVER_WIFI_SSID, WEBSERVER_WIFI_PASSWORD, WEBSERVER_WIFI_CHANNEL);
    
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
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
        Serial.printf("OTA Update Start: %s\n", filename.c_str());
        uploadInProgress = true;
        uploadSize = request->contentLength();
        uploadReceived = 0;
        
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
            Update.printError(Serial);
        }
    }
    
    if (len) {
        if (Update.write(data, len) != len) {
            Update.printError(Serial);
        } else {
            uploadReceived += len;
            Serial.printf("Progress: %d%%\n", (int)getProgress());
        }
    }
    
    if (final) {
        if (Update.end(true)) {
            Serial.printf("OTA Update Success: %u bytes\n", index + len);
            uploadInProgress = false;
        } else {
            Update.printError(Serial);
            uploadInProgress = false;
        }
    }
}

