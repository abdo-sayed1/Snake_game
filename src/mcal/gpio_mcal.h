#ifndef GPIO_MCAL_H
#define GPIO_MCAL_H

#include <Arduino.h>

// GPIO modes
#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

// GPIO levels
#define GPIO_LOW 0
#define GPIO_HIGH 1

class GPIO_MCAL {
public:
    // Initialize GPIO pin
    static void pinMode(uint8_t pin, uint8_t mode);
    
    // Write to GPIO pin
    static void digitalWrite(uint8_t pin, uint8_t value);
    
    // Read from GPIO pin
    static uint8_t digitalRead(uint8_t pin);
    
    // Write PWM value
    static void analogWrite(uint8_t pin, uint8_t value);
    
    // Read analog value
    static uint16_t analogRead(uint8_t pin);
};

#endif
