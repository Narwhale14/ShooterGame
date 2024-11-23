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

#include "MainMap.h"

class Game {
    public:
        Game();
        ~Game();

        void update();
        void render();
        void run();
    private:
        sf::RenderWindow *window;
        sf::VideoMode windowBounds;
        sf::Event sfEvent;

        sf::Clock dtClock;
        float dt;

        std::stack<State*> states;

        // Supported keys for the game
        std::map<std::string, int> supportedKeys;

        void initializeWindow();
        void initializeKeys();
};

#endif