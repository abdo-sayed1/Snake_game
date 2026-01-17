#ifndef DISPLAY_HAL_H
#define DISPLAY_HAL_H

#include <Arduino.h>
#include <stdint.h>
#include "../../config.h"

class DisplayHAL {
private:
    static uint8_t frameBuffer[DISPLAY_WIDTH * DISPLAY_BANKS];
    
public:
    // Initialize display
    static void init();
    
    // Set pixel
    static void setPixel(int x, int y, uint8_t value);
    
    // Clear display
    static void clear();
    
    // Update display with frame buffer
    static void update();
    
    // Draw filled rectangle
    static void drawRect(int x, int y, int width, int height, uint8_t fill);
    
    // Draw line
    static void drawLine(int x0, int y0, int x1, int y1);
    
    // Get frame buffer pointer
    static uint8_t* getFrameBuffer();
};

#endif
