/**
 * @file GameState.h
 * @author Niall Murray
 * @brief GameState class declaration file. This class takes the State template and finishes construction of it's pure virtual functions. Any object of this class will contain
 *        it's scene worth of entities, textures, whatever is visible
 * @date 2024-10-23
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State {
    public:
        GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
        virtual ~GameState();

        // Functions
        void endState();

        void updateInput(const float& dt);
        void update(const float& dt);
        void render(sf::RenderTarget* target = NULL);
    private:
        Entity player;

        // Functions
        void initializeKeybinds();
};

#endif