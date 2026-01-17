// Configuration file for Snake Game Project

#ifndef CONFIG_H
#define CONFIG_H

// Game Configuration
#define GAME_TICK_MS 200
#define GRID_WIDTH 21
#define GRID_HEIGHT 12
#define CELL_SIZE 4
#define MAX_SNAKE_LENGTH (GRID_WIDTH * GRID_HEIGHT)

// Display Configuration
#define DISPLAY_WIDTH 84
#define DISPLAY_HEIGHT 48
#define DISPLAY_BANKS 6

// Display Pins (Nokia 5510)
#define LCD_RST 4
#define LCD_CE 5
#define LCD_DC 17
#define LCD_DIN 23
#define LCD_CLK 18

// Button Pins
#define PIN_BTN_UP 32
#define PIN_BTN_DOWN 33
#define PIN_BTN_LEFT 25
#define PIN_BTN_RIGHT 26
#define PIN_BTN_START 27

// Buzzer Pin
#define PIN_BUZZER 12

// WiFi Configuration
#define WIFI_SSID "SnakeGame"
#define WIFI_PASSWORD "snakegame123"
#define WIFI_GAME_IP 192, 168, 4, 1
#define WIFI_UDP_PORT 8888

// Debug Configuration
#define DEBUG_ENABLED 1

#if DEBUG_ENABLED
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

#endif
