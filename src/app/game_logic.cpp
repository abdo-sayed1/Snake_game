#include "game_logic.h"

unsigned long GameLogic::lastGameUpdateTime = 0;

void GameLogic::init() {
    GameStateManager::init();
    DisplayHAL::init();
    BuzzerHAL::init();
}

void GameLogic::update() {
    GameState state = GameStateManager::getState();
    
    switch (state) {
        case STATE_WELCOME:
            // Display welcome screen
            break;
            
        case STATE_PLAYING:
            if (millis() - lastGameUpdateTime > GAME_TICK_MS) {
                gameTickUpdate();
                lastGameUpdateTime = millis();
            }
            break;
            
        case STATE_PAUSED:
            // Game paused
            break;
            
        case STATE_GAME_OVER:
            // Game over screen
            break;
    }
    
    render();
}

void GameLogic::handleDirectionInput(Direction dir) {
    if (GameStateManager::getState() == STATE_PLAYING) {
        GameStateManager::setNextDirection(dir);
    }
}

void GameLogic::handleStartInput() {
    GameState state = GameStateManager::getState();
    
    if (state == STATE_WELCOME || state == STATE_GAME_OVER) {
        GameStateManager::resetSnake();
        GameStateManager::generateFood();
        GameStateManager::resetScore();
        GameStateManager::setState(STATE_PLAYING);
        lastGameUpdateTime = millis();
        BuzzerHAL::playStart();
    } else if (state == STATE_PLAYING) {
        GameStateManager::setState(STATE_PAUSED);
        BuzzerHAL::playPause();
    } else if (state == STATE_PAUSED) {
        GameStateManager::setState(STATE_PLAYING);
        BuzzerHAL::playPause();
    }
}

void GameLogic::gameTickUpdate() {
    // Move snake
    GameStateManager::moveSnake();
    
    // Check collisions
    if (GameStateManager::checkCollisionWithWalls() || 
        GameStateManager::checkCollisionWithSelf()) {
        GameStateManager::setState(STATE_GAME_OVER);
        BuzzerHAL::playGameOver();
        return;
    }
    
    // Check food collision
    if (GameStateManager::checkFoodCollision()) {
        GameStateManager::increaseSnakeLength();
        GameStateManager::addScore(10);
        GameStateManager::generateFood();
        BuzzerHAL::playSuccess();
    }
}

bool GameLogic::isGameOver() {
    return GameStateManager::getState() == STATE_GAME_OVER;
}

void GameLogic::resetGame() {
    GameStateManager::init();
}

void GameLogic::render() {
    DisplayHAL::clear();
    
    // Draw border
    int startX = 10;
    int startY = 10;
    int endX = startX + GRID_WIDTH * CELL_SIZE;
    int endY = startY + GRID_HEIGHT * CELL_SIZE;
    
    for (int x = startX; x <= endX; x++) {
        DisplayHAL::setPixel(x, startY, 1);
        DisplayHAL::setPixel(x, endY, 1);
    }
    
    for (int y = startY; y <= endY; y++) {
        DisplayHAL::setPixel(startX, y, 1);
        DisplayHAL::setPixel(endX, y, 1);
    }
    
    // Draw food
    Point food = GameStateManager::getFood();
    for (int dx = 0; dx < CELL_SIZE - 1; dx++) {
        for (int dy = 0; dy < CELL_SIZE - 1; dy++) {
            DisplayHAL::setPixel(startX + 1 + food.x * CELL_SIZE + dx,
                               startY + 1 + food.y * CELL_SIZE + dy, 1);
        }
    }
    
    // Draw snake
    for (int i = 0; i < GameStateManager::getSnakeLength(); i++) {
        Point segment = GameStateManager::getSnakeSegment(i);
        for (int dx = 0; dx < CELL_SIZE - 1; dx++) {
            for (int dy = 0; dy < CELL_SIZE - 1; dy++) {
                DisplayHAL::setPixel(startX + 1 + segment.x * CELL_SIZE + dx,
                                   startY + 1 + segment.y * CELL_SIZE + dy, 1);
            }
        }
    }
    
    DisplayHAL::update();
}
