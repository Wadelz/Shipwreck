#pragma once

namespace GameConstants {
    // Window settings
    const int WINDOW_WIDTH = 1024;
    const int WINDOW_HEIGHT = 768;
    const int FRAME_RATE_LIMIT = 144;
    const char* WINDOW_TITLE = "Wave Break";

    // Ocean background color (RGB)
    const int OCEAN_R = 26;
    const int OCEAN_G = 128;
    const int OCEAN_B = 182;
    const int OCEAN_A = 255;

    // Game settings
    const int STARTING_LIVES = 3;
    const int REQUIRED_SURVIVORS = 6;
    const int SPEED_REDUCTION_THRESHOLD = 4; // Reduce speed after saving this many survivors

    // Animation settings
    const int ANIMATION_CYCLE = 100;
    const int ANIMATION_MIDPOINT = 50;

    // HUD settings
    const int HUD_TEXT_SIZE = 65;
    const int COMPLETE_TEXT_SIZE = 75;

    // Entity initial positions
    namespace Positions {
        // Flag position
        const float FLAG_X = 315.0f;
        const float FLAG_Y = 180.0f;

        // Wave starting position (off-screen)
        const float WAVE_X = -3076.0f;
        const float WAVE_Y = 0.0f;

        // Rock positions
        const float ROCK1_X = 900.0f;
        const float ROCK1_Y = 384.0f;

        const float ROCK2_X = 500.0f;
        const float ROCK2_Y = 200.0f;

        const float ROCK3_X = 200.0f;
        const float ROCK3_Y = 225.0f;

        const float ROCK4_X = 10.0f;
        const float ROCK4_Y = 384.0f;

        // Survivor positions
        const float SURVIVOR1_X = 900.0f;
        const float SURVIVOR1_Y = 500.0f;

        const float SURVIVOR2_X = 700.0f;
        const float SURVIVOR2_Y = 400.0f;

        const float SURVIVOR3_X = 500.0f;
        const float SURVIVOR3_Y = 325.0f;

        const float SURVIVOR4_X = 350.0f;
        const float SURVIVOR4_Y = 600.0f;

        const float SURVIVOR5_X = 200.0f;
        const float SURVIVOR5_Y = 380.0f;

        const float SURVIVOR6_X = 15.0f;
        const float SURVIVOR6_Y = 500.0f;

        // Ship starting position
        const float SHIP_START_Y = 650.0f;

        // Beach ball position
        const float BEACH_BALL_Y = 1.0f;
    }

    // Asset paths
    namespace Assets {
        const char* FONT_RETRO = "assets/fonts/RetroTeam.otf";
        const char* FONT_DIGIT = "assets/fonts/DS-DIGIT.TTF";

        const char* TEXTURE_BOAT = "assets/textures/RowBoatC.png";
        const char* TEXTURE_WAVE = "assets/textures/WavesHalf.png";
        const char* TEXTURE_WAVE_FADE = "assets/textures/WaveFade.png";
        const char* TEXTURE_ROCK = "assets/textures/Rock2_1.png";
        const char* TEXTURE_FLAG = "assets/textures/Flag2k.png";
        const char* TEXTURE_SURVIVOR = "assets/textures/head.png";
        const char* TEXTURE_BEACH_BALL = "assets/textures/easterBeachBall.png";
    }

    // Gameplay messages
    namespace Messages {
        const char* GAME_INTRO =
            "Some of your pirate crew went overboard due to rough waters just off shore.\n"
            "Collect them in your trusty row boat while avoiding the waves by hiding behind rocks\n"
            "and then head back to your ship through the flags.\n";

        const char* PLAY_PROMPT = "\n1 - Yes\n0 - No\nWould you like to play: ";
        const char* PLAY_AGAIN_PROMPT = "\n1 - Yes\n0 - No\nWould you like to play again: ";

        const char* WIN_MESSAGE = "                 You have won!\n"
                                  "           Your Time: ";
        const char* WIN_MESSAGE_SUFFIX = " seconds\n\n         Press Space to continue";
    }
}
