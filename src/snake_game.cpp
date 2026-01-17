#include "snake_game.h"

WiFiUDP SnakeGame::udp;
const char* SnakeGame::SSID = "SnakeGame";
const char* SnakeGame::PASSWORD = "snakegame123";
const int SnakeGame::UDP_PORT = 8888;

void SnakeGame::init() {
    Serial.begin(115200);
    delay(1000);
    
    // Initialize game
    GameLogic::init();
    
    // Initialize WiFi
    initWiFi();
    
    // Start UDP server
    udp.begin(UDP_PORT);
    
    Serial.println("Snake Game initialized!");
}

void SnakeGame::run() {
    receiveCommands();
    GameLogic::update();
}

void SnakeGame::initWiFi() {
    Serial.println("Initializing WiFi AP...");
    WiFiHAL::initAP(SSID, PASSWORD);
    
    IPAddress ip = WiFiHAL::getLocalIP();
    Serial.print("AP IP: ");
    Serial.println(ip);
}

void SnakeGame::receiveCommands() {
    if (udp.parsePacket()) {
        char buffer[256];
        int len = udp.read((uint8_t*)buffer, 255);
        buffer[len] = '\0';
        
        if (strcmp(buffer, "UP") == 0) {
            GameLogic::handleDirectionInput(DIR_UP);
        } else if (strcmp(buffer, "DOWN") == 0) {
            GameLogic::handleDirectionInput(DIR_DOWN);
        } else if (strcmp(buffer, "LEFT") == 0) {
            GameLogic::handleDirectionInput(DIR_LEFT);
        } else if (strcmp(buffer, "RIGHT") == 0) {
            GameLogic::handleDirectionInput(DIR_RIGHT);
        } else if (strcmp(buffer, "START") == 0) {
            GameLogic::handleStartInput();
        }
    }
}
