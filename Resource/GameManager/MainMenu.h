/**
 * @file MenuScreen.h
 * @author Niall Murray
 * @brief Menu class declaration
 * @date 2024-11-05
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"

class MainMenu : public State {
    public:
        MainMenu(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
        virtual ~MainMenu();

        virtual void checkForQuit();

        void updateInput(const float& dt);
        void update(const float& dt);

        void render(sf::RenderTarget* target = nullptr);
    private:
        Button* playButton;
        Button* exitButton;

        void initializeKeybinds();
        void initializeFonts();
        void initializeTextures();
};

#endif