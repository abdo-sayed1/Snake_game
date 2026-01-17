#include "game_state.h"

// Static member initialization
GameState GameStateManager::currentState = STATE_WELCOME;
Point GameStateManager::snake[MAX_SNAKE_LENGTH];
uint16_t GameStateManager::snakeLength = 0;
Point GameStateManager::food = {10, 6};
Direction GameStateManager::currentDirection = DIR_RIGHT;
Direction GameStateManager::nextDirection = DIR_RIGHT;
uint16_t GameStateManager::score = 0;
unsigned long GameStateManager::lastUpdateTime = 0;

void GameStateManager::init() {
    resetSnake();
    generateFood();
    resetScore();
    currentState = STATE_WELCOME;
}

GameState GameStateManager::getState() {
    return currentState;
}

void GameStateManager::setState(GameState newState) {
    currentState = newState;
}

void GameStateManager::resetSnake() {
    snakeLength = 3;
    snake[0] = {GRID_WIDTH / 2, GRID_HEIGHT / 2};
    snake[1] = {GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2};
    snake[2] = {GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2};
    currentDirection = DIR_RIGHT;
    nextDirection = DIR_RIGHT;
}

Point GameStateManager::getSnakeHead() {
    return snake[0];
}

Point GameStateManager::getSnakeSegment(uint16_t index) {
    if (index < snakeLength) {
        return snake[index];
    }
    return {-1, -1};
}

uint16_t GameStateManager::getSnakeLength() {
    return snakeLength;
}

void GameStateManager::moveSnake() {
    // Update direction
    currentDirection = nextDirection;
    
    // Calculate new head position
    Point newHead = snake[0];
    
    switch (currentDirection) {
        case DIR_UP:    newHead.y--; break;
        case DIR_RIGHT: newHead.x++; break;
        case DIR_DOWN:  newHead.y++; break;
        case DIR_LEFT:  newHead.x--; break;
    }
    
    // Shift snake body
    for (int i = snakeLength; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    
    // Place new head
    snake[0] = newHead;
}

void GameStateManager::generateFood() {
    bool validPosition = false;
    while (!validPosition) {
        food.x = random(0, GRID_WIDTH);
        food.y = random(0, GRID_HEIGHT);
        validPosition = true;
        
        // Check if food overlaps with snake
        for (int i = 0; i < snakeLength; i++) {
            if (snake[i].x == food.x && snake[i].y == food.y) {
                validPosition = false;
                break;
            }
        }
    }
}

Point GameStateManager::getFood() {
    return food;
}

void GameStateManager::setNextDirection(Direction dir) {
    // Prevent 180-degree turns
    if ((currentDirection == DIR_UP && dir == DIR_DOWN) ||
        (currentDirection == DIR_DOWN && dir == DIR_UP) ||
        (currentDirection == DIR_LEFT && dir == DIR_RIGHT) ||
        (currentDirection == DIR_RIGHT && dir == DIR_LEFT)) {
        return;
    }
    nextDirection = dir;
}

Direction GameStateManager::getDirection() {
    return currentDirection;
}

void GameStateManager::addScore(uint16_t points) {
    score += points;
}

uint16_t GameStateManager::getScore() {
    return score;
}

void GameStateManager::resetScore() {
    score = 0;
}

bool GameStateManager::checkCollisionWithWalls() {
    Point head = getSnakeHead();
    return (head.x < 0 || head.x >= GRID_WIDTH || 
            head.y < 0 || head.y >= GRID_HEIGHT);
}

bool GameStateManager::checkCollisionWithSelf() {
    Point head = getSnakeHead();
    for (int i = 1; i < snakeLength; i++) {
        if (head.x == snake[i].x && head.y == snake[i].y) {
            return true;
        }
    }
    return false;
}

bool GameStateManager::checkFoodCollision() {
    Point head = getSnakeHead();
    return (head.x == food.x && head.y == food.y);
}

void GameStateManager::increaseSnakeLength() {
    if (snakeLength < MAX_SNAKE_LENGTH) {
        snakeLength++;
    }
}
