/**
 * @file Game.h
 * @author Niall Murray
 * @brief The game class declaration file. The Game class is the core class that brings everything together. Constantly updates through checking the current top active GameState
 *        and checking for SFML events. Contains variable deltaTime, which will make frame time consistent across devices by setting it to the time in-between frames and
 *        multiplying it with anything that requires movement or constant updating
 * @date 2024-10-23
 */

#ifndef GAME_H
#define GAME_H

#include "GameState.h"

class Game {
    public:
        // Constructors/Destructor
        Game();
        virtual ~Game();

        // Regular
        void endApplication();

        // Update
        void updateDt();
        void updateSFMLEvents();
        void update();

        // Render
        void render();

        // Core
        void run();

    private:
        // Variables
        sf::RenderWindow *window;
        sf::Event sfEvent;

        sf::Clock dtClock;
        float dt;

        /* 
        States stack - If a state is popped off the stack, then you go down a state
        Think of a stack of cards in uno. The top card is the active one. 
        */
        std::stack<State*> states;

        // Supported keys for the game
        std::map<std::string, int> supportedKeys;

        // Initialization
        void initializeWindow();
        void initializeKeys();
        void initializeStates();
};

#endif