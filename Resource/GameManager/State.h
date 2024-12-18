/**
 * @file State.h
 * @author Niall Murray
 * @brief State class declaration. The point of this class is to be an abstract class meaning that it cannot be on object itself unless declared a pointer.
 *        It serves to be the template for any GameState object, which would end up being something like a menu, game end screen, inventory, or just
 *        the normal game state where the player controls the player.
 * @date 2024-10-23
 */

#ifndef STATE_H
#define STATE_H

#include "../Entity/Enemy.h"

class State {
    public:
        State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
        virtual ~State();

        const bool& getQuit() const;
        const bool& getFlush() const;

        virtual void checkForQuit() = 0;
        void endState();

        void updateMousePositions();
        virtual void updateInput(const float& dt) = 0;
        virtual void update(const float& dt) = 0;

        virtual void render(sf::RenderTarget* target = NULL) = 0;
    protected:
        sf::RenderWindow* window;

        std::map<std::string, int>* supportedKeys; // A point to avoid copying list of keys
        std::map<std::string, int> keybinds;

        bool quit;
        bool flush;

        sf::Vector2f mousePosView;

        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font> fonts;
    private:
};

#endif