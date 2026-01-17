#include "spi_mcal.h"
#include "gpio_mcal.h"

// SPI pins for ESP32
#define SPI_CLK 18
#define SPI_MOSI 23

void SPI_MCAL::init() {
    GPIO_MCAL::pinMode(SPI_CLK, 1);  // OUTPUT
    GPIO_MCAL::pinMode(SPI_MOSI, 1); // OUTPUT
    GPIO_MCAL::digitalWrite(SPI_CLK, 0);   // LOW
    GPIO_MCAL::digitalWrite(SPI_MOSI, 0);  // LOW
}

void SPI_MCAL::transmit(uint8_t data) {
    for (int i = 7; i >= 0; i--) {
        GPIO_MCAL::digitalWrite(SPI_CLK, 0);  // LOW
        GPIO_MCAL::digitalWrite(SPI_MOSI, (data >> i) & 1);
        GPIO_MCAL::digitalWrite(SPI_CLK, 1);  // HIGH
    }
}

void SPI_MCAL::transmitBuffer(const uint8_t* buffer, uint16_t length) {
    for (uint16_t i = 0; i < length; i++) {
        transmit(buffer[i]);
    }
}

void SPI_MCAL::setClockSpeed(uint32_t speed) {
    // ESP32 SPI configuration
    // Clock speed management handled by transmit timing
}
