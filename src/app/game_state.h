#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <Arduino.h>
#include <stdint.h>
#include "../../config.h"

// Game states
enum GameState {
    STATE_WELCOME,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER
};

// Point structure
struct Point {
    int8_t x;
    int8_t y;
};

// Direction enum
enum Direction {
    DIR_UP = 0,
    DIR_RIGHT = 1,
    DIR_DOWN = 2,
    DIR_LEFT = 3
};

class GameStateManager {
private:
    static GameState currentState;
    static Point snake[MAX_SNAKE_LENGTH];
    static uint16_t snakeLength;
    static Point food;
    static Direction currentDirection;
    static Direction nextDirection;
    static uint16_t score;
    static unsigned long lastUpdateTime;
    
public:
    // State management
    static void init();
    
    static GameState getState();
    
    static void setState(GameState newState);
    
    // Snake management
    static void resetSnake();
    
    static Point getSnakeHead();
    
    static Point getSnakeSegment(uint16_t index);
    
    static uint16_t getSnakeLength();
    
    static void moveSnake();
    
    // Food management
    static void generateFood();
    
    static Point getFood();
    
    // Direction management
    static void setNextDirection(Direction dir);
    
    static Direction getDirection();
    
    // Score management
    static void addScore(uint16_t points);
    
    static uint16_t getScore();
    
    static void resetScore();
    
    // Game logic
    static bool checkCollisionWithWalls();
    
    static bool checkCollisionWithSelf();
    
    static bool checkFoodCollision();
    
    static void increaseSnakeLength();
};

#endif
