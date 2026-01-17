# 🎮 Snake Game - ESP32 Wireless Edition

A professional embedded systems project implementing a classic Snake game on ESP32 microcontrollers with wireless communication. One ESP32 displays the game on a Nokia 5510 LCD, while another acts as a wireless controller with 5 buttons.

## ✨ Key Features

- **Dual ESP32 Architecture** - Separate game and controller devices
- **Wireless Communication** - WiFi-based control using UDP protocol
- **Nokia 5510 LCD Display** - 84x48 pixel monochrome display
- **5-Button Controller** - Up, Down, Left, Right, and Start/Reset buttons
- **Buzzer Audio** - Game sounds and feedback
- **Professional Code Structure** - 3-layer architecture (MCAL/HAL/APP)
- **Modular & Extensible** - Easy to add features or modify hardware
- **Real-time Game Logic** - Collision detection, food generation, scoring

## 📋 Hardware Requirements

### Game Device (ESP32 #1)
| Component | Pin | Connection |
|-----------|-----|------------|
| ESP32 | GPIO 4 | Nokia 5510 RST |
| ESP32 | GPIO 5 | Nokia 5510 CE |
| ESP32 | GPIO 17 | Nokia 5510 DC |
| ESP32 | GPIO 23 | Nokia 5510 DIN (MOSI) |
| ESP32 | GPIO 18 | Nokia 5510 CLK |
| ESP32 | GPIO 12 | Buzzer (+) |
| ESP32 | GND | Nokia 5510 GND, Buzzer (-) |
| ESP32 | 3.3V | Nokia 5510 VCC |

### Controller Device (ESP32 #2)
| Component | Pin | Function |
|-----------|-----|----------|
| ESP32 | GPIO 32 | UP Button |
| ESP32 | GPIO 33 | DOWN Button |
| ESP32 | GPIO 25 | LEFT Button |
| ESP32 | GPIO 26 | RIGHT Button |
| ESP32 | GPIO 27 | START Button |
| ESP32 | GND | All Button GND (Pull-up) |

## 📁 Project Architecture

```
src/
├── app/
│   ├── game_logic.h/cpp      - Game rules, rendering, state updates
│   └── game_state.h/cpp      - Game state management
├── hal/
│   ├── display_hal.h/cpp     - Nokia 5510 display control (SPI)
│   ├── buttons_hal.h/cpp     - Button input handling with debouncing
│   ├── buzzer_hal.h/cpp      - Buzzer sound generation (PWM)
│   └── wifi_hal.h/cpp        - WiFi AP/STA setup
└── mcal/
    ├── gpio_mcal.h/cpp       - GPIO operations
    └── spi_mcal.h/cpp        - SPI communication driver

game/
└── game.ino                  - Game device entry point

controller/
└── controller.ino            - Controller device entry point
```

## 🚀 Installation & Setup

### 1. Prerequisites
- Arduino IDE 2.0 or later
- ESP32 Board Package v2.0.0 or later
- USB cables for both ESP32 devices

### 2. Arduino IDE Configuration
```
Tools → Board Manager
├── Search: "ESP32"
├── Install: esp32 by Espressif Systems
└── Select Board: ESP32 Dev Module

Tools
├── Upload Speed: 921600
├── Flash Frequency: 80MHz
├── Flash Mode: DIO
└── Port: COM[Your Device]
```

### 3. Hardware Wiring

**Game Device Connections:**
- ESP32 GPIO 4 → Nokia 5510 RST
- ESP32 GPIO 5 → Nokia 5510 CE
- ESP32 GPIO 17 → Nokia 5510 DC
- ESP32 GPIO 23 → Nokia 5510 DIN
- ESP32 GPIO 18 → Nokia 5510 CLK
- ESP32 GPIO 12 → Buzzer (+)
- ESP32 GND → Nokia 5510 GND, Buzzer (-)
- ESP32 3.3V → Nokia 5510 VCC

**Controller Device Connections:**
- Connect buttons to GPIO 32, 33, 25, 26, 27 with GND (pull-up)

## 💻 Uploading Code

### Game Device
1. Open `game/game.ino` in Arduino IDE
2. Select correct COM port (game device)
3. Click Upload (Ctrl+U)
4. Open Serial Monitor (115200 baud) to verify initialization

### Controller Device
1. Open `controller/controller.ino` in Arduino IDE
2. Select correct COM port (controller device)
3. Click Upload (Ctrl+U)
4. Open Serial Monitor to verify WiFi connection

## ⚙️ Configuration

All settings in `config.h`:

```cpp
// Game Speed (milliseconds per move)
#define GAME_TICK_MS 200        // Lower = faster

// Grid Dimensions
#define GRID_WIDTH 21           // Number of columns
#define GRID_HEIGHT 12          // Number of rows

// Display Configuration
#define DISPLAY_WIDTH 84
#define DISPLAY_HEIGHT 48
#define DISPLAY_BANKS 6

// WiFi Settings
#define WIFI_SSID "SnakeGame"
#define WIFI_PASSWORD "snakegame123"
#define WIFI_UDP_PORT 8888

// Pin Definitions
#define LCD_RST 4
#define LCD_CE 5
#define LCD_DC 17
#define LCD_DIN 23
#define LCD_CLK 18
#define PIN_BUZZER 12
#define PIN_BTN_UP 32
#define PIN_BTN_DOWN 33
#define PIN_BTN_LEFT 25
#define PIN_BTN_RIGHT 26
#define PIN_BTN_START 27
```

