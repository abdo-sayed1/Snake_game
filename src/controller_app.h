#ifndef CONTROLLER_APP_H
#define CONTROLLER_APP_H

#include "hal/buttons_hal.h"
#include "hal/wifi_hal.h"
#include "../config.h"
#include <WiFi.h>

class ControllerApp {
private:
    static WiFiUDP udp;
    static const char* SSID;
    static const char* PASSWORD;
    static const IPAddress GAME_IP;
    static const int UDP_PORT;
    static unsigned long lastConnectionAttempt;
    
public:
    // Initialize the controller
    static void init();
    
    // Main controller loop
    static void run();
    
    // Initialize WiFi connection
    static void initWiFi();
    
    // Update button states
    static void updateButtons();
    
    // Send command to game
    static void sendCommand(const char* command);
};

#endif
