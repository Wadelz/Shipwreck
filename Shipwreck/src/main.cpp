#include <iostream>
#include <cmath>
#include "core/Game.h"
#include "core/Constants.h"

/**
 * @brief Main entry point for Shipwreck game
 *
 * Handles game initialization, main game loop control, and replay logic.
 * Displays game introduction and handles play again prompts.
 *
 * @return int Exit code (0 for success, -1 for error)
 */
int main() {
    bool playAgain = true;
    bool start = false;

    // Display game introduction
    std::cout << GameConstants::Messages::GAME_INTRO;
    std::cout << GameConstants::Messages::PLAY_PROMPT;
    std::cin >> start;

    if (!start) {
        return 0;
    }

    // Main game loop - allows replay
    do {
        // Create game instance
        Game game;

        // Initialize game resources
        if (!game.initialize()) {
            std::cerr << "Failed to initialize game!\n";
            return -1;
        }

        // Run the game
        playAgain = game.run();

        // Display best time and prompt for replay
        if (playAgain) {
            std::cout << "\nYour best time: "
                      << static_cast<int>(std::ceil(game.getBestTime()))
                      << " seconds\n";
            std::cout << GameConstants::Messages::PLAY_AGAIN_PROMPT;
            std::cin >> playAgain;
        }

    } while (playAgain);

    return 0;
}
