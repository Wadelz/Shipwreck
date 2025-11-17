#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "../entities/Ship.h"
#include "../entities/Wave.h"
#include "../entities/Rock.h"
#include "../entities/Survivor.h"
#include "../entities/Flag.h"
#include "../entities/Ball.h"

/**
 * @brief Main game class that manages the game loop and game state
 *
 * This class encapsulates all game logic, entity management, collision detection,
 * rendering, and user input handling.
 */
class Game {
private:
    // Window
    sf::RenderWindow window;

    // Game state
    int score;
    int lives;
    bool haveWon;
    float bestTime;
    int animateWave;

    // Clock for timing
    sf::Clock clock;

    // Entities
    std::unique_ptr<Ship> ship;
    std::unique_ptr<Wave> wave;
    std::unique_ptr<Flag> flag;
    std::unique_ptr<EasterBall> beachBall;
    std::vector<std::unique_ptr<Rock>> rocks;
    std::vector<std::unique_ptr<Survivor>> survivors;

    // UI Elements
    sf::Text hud;
    sf::Text complete;
    sf::Font font;

public:
    /**
     * @brief Construct a new Game object
     */
    Game();

    /**
     * @brief Destroy the Game object
     */
    ~Game();

    /**
     * @brief Initialize the game (load resources, create entities)
     * @return true if initialization successful
     * @return false if initialization failed
     */
    bool initialize();

    /**
     * @brief Run the main game loop
     * @return true if player wants to play again
     * @return false if player wants to quit
     */
    bool run();

    /**
     * @brief Get the best time achieved
     * @return float The best time in seconds
     */
    float getBestTime() const { return bestTime; }

private:
    /**
     * @brief Create all game entities
     */
    void createEntities();

    /**
     * @brief Initialize UI elements (HUD, fonts, text)
     * @return true if successful
     * @return false if failed
     */
    bool initializeUI();

    /**
     * @brief Handle user input
     */
    void handleInput();

    /**
     * @brief Update game state
     * @param deltaTime Time since last update
     */
    void update(float deltaTime);

    /**
     * @brief Update animations (wave, flag)
     */
    void updateAnimations();

    /**
     * @brief Check all collision detection
     */
    void checkCollisions();

    /**
     * @brief Check ship collisions with rocks
     */
    void checkRockCollisions();

    /**
     * @brief Check wave collision with ship
     */
    void checkWaveCollision();

    /**
     * @brief Check survivor collection
     */
    void checkSurvivorCollection();

    /**
     * @brief Check win condition
     */
    void checkWinCondition();

    /**
     * @brief Update HUD text
     * @param time Current game time
     */
    void updateHUD(float time);

    /**
     * @brief Render all game objects
     */
    void render();

    /**
     * @brief Reset game state for new game
     */
    void resetGame();
};
