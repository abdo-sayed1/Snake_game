# 🎮 Snake Game - ESP32 Wireless Edition

![Status](https://img.shields.io/badge/Status-Active-brightgreen)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B-red)
![License](https://img.shields.io/badge/License-MIT-green)

> A professional embedded systems project implementing a classic Snake game on ESP32 microcontrollers using wireless communication. One ESP32 displays the game on a Nokia 5510 LCD, while another acts as a wireless controller with physical buttons.

```
┌─────────────────────────────────────┐
│   ESP32 + Nokia 5510 Display        │
│  (Game Device)                      │
│  ┌─────────────────────────┐        │
│  │  🎮 Snake Game Screen   │        │
│  │  84x48 Monochrome LCD   │        │
│  │                         │        │
│  │  Score: 100 ⭐         │        │
│  └─────────────────────────┘        │
└─────────────────────────────────────┘
           ↕ WiFi UDP ↕
┌─────────────────────────────────────┐
│   ESP32 + 5 Buttons Controller      │
│  (Controller Device)                │
│  ┌─────────────────────────┐        │
│  │  🔼 UP      🔴 START   │        │
│  │  🔽 DOWN                │       │
│  │  🔙 LEFT   ▶ RIGHT     │        │
│  └─────────────────────────┘        │
└─────────────────────────────────────┘
```

## ✨ Features

| Feature | Details |
|---------|---------|
| 🎮 **Dual Device** | Separate game and controller ESP32s |
| 📡 **Wireless** | WiFi-based control via UDP protocol |
| 🖥️ **Display** | Nokia 5510 LCD (84x48 monochrome) |
| 🎛️ **Controls** | 5 buttons (4 directions + Start/Reset) |
| 🔊 **Audio** | Buzzer with game sounds |
| 🏗️ **Architecture** | Professional 3-layer design (MCAL/HAL/APP) |
| 🔄 **Modular** | Easy to extend and maintain |
| ⚡ **Performance** | Real-time game logic with collision detection |

---

## 📋 Hardware Requirements

### Game Device (ESP32 #1)
```
┌──────────────────────────────────┐
│         ESP32 DevKit             │
├──────────────────────────────────┤
│  GPIO 4  ──→ LCD RST             │
│  GPIO 5  ──→ LCD CE (Chip Sel)   │
│  GPIO 17 ──→ LCD DC (Data/Cmd)   │
│  GPIO 23 ──→ LCD DIN (MOSI)      │
│  GPIO 18 ──→ LCD CLK             │
│  GPIO 12 ──→ Buzzer              │
└──────────────────────────────────┘
         ↓
    ┌─────────────┐
    │ Nokia 5510  │
    │   Display   │
    │  84x48 px   │
    └─────────────┘
```

### Controller Device (ESP32 #2)
```
┌──────────────────────────────────┐
│         ESP32 DevKit             │
├──────────────────────────────────┤
│  GPIO 32 ──→ UP Button    ↑      │
│  GPIO 33 ──→ DOWN Button  ↓      │
│  GPIO 25 ──→ LEFT Button  ←      │
│  GPIO 26 ──→ RIGHT Button →      │
│  GPIO 27 ──→ START Button PRESS  │
│  GND    ──→ All Buttons (Pull-up)│
└──────────────────────────────────┘
```

---

## 📁 Project Structure

```
SNAKE_GAME/
│
├── 📄 README.md                 ← You are here
├── ⚙️ config.h                  ← Global configuration
│
├── 📂 src/
│   ├── snake_game.h/cpp         ← Game coordinator
│   ├── controller_app.h/cpp     ← Controller coordinator
│   │
│   ├── 📂 app/                  ← Application Layer
│   │   ├── game_logic.h/cpp     ← Game rules & rendering
│   │   └── game_state.h/cpp     ← State management
│   │
│   ├── 📂 hal/                  ← Hardware Abstraction Layer
│   │   ├── display_hal.h/cpp    ← LCD display control
│   │   ├── buttons_hal.h/cpp    ← Button input handling
│   │   ├── buzzer_hal.h/cpp     ← Sound generation
│   │   └── wifi_hal.h/cpp       ← WiFi connectivity
│   │
│   └── 📂 mcal/                 ← Microcontroller Abstraction Layer
│       ├── gpio_mcal.h/cpp      ← GPIO driver
│       └── spi_mcal.h/cpp       ← SPI communication driver
│
├── 📂 game/
│   └── game.ino                 ← Game device entry point
│
├── 📂 controller/
│   └── controller.ino           ← Controller entry point
│
└── 📂 lib/                      ← External libraries (optional)
```

---

## 🏗️ Architecture Layers

### Layered Design Overview
```
┌─────────────────────────────────────┐
│   APPLICATION LAYER (APP)           │
│  ┌───────────────────────────────┐  │
│  │  • Game Logic & Rules         │  │
│  │  • Game State Machine         │  │
│  │  • Collision Detection        │  │
│  │  • Score & Rendering          │  │
│  └───────────────────────────────┘  │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│  HARDWARE ABSTRACTION LAYER (HAL)   │
│  ┌───────────────────────────────┐  │
│  │  • Display Controller         │  │
│  │  • Button Input Handler       │  │
│  │  • Buzzer Sound Gen           │  │
│  │  • WiFi Management            │  │
│  └───────────────────────────────┘  │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│ MICROCONTROLLER ABSTRACTION (MCAL)  │
│  ┌───────────────────────────────┐  │
│  │  • GPIO Driver                │  │
│  │  • SPI Communication          │  │
│  │  • Low-level Hardware Control │  │
│  └───────────────────────────────┘  │
└─────────────────────────────────────┘
```

---

## 🚀 Installation & Setup

### Step 1: Install Arduino IDE
```bash
# Download from https://www.arduino.cc/en/software
# Install Arduino IDE 2.0+
```

### Step 2: Add ESP32 Board Package
```
Tools → Boards → Board Manager
├── Search: "ESP32"
├── Select: "esp32 by Espressif Systems"
└── Install: Latest Version
```

### Step 3: Configure Board Settings
```
Tools
├── Board: "ESP32 Dev Module"
├── Upload Speed: 921600
├── Flash Frequency: 80MHz
├── Flash Mode: DIO
└── Port: COM [Your Device]
```

### Step 4: Hardware Assembly

**Game Device Wiring:**
```
ESP32 PIN    →    Nokia 5510
─────────────────────────────
GPIO 4       →    RST
GPIO 5       →    CE
GPIO 17      →    DC
GPIO 23      →    DIN (MOSI)
GPIO 18      →    CLK
GND          →    GND
3.3V         →    VCC

GPIO 12      →    Buzzer (+)
GND          →    Buzzer (-)
```

**Controller Device Wiring:**
```
ESP32 PIN    →    Button
──────────────────────────
GPIO 32      →    UP (with pull-up)
GPIO 33      →    DOWN
GPIO 25      →    LEFT
GPIO 26      →    RIGHT
GPIO 27      →    START
GND          →    All Button GND
```

---

## 💻 Compilation & Upload

### Upload Game Device
```bash
1. Open: game/game.ino
2. Select Board: ESP32 Dev Module
3. Select Port: COM[Game Device]
4. Click: Upload ⬆️
5. Monitor: Tools → Serial Monitor (115200 baud)
```

### Upload Controller Device
```bash
1. Open: controller/controller.ino
2. Select Board: ESP32 Dev Module
3. Select Port: COM[Controller Device]
4. Click: Upload ⬆️
5. Monitor: Tools → Serial Monitor (115200 baud)
```

---

## ⚙️ Configuration

Edit `config.h` to customize your setup:

```cpp
// Game Speed (200ms = 5 moves/second)
#define GAME_TICK_MS 200

// Game Grid Size
#define GRID_WIDTH 21
#define GRID_HEIGHT 12

// WiFi Settings
#define WIFI_SSID "SnakeGame"
#define WIFI_PASSWORD "snakegame123"

// Pin Assignments
#define PIN_BTN_UP 32
#define PIN_BUZZER 12
// ... and more
```

| Setting | Default | Range | Notes |
|---------|---------|-------|-------|
| GAME_TICK_MS | 200 | 100-500 | Lower = Harder |
| GRID_WIDTH | 21 | 10-30 | Snake area width |
| GRID_HEIGHT | 12 | 8-20 | Snake area height |

---

## 🎯 Usage Guide

### Starting the Game
```
1. Power on BOTH ESP32 devices
2. Watch Serial Monitor for initialization
3. Game device creates WiFi AP "SnakeGame"
4. Controller connects to the AP
5. Press START button to begin
```

### Playing

| Button | Action |
|--------|--------|
| **UP** | Move snake up ⬆️ |
| **DOWN** | Move snake down ⬇️ |
| **LEFT** | Move snake left ⬅️ |
| **RIGHT** | Move snake right ➡️ |
| **START** | Begin/Pause/Resume 🎮 |

### Game States

```
┌─────────────┐
│   WELCOME   │ ← Initial state
└──────┬──────┘
       │ START pressed
       ▼
┌─────────────┐
│   PLAYING   │ ← Main game loop
└──────┬──────┘
       │ Collision or START
       ▼
┌─────────────┐
│  GAME OVER  │ ← Final state
└──────┬──────┘
       │ START pressed
       └────→ Back to WELCOME
```

### Sound Feedback

| Event | Sound | Duration |
|-------|-------|----------|
| Game Start | 🔊 Beep | 150ms |
| Food Eaten | 🎵 2-tone up | 200ms |
| Pause/Resume | 🔔 Double-beep | 160ms |
| Game Over | 📯 3-tone down | 600ms |

---

Problem: Black screen, no display
Solution:
├─ Verify all 5 display pins connected
├─ Check GPIO pin numbers in config.h
├─ Inspect Nokia 5510 VCC/GND connections
└─ Test with SPI analyzer
```


## 📊 Game Mechanics

```
┌─────────────────────────────────┐
│      GAME MECHANICS             │
├─────────────────────────────────┤
│ Initial Snake Length:    3 cells │
│ Points per Food:         10 pts  │
│ Speed:                   200ms   │
│ Game Area:               21×12   │
│ Max Snake Length:        252     │
└─────────────────────────────────┘
```

### Collision Rules
```
┌────────────────────────────┐
│  COLLISION DETECTION       │
├────────────────────────────┤
│ ✗ Hit Top Wall     → GAME OVER
│ ✗ Hit Bottom Wall  → GAME OVER
│ ✗ Hit Left Wall    → GAME OVER
│ ✗ Hit Right Wall   → GAME OVER
│ ✗ Hit Self Body    → GAME OVER
│ ✓ Hit Food         → +10 Points
└────────────────────────────┘
```

---

## 🛠️ Development

### Adding New Features

#### 1. Add Game State
```cpp
// In src/app/game_state.h
enum GameState {
    STATE_WELCOME,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER,
    STATE_MY_NEW_STATE  // ← Add here
};
```

#### 2. Add Hardware Interface
```cpp
// Create src/hal/my_device_hal.h/cpp
class MyDeviceHAL {
public:
    static void init();
    static void doSomething();
};
```

#### 3. Integrate into Game
```cpp
// In src/app/game_logic.cpp
MyDeviceHAL::init();
MyDeviceHAL::doSomething();
```

### Code Quality Guidelines
- ✅ Use clear variable names
- ✅ Add comments for complex logic
- ✅ Follow Arduino naming conventions
- ✅ Test on hardware before committing
- ✅ Keep HAL/MCAL layers independent

---

## 📚 Resources

| Resource | Link |
|----------|------|
| ESP32 Docs | https://docs.espressif.com/projects/esp-idf/ |
| Arduino IDE | https://docs.arduino.cc/software/ide-v2 |
| Nokia 5110 | https://en.wikipedia.org/wiki/Nokia_5110 |
| WiFi UDP | https://docs.arduino.cc/reference/en/libraries/wifi/ |

---

## 🐛 Known Limitations

| Limitation | Impact | Workaround |
|-----------|--------|-----------|
| Single Game Instance | Can't play on multiple displays | Use separate WiFi networks |
| Monochrome Display | Limited graphics | Use color display alternative |
| No Score Persistence | Scores lost on restart | Add EEPROM storage |
| Fixed Game Speed | No difficulty selection | Modify GAME_TICK_MS in config.h |

---

## 🔮 Future Enhancements

```
Priority: HIGH
├── [ ] EEPROM high score storage
├── [ ] Multiple difficulty levels
└── [ ] Obstacle/wall mode

Priority: MEDIUM
├── [ ] Bluetooth support
├── [ ] Alternative displays (OLED)
├── [ ] Web dashboard
└── [ ] Multiplayer mode

Priority: LOW
├── [ ] Mobile app controller
├── [ ] Cloud leaderboard
├── [ ] Custom themes
└── [ ] Power management
```

---

## 📝 License & Attribution

```
MIT License - Free to use and modify
Created for educational and personal projects
```

---

## 🎓 Learning Outcomes

After building this project, you'll understand:
- ✓ Embedded systems architecture
- ✓ Hardware abstraction principles
- ✓ WiFi communication (UDP)
- ✓ Game state machines
- ✓ Display drivers (SPI protocol)
- ✓ Button input handling
- ✓ Real-time systems design
- ✓ Professional C++ coding

---

## 📞 Support

For issues or questions:
1. Check the troubleshooting section
2. Review code comments
3. Monitor Serial output for errors
4. Test components individually

---

**Happy Gaming! 🎮 Level Up Your Embedded Systems Skills! 🚀**

```
  ╔════════════════════════════════╗
  ║   Snake Game - ESP32 Edition   ║
  ║      Ready to Play! 🎮         ║
  ╚════════════════════════════════╝
```