## 🎮 Gameplay

### Game States
- **WELCOME** - Idle state, waiting for START press
- **PLAYING** - Active game loop with snake movement
- **PAUSED** - Game paused, can resume with START
- **GAME_OVER** - Collision detected, press START to restart

### Controls
| Button | Action |
|--------|--------|
| UP | Move snake up (↑) |
| DOWN | Move snake down (↓) |
| LEFT | Move snake left (←) |
| RIGHT | Move snake right (→) |
| START | Begin/Pause/Resume game |

### Game Mechanics
- **Initial Snake Length** - 3 cells
- **Points per Food** - 10 points
- **Game Speed** - Configurable via GAME_TICK_MS
- **Collision Detection** - Wall and self-collision causes game over
- **Food Generation** - Random placement (never on snake)

### Sound Feedback
| Event | Frequency | Duration |
|-------|-----------|----------|
| Game Start | 1000 Hz | 150ms |
| Food Eaten | 2-tone (800→1200 Hz) | 200ms |
| Pause/Resume | 900 Hz | 160ms (2x) |
| Game Over | 3-tone (1000→800→600 Hz) | 600ms |

## 🏗️ Code Architecture

### Layered Design
```
┌─────────────────────────────┐
│    Application Layer        │
│  (Game Logic & Rendering)   │
└──────────────┬──────────────┘
               ↓
┌─────────────────────────────┐
│   Hardware Abstraction      │
│  (Display, Buttons, WiFi)   │
└──────────────┬──────────────┘
               ↓
┌─────────────────────────────┐
│  Microcontroller Layer      │
│  (GPIO, SPI Drivers)        │
└─────────────────────────────┘
```

This separation allows:
- Easy hardware modification
- Code reusability
- Independent testing of layers
- Simple migration to different displays/controllers

## 🔧 Customization

### Change Game Speed
Edit in `config.h`:
```cpp
#define GAME_TICK_MS 150  // Faster
#define GAME_TICK_MS 300  // Slower
```

### Change Grid Size
```cpp
#define GRID_WIDTH 30
#define GRID_HEIGHT 15
```

### Change WiFi Credentials
```cpp
#define WIFI_SSID "MyNetwork"
#define WIFI_PASSWORD "mypassword"
```

### Reassign Pins
Simply update pin definitions and reconnect hardware accordingly.

## 🐛 Troubleshooting

| Issue | Cause | Solution |
|-------|-------|----------|
| Display blank/no output | Wrong GPIO pins | Check config.h pin assignments match wiring |
| Buttons not responding | Incorrect button pins | Verify GPIO pins 32-27 are correct |
| Controller can't connect | WiFi mismatch | Ensure SSID/password match on both devices |
| Serial monitor no output | Wrong baud rate | Set Serial Monitor to 115200 baud |
| Display shows garbage | SPI timing issue | Reduce SPI clock speed or check cable length |
| Buzzer not working | Pin or frequency issue | Verify GPIO 12 connection and config.h settings |

## 📊 Performance Metrics

- **Frame Rate** - 5 FPS (200ms tick) - Configurable
- **Game Loop Time** - <20ms per iteration (50 FPS polling)
- **Display Update** - ~50ms (SPI communication)
- **WiFi Latency** - <100ms typical
- **Memory Usage** - ~60KB RAM (Snake buffer, display buffer)

## 📝 File Overview

| File | Lines | Purpose |
|------|-------|---------|
| config.h | 50 | Global configuration |
| game_logic.cpp | 100 | Game update and render logic |
| game_state.cpp | 150 | Snake state management |
| display_hal.cpp | 80 | LCD display driver |
| buttons_hal.cpp | 40 | Button input handler |
| buzzer_hal.cpp | 30 | Sound generation |
| wifi_hal.cpp | 30 | WiFi setup |
| Total Project | ~650 | Professional embedded system |

## 🔮 Future Enhancements

- [ ] EEPROM high score storage
- [ ] Multiple difficulty levels (dynamic speed)
- [ ] Obstacles/walls mode
- [ ] Bluetooth alternative to WiFi
- [ ] OLED display support
- [ ] Mobile app controller
- [ ] Multiplayer mode (2 snakes)
- [ ] Power management optimization

## 📚 Resources

- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/)
- [Arduino ESP32 Reference](https://docs.arduino.cc/reference/en/libraries/wifi/)
- [Nokia 5110 Datasheet](https://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf)
- [SPI Protocol Guide](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)

## 📝 License

MIT License - Free to use, modify, and distribute

---

**Created for embedded systems learning and IoT applications.**

🚀 **Happy Gaming!**
