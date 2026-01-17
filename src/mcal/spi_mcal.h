#ifndef SPI_MCAL_H
#define SPI_MCAL_H

#include <Arduino.h>

class SPI_MCAL {
public:
    // Initialize SPI interface
    static void init();
    
    // Transmit single byte
    static void transmit(uint8_t data);
    
    // Transmit multiple bytes
    static void transmitBuffer(const uint8_t* buffer, uint16_t length);
    
    // Set clock speed (in Hz)
    static void setClockSpeed(uint32_t speed);
};

#endif
