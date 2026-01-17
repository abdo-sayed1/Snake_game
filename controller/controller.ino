// Snake Game - Controller Device Entry Point
// ESP32 with 5 Buttons

#include "../src/controller_app.h"

ControllerApp controllerInstance;

void setup() {
  // Initialize the controller
  controllerInstance.init();
}

void loop() {
  // Run the controller main loop
  controllerInstance.run();
  
  delay(20); // 50 FPS polling
}

// Include all source files for Arduino IDE compilation
#include "../src/mcal/gpio_mcal.cpp"
#include "../src/hal/buttons_hal.cpp"
#include "../src/hal/wifi_hal.cpp"
#include "../src/controller_app.cpp"
