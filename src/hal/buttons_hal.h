#ifndef BUTTONS_HAL_H
#define BUTTONS_HAL_H

#include <Arduino.h>
#include "../../config.h"

// Button definitions
enum Button {
    BTN_UP = 0,
    BTN_DOWN = 1,
    BTN_LEFT = 2,
    BTN_RIGHT = 3,
    BTN_START = 4,
    BTN_COUNT = 5
};

class ButtonsHAL {
private:
    static const uint8_t buttonPins[BTN_COUNT];
    static uint8_t lastState[BTN_COUNT];
    static unsigned long lastDebounceTime;
    
public:
    // Initialize buttons
    static void init();
    
    // Check if button is pressed
    static bool isPressed(Button btn);
    
    // Get button state (debounced)
    static bool getButtonState(Button btn);
    
    // Update button states (call regularly)
    static void update();
};

#endif
