#include "display_hal.h"
#include "../mcal/gpio_mcal.h"
#include "../mcal/spi_mcal.h"

uint8_t DisplayHAL::frameBuffer[DISPLAY_WIDTH * DISPLAY_BANKS];

void DisplayHAL::init() {
    // Initialize GPIO pins
    GPIO_MCAL::pinMode(LCD_RST, 1);  // OUTPUT
    GPIO_MCAL::pinMode(LCD_CE, 1);   // OUTPUT
    GPIO_MCAL::pinMode(LCD_DC, 1);   // OUTPUT
    
    // Initialize SPI
    SPI_MCAL::init();
    
    // Reset display
    GPIO_MCAL::digitalWrite(LCD_RST, 0);  // LOW
    delay(10);
    GPIO_MCAL::digitalWrite(LCD_RST, 1);  // HIGH
    
    // Initialize display commands
    GPIO_MCAL::digitalWrite(LCD_CE, 0);   // LOW
    GPIO_MCAL::digitalWrite(LCD_DC, 0);   // LOW
    SPI_MCAL::transmit(0x21); // Function set
    SPI_MCAL::transmit(0x10); // Bias
    SPI_MCAL::transmit(0x04); // Temperature
    SPI_MCAL::transmit(0x0C); // Display control
    GPIO_MCAL::digitalWrite(LCD_CE, 1);   // HIGH
    
    clear();
}

void DisplayHAL::setPixel(int x, int y, uint8_t value) {
    if (x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT) {
        return;
    }
    
    int bank = y / 8;
    int bit = y % 8;
    
    if (value) {
        frameBuffer[bank * DISPLAY_WIDTH + x] |= (1 << bit);
    } else {
        frameBuffer[bank * DISPLAY_WIDTH + x] &= ~(1 << bit);
    }
}

void DisplayHAL::clear() {
    memset(frameBuffer, 0, DISPLAY_WIDTH * DISPLAY_BANKS);
}

void DisplayHAL::update() {
    for (int bank = 0; bank < DISPLAY_BANKS; bank++) {
        GPIO_MCAL::digitalWrite(LCD_CE, 0);   // LOW
        GPIO_MCAL::digitalWrite(LCD_DC, 0);   // LOW
        SPI_MCAL::transmit(0x80 | 0);         // Set column
        SPI_MCAL::transmit(0x40 | bank);      // Set bank
        GPIO_MCAL::digitalWrite(LCD_CE, 1);   // HIGH
        
        GPIO_MCAL::digitalWrite(LCD_CE, 0);   // LOW
        GPIO_MCAL::digitalWrite(LCD_DC, 1);   // HIGH
        for (int col = 0; col < DISPLAY_WIDTH; col++) {
            SPI_MCAL::transmit(frameBuffer[bank * DISPLAY_WIDTH + col]);
        }
        GPIO_MCAL::digitalWrite(LCD_CE, 1);   // HIGH
    }
}

void DisplayHAL::drawRect(int x, int y, int width, int height, uint8_t fill) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            setPixel(x + i, y + j, fill);
        }
    }
}

void DisplayHAL::drawLine(int x0, int y0, int x1, int y1) {
    // Bresenham's line algorithm
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    
    int x = x0, y = y0;
    while (1) {
        setPixel(x, y, 1);
        if (x == x1 && y == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

uint8_t* DisplayHAL::getFrameBuffer() {
    return frameBuffer;
}
