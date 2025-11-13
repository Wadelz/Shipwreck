#include "Game.h"
#include "Constants.h"
#include <sstream>
#include <cmath>
#include <iostream>

using namespace GameConstants;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
    , score(0)
    , lives(STARTING_LIVES)
    , haveWon(false)
    , bestTime(99999.0f)
    , animateWave(0)
{
    window.setFramerateLimit(FRAME_RATE_LIMIT);
}

Game::~Game() {
    // Cleanup handled by smart pointers
}

bool Game::initialize() {
    // Initialize UI first
    if (!initializeUI()) {
        return false;
    }

    // Create all game entities
    createEntities();

    return true;
}

void Game::createEntities() {
    // Create flag
    flag = std::make_unique<Flag>(Positions::FLAG_X, Positions::FLAG_Y);

    // Create ship (centered horizontally at starting Y position)
    ship = std::make_unique<Ship>(WINDOW_WIDTH / 2.0f, Positions::SHIP_START_Y);

    // Create rocks
    rocks.push_back(std::make_unique<Rock>(Positions::ROCK1_X, Positions::ROCK1_Y));
    rocks.push_back(std::make_unique<Rock>(Positions::ROCK2_X, Positions::ROCK2_Y));
    rocks.push_back(std::make_unique<Rock>(Positions::ROCK3_X, Positions::ROCK3_Y));
    rocks.push_back(std::make_unique<Rock>(Positions::ROCK4_X, Positions::ROCK4_Y));

    // Create wave
    wave = std::make_unique<Wave>(Positions::WAVE_X, Positions::WAVE_Y);

    // Create survivors
    survivors.push_back(std::make_unique<Survivor>(Positions::SURVIVOR1_X, Positions::SURVIVOR1_Y));
    survivors.push_back(std::make_unique<Survivor>(Positions::SURVIVOR2_X, Positions::SURVIVOR2_Y));
    survivors.push_back(std::make_unique<Survivor>(Positions::SURVIVOR3_X, Positions::SURVIVOR3_Y));
    survivors.push_back(std::make_unique<Survivor>(Positions::SURVIVOR4_X, Positions::SURVIVOR4_Y));
    survivors.push_back(std::make_unique<Survivor>(Positions::SURVIVOR5_X, Positions::SURVIVOR5_Y));
    survivors.push_back(std::make_unique<Survivor>(Positions::SURVIVOR6_X, Positions::SURVIVOR6_Y));

    // Create beach ball (easter egg)
    beachBall = std::make_unique<EasterBall>(WINDOW_WIDTH / 2.0f, Positions::BEACH_BALL_Y);
}

bool Game::initializeUI() {
    // Load font
    if (!font.loadFromFile(Assets::FONT_RETRO)) {
        std::cerr << "Error: Could not load font '" << Assets::FONT_RETRO
                  << "'. Make sure the file exists in the correct location.\n";
        return false;
    }

    // Setup HUD
    hud.setFont(font);
    hud.setCharacterSize(HUD_TEXT_SIZE);
    hud.setFillColor(sf::Color::White);
    hud.setPosition(0, 0);

    // Setup completion text
    complete.setFont(font);
    complete.setCharacterSize(COMPLETE_TEXT_SIZE);
    complete.setFillColor(sf::Color::White);
    complete.setPosition(0, WINDOW_HEIGHT / 2.0f);

    return true;
}

bool Game::run() {
    // Reset game state
    resetGame();

    // Start the clock
    clock.restart();

    // Main game loop
    while (window.isOpen()) {
        // Get elapsed time
        float time = clock.getElapsedTime().asSeconds();

        // Handle input
        handleInput();

        // Update animations
        updateAnimations();

        // Check collisions
        checkCollisions();

        // Check for zero lives
        if (lives <= 0) {
            window.close();
            return true; // Player can play again
        }

        // Update HUD
        updateHUD(time);

        // Check win condition
        checkWinCondition();

        // Update all entities
        update(time);

        // Render everything
        render();
    }

    // Return false if window was closed without completing the game
    return false;
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    // Game controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        ship->moveLeft();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        ship->moveUp();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        ship->moveDown();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        ship->moveRight();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }

    // Handle space key for win screen
    if (haveWon && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        window.close();
    }
}

void Game::update(float deltaTime) {
    // Update flag
    flag->update();

    // Update beach ball
    beachBall->update();

    // Update ship
    ship->update();

    // Update wave
    wave->update();

    // Update all survivors
    for (auto& survivor : survivors) {
        survivor->update();
    }
}

