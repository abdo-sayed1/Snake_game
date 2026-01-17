// Snake Game - Game Device Entry Point
// ESP32 with Nokia 5510 Display

#include "../src/snake_game.h"

SnakeGame gameInstance;

void setup() {
  // Initialize the game
  gameInstance.init();
}

void loop() {
  // Run the game main loop
  gameInstance.run();
  
  delay(20); // 50 FPS
}

// Include all source files for Arduino IDE compilation
#include "../src/mcal/gpio_mcal.cpp"
#include "../src/mcal/spi_mcal.cpp"
#include "../src/hal/display_hal.cpp"
#include "../src/hal/buttons_hal.cpp"
#include "../src/hal/buzzer_hal.cpp"
#include "../src/hal/wifi_hal.cpp"
#include "../src/app/game_state.cpp"
#include "../src/app/game_logic.cpp"
#include "../src/snake_game.cpp"
