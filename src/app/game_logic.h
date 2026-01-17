#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "game_state.h"
#include "../hal/display_hal.h"
#include "../hal/buzzer_hal.h"

class GameLogic {
private:
    static unsigned long lastGameUpdateTime;
    
public:
    // Initialize game
    static void init();
    
    // Main game update
    static void update();
    
    // Handle input
    static void handleDirectionInput(Direction dir);
    
    static void handleStartInput();
    
    // Game tick (update game state)
    static void gameTickUpdate();
    
    // Check game over condition
    static bool isGameOver();
    
    // Reset game
    static void resetGame();
    
    // Render game (output to display)
    static void render();
};

#endif
