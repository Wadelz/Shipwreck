#pragma once

namespace GameConstants {
    // Window settings
    inline constexpr int WINDOW_WIDTH = 1024;
    inline constexpr int WINDOW_HEIGHT = 768;
    inline constexpr int FRAME_RATE_LIMIT = 144;
    inline constexpr const char* WINDOW_TITLE = "Wave Break";

    // Ocean background color (RGB)
    inline constexpr int OCEAN_R = 26;
    inline constexpr int OCEAN_G = 128;
    inline constexpr int OCEAN_B = 182;
    inline constexpr int OCEAN_A = 255;

    // Game settings
    inline constexpr int STARTING_LIVES = 3;
    inline constexpr int REQUIRED_SURVIVORS = 6;
    inline constexpr int SPEED_REDUCTION_THRESHOLD = 4; // Reduce speed after saving this many survivors

    // Animation settings
    inline constexpr int ANIMATION_CYCLE = 100;
    inline constexpr int ANIMATION_MIDPOINT = 50;

    // HUD settings
    inline constexpr int HUD_TEXT_SIZE = 65;
    inline constexpr int COMPLETE_TEXT_SIZE = 75;

    // Entity initial positions
    namespace Positions {
        // Flag position
        inline constexpr float FLAG_X = 315.0f;
        inline constexpr float FLAG_Y = 180.0f;

        // Wave starting position (off-screen)
        inline constexpr float WAVE_X = -3076.0f;
        inline constexpr float WAVE_Y = 0.0f;

        // Rock positions
        inline constexpr float ROCK1_X = 900.0f;
        inline constexpr float ROCK1_Y = 384.0f;

        inline constexpr float ROCK2_X = 500.0f;
        inline constexpr float ROCK2_Y = 200.0f;

        inline constexpr float ROCK3_X = 200.0f;
        inline constexpr float ROCK3_Y = 225.0f;

        inline constexpr float ROCK4_X = 10.0f;
        inline constexpr float ROCK4_Y = 384.0f;

        // Survivor positions
        inline constexpr float SURVIVOR1_X = 900.0f;
        inline constexpr float SURVIVOR1_Y = 500.0f;

        inline constexpr float SURVIVOR2_X = 700.0f;
        inline constexpr float SURVIVOR2_Y = 400.0f;

        inline constexpr float SURVIVOR3_X = 500.0f;
        inline constexpr float SURVIVOR3_Y = 325.0f;

        inline constexpr float SURVIVOR4_X = 350.0f;
        inline constexpr float SURVIVOR4_Y = 600.0f;

        inline constexpr float SURVIVOR5_X = 200.0f;
        inline constexpr float SURVIVOR5_Y = 380.0f;

        inline constexpr float SURVIVOR6_X = 15.0f;
        inline constexpr float SURVIVOR6_Y = 500.0f;

        // Ship starting position
        inline constexpr float SHIP_START_Y = 650.0f;

        // Beach ball position
        inline constexpr float BEACH_BALL_Y = 1.0f;
    }

    // Asset paths
    namespace Assets {
        inline constexpr const char* FONT_RETRO = "assets/fonts/RetroTeam.otf";
        inline constexpr const char* FONT_DIGIT = "assets/fonts/DS-DIGIT.TTF";

        inline constexpr const char* TEXTURE_BOAT = "assets/textures/RowBoatC.png";
        inline constexpr const char* TEXTURE_WAVE = "assets/textures/WavesHalf.png";
        inline constexpr const char* TEXTURE_WAVE_FADE = "assets/textures/WaveFade.png";
        inline constexpr const char* TEXTURE_ROCK = "assets/textures/Rock2_1.png";
        inline constexpr const char* TEXTURE_FLAG = "assets/textures/Flag2k.png";
        inline constexpr const char* TEXTURE_SURVIVOR = "assets/textures/head.png";
        inline constexpr const char* TEXTURE_BEACH_BALL = "assets/textures/easterBeachBall.png";
    }

    // Gameplay messages
    namespace Messages {
        inline constexpr const char* GAME_INTRO =
            "Some of your pirate crew went overboard due to rough waters just off shore.\n"
            "Collect them in your trusty row boat while avoiding the waves by hiding behind rocks\n"
            "and then head back to your ship through the flags.\n";

        inline constexpr const char* PLAY_PROMPT = "\n1 - Yes\n0 - No\nWould you like to play: ";
        inline constexpr const char* PLAY_AGAIN_PROMPT = "\n1 - Yes\n0 - No\nWould you like to play again: ";

        inline constexpr const char* WIN_MESSAGE = "                 You have won!\n"
                                  "           Your Time: ";
        inline constexpr const char* WIN_MESSAGE_SUFFIX = " seconds\n\n         Press Space to continue";
    }
}
