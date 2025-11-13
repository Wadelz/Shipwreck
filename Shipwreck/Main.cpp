// These "include" code from the C++ library and SFML too
#include "ship.h"
#include "rock.h"
#include "easterBall.h"
#include "wave.h"
#include "flag.h"
#include "survivor.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


// Avoid having to put sf in front of all the SFML classes and functions
using namespace sf;
bool playAgain = 1;
bool haveWon = 0;
bool pointless = 0;
bool start = 0;
// This is where our game starts from
int main()
{
    float bestTime = 99999;
    std::cout << "Some of your pirate crew went overboard due to rough waters just off shore.\nCollect them in your trusty row boat while avoiding the waves by hiding behind rocks\nand then head back to your ship through the flags.\n";
    std::cout << "\n1 - Yes\n0 - No\nWould you like to play: ";
    std::cin >> start;

    if (start == 0)
    {
        return 0;
    }

    do{

    int windowWidth = 1024;
    int windowHeight = 768;
    // Make a window that is 1024 by 768 pixels
    // And has the title "Pirate Saver"
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Wave Break");
    window.setFramerateLimit(144);

    int score = 0;
    int lives = 3;
    bool haveWon = 0;
    // Creat flags
    Flag flag(315, 180);

    // Create a ship
    Ship ship(windowWidth / 2, 650);

    // create rocks
    Rock rock1(900, 384);
    Rock rock2(500, 200);
    Rock rock3(200, 225);
    Rock rock4(10, 384);

    // Create wave
    Wave wave(-3076, 0);

   // Create survivor
    Survivor survivor1(900, 500);
    Survivor survivor2(700, 400);
    Survivor survivor3(500, 325);
    Survivor survivor4(350, 600);
    Survivor survivor5(200, 380);
    Survivor survivor6(15, 500);

    
    // Create a easter ball
    EasterBall beachBall(windowWidth / 2, 1);

    // Create a "Text" object for our hud and game completion message
    Text hud;
    Text complete;

    // Selecting the downloaded font
    Font font;
    // https://www.dafont.com/retro-team.font
    font.loadFromFile("RetroTeam.otf");

    if (!font.loadFromFile("RetroTeam.otf"))
    {
        std::cerr << "Error: Could not load font 'RetroTeam.otf'. Make sure the file exists in the correct location.\n";
        return -1;  // Exit the program with an error code
    }

    // Setting text positions on screen
    hud.setPosition(0, 0);
    complete.setPosition(0, windowHeight / 2);

    // Setting the font of the text
    hud.setFont(font);
    complete.setFont(font);

    // Changing text size
    hud.setCharacterSize(65);
    complete.setCharacterSize(75);

    // Choosing a text color
    hud.setFillColor(sf::Color::White);
    complete.setFillColor(sf::Color::White);

    // Setting up for rudimentary attempt at animation
    int animateWave = 0;
    
    // Creating a clock for ingame stop watch
    Clock clock;
    

    // The while loops that handles in game events
    while (window.isOpen())
    {
        // Getting elapsed time
        float time = clock.getElapsedTime().asSeconds();
        
        // Animations for wave and flag
        if (true)
        {
            animateWave = animateWave + 1;
        }

        if (animateWave % 100 > 50)
        {
            wave.setPos1();
            flag.setPos1();
        }

        else
        {
            wave.setPos2();
            flag.setPos2();
        }

        /*
            
            *********************************************************************
            ********************Handle the player input**************************
            *********************************************************************
        */

        // Checking if windows was closed
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                // Close window
                window.close();
        }

        if (event.type == Event::Closed)
            // Set play again to flase
            playAgain = 0;

        // Game controles
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            // Move left
            ship.moveLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            // Move up
            ship.moveUp();
        
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            // Move down
            ship.moveDown();
        }
  
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            // Move right
            ship.moveRight();
          
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // Quit game and close window
            playAgain = 0;
            window.close();
        }

        /*
            *********************************************************************
            ********************** Update the frame******************************
            *********************************************************************
        */

        // Collision ball hitting the bottom
        if (beachBall.getPosition().top + 100 == windowHeight)
        {
            // reverse the ball direction
            beachBall.hitBottom();
        }

        // Collision ball hitting top
        if (beachBall.getPosition().top == 0)
        {
            beachBall.reboundBatOrTop();
        }

        // Collision ball hitting sides
        if (beachBall.getPosition().left == 0 || beachBall.getPosition().left + 100 > windowWidth)
        {
            beachBall.reboundSides();
        }

        // Ship collision
        // Right side
        if ((ship.getPosition().left + 25) > windowWidth)
        {
            ship.reboundRight();
        }

        // Left side

        if (ship.getPosition().left < 0)
        {
            ship.reboundLeft();
        }
        // Wave hits bottom and resets position
        if (wave.getPosition().top + 100 > windowHeight)
        {
            wave.resetPosition();
        }

        // Has ship hit rock
        if (rock1.getPosition().intersects(ship.getPosition()) || rock2.getPosition().intersects(ship.getPosition()) || rock3.getPosition().intersects(ship.getPosition()) || rock4.getPosition().intersects(ship.getPosition()))
        {
            ship.shipHitRock();
        }

        // Hit by wave & not in safe zone(Behind rock)
        if (ship.getPosition().intersects(wave.getPosition()) && !(ship.getPosition().intersects(rock1.safeZonPos()) || ship.getPosition().intersects(rock2.safeZonPos()) || ship.getPosition().intersects(rock3.safeZonPos()) || ship.getPosition().intersects(rock4.safeZonPos())))
        {
            ship.resetPosition();
            wave.resetPosition();
            lives--; 
        }

        // Check for zero lives
        if (lives == 0)
        {
            window.close();
            std::cout << "\n1 - Yes\n0 - No\nWould you like to play again: ";
            std::cin >> playAgain;
        }


        // Collecting survivors
        if (ship.getPosition().intersects(survivor1.getPosition()))
        {
            survivor1.collectSurvivor();
            score++;
        }

        if (ship.getPosition().intersects(survivor2.getPosition()))
        {
            survivor2.collectSurvivor();
            score++;
        }

        if (ship.getPosition().intersects(survivor3.getPosition()))
        {
            survivor3.collectSurvivor();
            score++;
        }

        if (ship.getPosition().intersects(survivor4.getPosition()))
        {
            survivor4.collectSurvivor();
            score++;
        }

        if (ship.getPosition().intersects(survivor5.getPosition()))
        {
            survivor5.collectSurvivor();
            score++;
        }

        if (ship.getPosition().intersects(survivor6.getPosition()))
        {
            survivor6.collectSurvivor();
            score++;
        }

        // Reducing speed based on survivors saved
        if (score == 4)
        {
            ship.reduceSpeed();
        }


        if (!haveWon)
        {   //You have won message with your time(stops updating when you've won)
            std::stringstream ss;
            ss << "Survivors saved:" << score << "    Lives:" << lives << "   Time: " << ceil(time);
            hud.setString(ss.str());

            //Update the HUD text(stops updating when you've won)
            std::stringstream finGame;
            finGame << "                 You have won!" <<"\n           Your Time: " << ceil(time) << " seconds" << "\n\n         Press Space to continue";
            complete.setString(finGame.str());
        }

        // Conditions for winning
        if (ship.getPosition().intersects(flag.getFinPosition()) && score == 6)
        {
            haveWon = 1;
            wave.waveStop();
            ship.shipStop();
            
            // Checking if you have a new best time
            if (time < bestTime)
            {
                bestTime = time;
            }

            // Continue to console to optionally replay game and see best time
            if ((Keyboard::isKeyPressed(Keyboard::Space)))
            {
                window.close();
                std::cout << "\nYour best time: " << ceil(bestTime) << "\n";
                std::cout << "\n1 - Yes\n0 - No\nWould you like to play again: ";
                std::cin >> playAgain;
            }
        }

        // Setting new positions
        flag.update();
        beachBall.update();
        ship.update();
        wave.update();
        survivor1.update();
        survivor2.update();
        survivor3.update();
        survivor4.update();
        survivor5.update();
        survivor6.update();


        /*
            *********************************************************************
            *************************Draw the frame******************************
            *********************************************************************
        */

        // Clear everything from the last frame
        window.clear(Color(26, 128, 182, 255));

        // Draw wave
        window.draw(wave.getShape());

        // Draw rock safezone overlay
        window.draw(rock1.getOverlay());
        window.draw(rock2.getOverlay());
        window.draw(rock3.getOverlay());
        window.draw(rock4.getOverlay());

        // Draw rocks
        window.draw(rock1.getShape());
        window.draw(rock2.getShape());
        window.draw(rock3.getShape());
        window.draw(rock4.getShape());

        // Draw ship
        window.draw(ship.getSprite());




        // Draw survivors
        window.draw(survivor1.getShape());
        window.draw(survivor2.getShape());
        window.draw(survivor3.getShape());
        window.draw(survivor4.getShape());
        window.draw(survivor5.getShape());
        window.draw(survivor6.getShape());

        // Draw flag
        window.draw(flag.getShape());
        window.draw(flag.getfinish());



        // Draw our score
        window.draw(hud);


        // Draw won game
        if (haveWon)
        {
            window.draw(complete);
            // Draw beach ball
            window.draw(beachBall.getShape());
        }


        // Show everything we just drew
        window.display();
    }// End of the while
    }while (playAgain == 1); // End of the do while loop
    return 0;
}