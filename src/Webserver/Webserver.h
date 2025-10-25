#ifndef FLYBY_WEBSERVER_H
#define FLYBY_WEBSERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Update.h>

class Webserver {
public:
    Webserver();
    void begin();
    void tick();
    void stop();
    bool isActive();
    float getProgress();

private:
    AsyncWebServer* server;
    unsigned long startTime;
    bool active;
    bool uploadInProgress;
    size_t uploadSize;
    size_t uploadReceived;
    String configRequestBody;  // Store POST body for config API

    void setupWiFi();
    void setupWebServer();
    void setupRoutes();
    
    // Route handlers
    void handleHome(AsyncWebServerRequest *request);
    void handleOTAPage(AsyncWebServerRequest *request);
    void handleInfo(AsyncWebServerRequest *request);
    void handleOTAUpload(AsyncWebServerRequest *request, 
                         String filename, 
                         size_t index, 
                         uint8_t *data, 
                         size_t len, 
                         bool final);
    
    // Configuration API handlers
    void handleConfigGet(AsyncWebServerRequest *request);
    void handleConfigPost(AsyncWebServerRequest *request);
    void handleConfigPostBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
    void handleConfigDefaults(AsyncWebServerRequest *request);
};

#endif // FLYBY_WEBSERVER_H

