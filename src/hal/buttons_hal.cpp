#include "buttons_hal.h"
#include "../mcal/gpio_mcal.h"

// Button pin assignments
const uint8_t ButtonsHAL::buttonPins[BTN_COUNT] = {PIN_BTN_UP, PIN_BTN_DOWN, PIN_BTN_LEFT, PIN_BTN_RIGHT, PIN_BTN_START};

uint8_t ButtonsHAL::lastState[BTN_COUNT];
unsigned long ButtonsHAL::lastDebounceTime = 0;

void ButtonsHAL::init() {
    for (int i = 0; i < BTN_COUNT; i++) {
        GPIO_MCAL::pinMode(buttonPins[i], 0); // INPUT
        lastState[i] = 1; // HIGH (not pressed)
    }
}

bool ButtonsHAL::isPressed(Button btn) {
    return GPIO_MCAL::digitalRead(buttonPins[btn]) == 0; // LOW means pressed
}

bool ButtonsHAL::getButtonState(Button btn) {
    return lastState[btn] == 0; // HIGH (not pressed) when lastState is 1
}

void ButtonsHAL::update() {
    if ((millis() - lastDebounceTime) > 50) { // 50ms debounce
        for (int i = 0; i < BTN_COUNT; i++) {
            lastState[i] = GPIO_MCAL::digitalRead(buttonPins[i]);
        }
        lastDebounceTime = millis();
    }
}
