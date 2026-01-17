#ifndef BUZZER_HAL_H
#define BUZZER_HAL_H

#include <Arduino.h>
#include "../../config.h"

class BuzzerHAL {
public:
    // Initialize buzzer
    static void init();
    
    // Play a simple beep
    static void beep(uint16_t frequency = 1000, uint16_t duration = 100);
    
    // Play success sound (food eaten)
    static void playSuccess();
    
    // Play game over sound
    static void playGameOver();
    
    // Play start sound
    static void playStart();
    
    // Play pause sound
    static void playPause();
    
    // Stop buzzer
    static void stop();
    
private:
    static const uint8_t BUZZER_CHANNEL;
    static const uint32_t PWM_FREQUENCY;
    static const uint8_t PWM_RESOLUTION;
};

#endif