void Game::updateAnimations() {
    animateWave++;

    if (animateWave % ANIMATION_CYCLE > ANIMATION_MIDPOINT) {
        wave->setPos1();
        flag->setPos1();
    } else {
        wave->setPos2();
        flag->setPos2();
    }
}

void Game::checkCollisions() {
    // Beach ball collisions with window edges
    if (beachBall->getPosition().top + 100 >= WINDOW_HEIGHT) {
        beachBall->hitBottom();
    }

    if (beachBall->getPosition().top <= 0) {
        beachBall->reboundBatOrTop();
    }

    if (beachBall->getPosition().left <= 0 ||
        beachBall->getPosition().left + 100 >= WINDOW_WIDTH) {
        beachBall->reboundSides();
    }

    // Ship boundary collisions
    if (ship->getPosition().left + 25 > WINDOW_WIDTH) {
        ship->reboundRight();
    }

    if (ship->getPosition().left < 0) {
        ship->reboundLeft();
    }

    // Wave reset at bottom
    if (wave->getPosition().top + 100 > WINDOW_HEIGHT) {
        wave->resetPosition();
    }

    // Check rock collisions
    checkRockCollisions();

    // Check wave collision
    checkWaveCollision();

    // Check survivor collection
    checkSurvivorCollection();
}

void Game::checkRockCollisions() {
    for (const auto& rock : rocks) {
        if (rock->getPosition().intersects(ship->getPosition())) {
            ship->shipHitRock();
            break; // Only need to handle one collision per frame
        }
    }
}

void Game::checkWaveCollision() {
    if (ship->getPosition().intersects(wave->getPosition())) {
        // Check if ship is in safe zone behind any rock
        bool inSafeZone = false;
        for (const auto& rock : rocks) {
            if (ship->getPosition().intersects(rock->safeZonPos())) {
                inSafeZone = true;
                break;
            }
        }

        // If not in safe zone, lose a life
        if (!inSafeZone) {
            ship->resetPosition();
            wave->resetPosition();
            lives--;
        }
    }
}

void Game::checkSurvivorCollection() {
    for (auto& survivor : survivors) {
        if (ship->getPosition().intersects(survivor->getPosition())) {
            survivor->collectSurvivor();
            score++;
        }
    }

    // Reduce speed after saving threshold number of survivors
    if (score == SPEED_REDUCTION_THRESHOLD) {
        ship->reduceSpeed();
    }
}

void Game::checkWinCondition() {
    if (ship->getPosition().intersects(flag->getFinPosition()) &&
        score == REQUIRED_SURVIVORS) {
        haveWon = true;
        wave->waveStop();
        ship->shipStop();

        // Update best time if current time is better
        float currentTime = clock.getElapsedTime().asSeconds();
        if (currentTime < bestTime) {
            bestTime = currentTime;
        }
    }
}

void Game::updateHUD(float time) {
    if (!haveWon) {
        // Update game status HUD
        std::stringstream ss;
        ss << "Survivors saved:" << score
           << "    Lives:" << lives
           << "   Time: " << static_cast<int>(std::ceil(time));
        hud.setString(ss.str());

        // Update completion message
        std::stringstream finGame;
        finGame << Messages::WIN_MESSAGE
                << static_cast<int>(std::ceil(time))
                << Messages::WIN_MESSAGE_SUFFIX;
        complete.setString(finGame.str());
    }
}

void Game::render() {
    // Clear with ocean color
    window.clear(sf::Color(OCEAN_R, OCEAN_G, OCEAN_B, OCEAN_A));

    // Draw wave
    window.draw(wave->getShape());

    // Draw rock safe zone overlays
    for (const auto& rock : rocks) {
        window.draw(rock->getOverlay());
    }

    // Draw rocks
    for (const auto& rock : rocks) {
        window.draw(rock->getShape());
    }

    // Draw ship
    window.draw(ship->getSprite());

    // Draw survivors
    for (const auto& survivor : survivors) {
        window.draw(survivor->getShape());
    }

    // Draw flag
    window.draw(flag->getShape());
    window.draw(flag->getfinish());

    // Draw HUD
    window.draw(hud);

    // Draw win screen elements
    if (haveWon) {
        window.draw(complete);
        window.draw(beachBall->getShape());
    }

    // Display everything
    window.display();
}

void Game::resetGame() {
    score = 0;
    lives = STARTING_LIVES;
    haveWon = false;
    animateWave = 0;

    // Recreate all entities for a fresh start
    createEntities();
}
