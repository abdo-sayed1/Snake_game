#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "app/game_logic.h"
#include "hal/wifi_hal.h"
#include "../config.h"
#include <WiFi.h>

class SnakeGame {
private:
    static WiFiUDP udp;
    static const char* SSID;
    static const char* PASSWORD;
    static const int UDP_PORT;
    
public:
    // Initialize the game
    static void init();
    
    // Main game loop
    static void run();
    
    // Initialize WiFi
    static void initWiFi();
    
    // Receive commands from controller
    static void receiveCommands();
};

#endif
