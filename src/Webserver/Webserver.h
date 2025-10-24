#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <WiFi.h>
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
};

#endif

