#include "wifi_hal.h"

void WiFiHAL::initAP(const char* ssid, const char* password) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
}

void WiFiHAL::initSTA(const char* ssid, const char* password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
}

bool WiFiHAL::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

IPAddress WiFiHAL::getLocalIP() {
    return WiFi.localIP();
}

uint8_t WiFiHAL::getStatus() {
    return WiFi.status();
}

void WiFiHAL::connect() {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.reconnect();
    }
}

void WiFiHAL::disconnect() {
    WiFi.disconnect(true); // Turn off WiFi
}
