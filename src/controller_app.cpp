#include "controller_app.h"

WiFiUDP ControllerApp::udp;
const char* ControllerApp::SSID = "SnakeGame";
const char* ControllerApp::PASSWORD = "snakegame123";
const IPAddress ControllerApp::GAME_IP(192, 168, 4, 1);
const int ControllerApp::UDP_PORT = 8888;
unsigned long ControllerApp::lastConnectionAttempt = 0;

void ControllerApp::init() {
    Serial.begin(115200);
    delay(1000);
    
    // Initialize buttons
    ButtonsHAL::init();
    
    // Initialize WiFi
    initWiFi();
    
    // Start UDP
    udp.begin(UDP_PORT);
    
    Serial.println("Controller initialized!");
}

void ControllerApp::run() {
    // Update button states
    ButtonsHAL::update();
    updateButtons();
    
    // Check WiFi connection periodically
    if (millis() - lastConnectionAttempt > 5000) {
        if (!WiFiHAL::isConnected()) {
            Serial.println("WiFi disconnected, attempting to reconnect...");
            initWiFi();
        }
        lastConnectionAttempt = millis();
    }
}

void ControllerApp::initWiFi() {
    Serial.print("Connecting to WiFi: ");
    Serial.println(SSID);
    
    WiFiHAL::initSTA(SSID, PASSWORD);
    
    int attempts = 0;
    while (!WiFiHAL::isConnected() && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFiHAL::isConnected()) {
        Serial.println();
        Serial.println("WiFi connected!");
        IPAddress ip = WiFiHAL::getLocalIP();
        Serial.print("IP: ");
        Serial.println(ip);
    } else {
        Serial.println();
        Serial.println("Failed to connect to WiFi");
    }
}

void ControllerApp::updateButtons() {
    static uint8_t lastPressedState[5] = {0, 0, 0, 0, 0};
    
    Button buttons[5] = {BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_START};
    const char* buttonNames[5] = {"UP", "DOWN", "LEFT", "RIGHT", "START"};
    
    for (int i = 0; i < 5; i++) {
        bool pressed = ButtonsHAL::isPressed(buttons[i]);
        
        // Detect button press (rising edge)
        if (pressed && !lastPressedState[i]) {
            sendCommand(buttonNames[i]);
            Serial.print("Button pressed: ");
            Serial.println(buttonNames[i]);
        }
        
        lastPressedState[i] = pressed;
    }
}

void ControllerApp::sendCommand(const char* command) {
    if (WiFiHAL::isConnected()) {
        udp.beginPacket(GAME_IP, UDP_PORT);
        udp.write((uint8_t*)command, strlen(command));
        udp.endPacket();
        
        Serial.print("Sent: ");
        Serial.println(command);
    } else {
        Serial.println("WiFi not connected!");
    }
}
