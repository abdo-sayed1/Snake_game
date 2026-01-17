#ifndef WIFI_HAL_H
#define WIFI_HAL_H

#include <WiFi.h>
#include "../../config.h"

class WiFiHAL {
public:
    // Initialize WiFi
    static void initAP(const char* ssid, const char* password);
    
    static void initSTA(const char* ssid, const char* password);
    
    // Check WiFi connection status
    static bool isConnected();
    
    // Get local IP
    static IPAddress getLocalIP();
    
    // WiFi status
    static uint8_t getStatus();
    
    // Connect/Disconnect
    static void connect();
    
    static void disconnect();
};

#endif
