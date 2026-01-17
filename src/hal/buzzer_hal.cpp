#include "buzzer_hal.h"
#include <Arduino.h>

const uint8_t BuzzerHAL::BUZZER_CHANNEL = 0;
const uint32_t BuzzerHAL::PWM_FREQUENCY = 5000;
const uint8_t BuzzerHAL::PWM_RESOLUTION = 8;

void BuzzerHAL::init() {
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
    DEBUG_PRINTLN("Buzzer initialized");
}

void BuzzerHAL::beep(uint16_t frequency, uint16_t duration) {
    tone(PIN_BUZZER, frequency, duration);
    delay(duration);
    noTone(PIN_BUZZER);
}

void BuzzerHAL::playSuccess() {
    // Two ascending beeps
    beep(800, 100);
    delay(50);
    beep(1200, 100);
}

void BuzzerHAL::playGameOver() {
    // Descending beeps
    beep(1000, 200);
    delay(100);
    beep(800, 200);
    delay(100);
    beep(600, 200);
}

void BuzzerHAL::playStart() {
    // Single start beep
    beep(1000, 150);
}

void BuzzerHAL::playPause() {
    // Two quick beeps
    beep(900, 80);
    delay(50);
    beep(900, 80);
}

void BuzzerHAL::stop() {
    noTone(PIN_BUZZER);
    digitalWrite(PIN_BUZZER, LOW);
}
